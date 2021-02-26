/**
 ********************************************************************************
 * @file     BETask.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BETask
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#pragma implementation "BETask.hpp"

#include <BEFCTypes.hpp>
#include <drv/timer/timerDev.h>
#include <taskLib.h>
#include <tickLib.h>
#include <stdexcept>
#include "BEModule.hpp"
#include "SviException.hpp"
#include "DetectPIAutomaticIOConfigurationFactory.hpp"
#include "BETaskConfiguration.hpp"

BETask::BETask(BETaskConfiguration conf)
{
    init(conf.getModule(), conf.getTaskName(), conf.getCycleTime(), conf.getPriority(), conf.getStackSize(), conf.getIOConfigurationFactory(), conf.getCoreCategory());
}

BETask::BETask(BEModule *pModule, std::string sTaskName)
{
    init(pModule, sTaskName, 0, pModule->getTaskPrior(), DEF_STACK_SIZE, NULL,"");
}

BETask::BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime)
{
	//Change since deprecation - cycletime is changed to microseconds.
    UINT32 newCycleTime = cycleTime * 1000;

    init(pModule, sTaskName, newCycleTime, pModule->getTaskPrior(), DEF_STACK_SIZE, NULL,"");
}

BETask::BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, BOOL8 autoDetectIO)
{
    //Change since deprecation - cycletime is changed to microseconds.
    UINT32 newCycleTime = cycleTime * 1000;

    if(autoDetectIO){
        init(pModule, sTaskName, newCycleTime, pModule->getTaskPrior(), DEF_STACK_SIZE, new DetectPIAutomaticIOConfigurationFactory(),"");
    }
    else{
        init(pModule, sTaskName, newCycleTime, pModule->getTaskPrior(), DEF_STACK_SIZE, new DetectPIConfigurationFactoryImpl(),"");
    }
}

BETask::BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority)
{
    //Change since deprecation - cycletime is changed to microseconds.
    UINT32 newCycleTime = cycleTime * 1000;

    init(pModule, sTaskName, newCycleTime, priority, DEF_STACK_SIZE, NULL,"");
}

BETask::BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority,
        UINT32 stackSize)
{
    //Change since deprecation - cycletime is changed to microseconds.
    UINT32 newCycleTime = cycleTime * 1000;

    init(pModule, sTaskName, newCycleTime, priority, stackSize, NULL,"");
}

BETask::BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority, IOConfigurationFactory *pIOFactory)
{
    //Change since deprecation - cycletime is changed to microseconds.
    UINT32 newCycleTime = cycleTime * 1000;

    init(pModule, sTaskName, newCycleTime, priority, DEF_STACK_SIZE, pIOFactory,"");
}

void BETask::init(BEModule *pModule, std::string sTaskName, int cycleTime, UINT32 priority,
        UINT32 stackSize, IOConfigurationFactory *pIOFactory, std::string coreCategory)
{
    this->debugMode = pModule->getDebugMode();
    if (this->debugMode == APP_DBG_INFO1)
    {
        info("create " << sTaskName);
    }

    this->pModule = pModule;
    this->sAppName = pModule->getAppName();
    this->sTaskName = sTaskName;
    this->sysClkRate = sysClkRateGet();
    this->cycleTime = cycleTime;
    this->pGroups = new std::vector<AbstractSviGroup*>();
    this->priority = priority;
    this->stackSize = stackSize;
    this->options = 0;
	this->tickNext = 0;
	this->tickWait = 1;
	this->coreCategory = coreCategory;

    /** create svi and smi list */
    pLocalSmiRequestList = new std::vector<SmiRequest*>();

    pLocalSviExportList = new std::vector<SviExportDescriptor*>();

    /** Detect and manual adding cards is default. Other behavior must
     * be configured by dependency injection.
     */
    pIOConfiguration = NULL;

    if(pIOFactory == NULL) {
        this->pIOFactory = new DetectPIConfigurationFactoryImpl();
    }
    else{
        this->pIOFactory = pIOFactory;
    }

    /** create the cycle semaphore when cycle time > 0 */
    if (this->cycleTime)
    {
        cycleSema = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    }
    else
    {
        cycleSema = NULL;
    }

    initIO();

    /** set task variables */
    taskId = ERROR;
    setState(BETaskState::STATE_INITIALIZED);
}

BETask::~BETask()
{
    /** Call desctuctor for svi client groups and variables */
	std::vector<AbstractSviGroup*>::iterator it;
    for (it = pGroups->begin(); it != pGroups->end(); ++it)
    {
        SAFE_DELETE(*it);
    }
    SAFE_DELETE(pGroups);

    /** delete all svi server smi calls */
    for (std::vector<SmiRequest*>::iterator itSmiRequest = pLocalSmiRequestList->begin();
            itSmiRequest != pLocalSmiRequestList->end(); ++itSmiRequest)
    {
        SAFE_DELETE(*itSmiRequest);
    }
    pLocalSmiRequestList->clear();
    SAFE_DELETE(pLocalSmiRequestList);


    /** remove all Svi descriptors */
    for (std::vector<SviExportDescriptor*>::iterator p = pLocalSviExportList->begin();
            p != pLocalSviExportList->end(); ++p)
    {
        SAFE_DELETE(*p);
    }
    pLocalSviExportList->clear();
    SAFE_DELETE(pLocalSviExportList);

    /** Delete IO setup */
    SAFE_DELETE(pIOConfiguration);
    SAFE_DELETE(pIOFactory);

    /** Delete semaphores */
    if (cycleSema)
    {
        semDelete(cycleSema);
    }
}

bool BETask::addSviGroup(AbstractSviGroup *pGroup)
{
	std::vector<AbstractSviGroup*>::iterator it;

    /** Check if group already exist */
    for (it = pGroups->begin(); it != pGroups->end(); ++it)
    {
        if ((*it)->getName().compare(pGroup->getName()) == 0)
        {
            return (false);
        }
    }

    /** Add group to vector */
    pGroups->push_back(pGroup);
    return (true);
}

bool BETask::removeSviGroup(AbstractSviGroup *pGroup)
{
	std::vector<AbstractSviGroup*>::iterator it;

    /** Check if group exist */
    for (it = pGroups->begin(); it != pGroups->end(); ++it)
    {
        if ((*it)->getName().compare(pGroup->getName()) == 0)
        {
            pGroups->erase(it);
            return (true);
        }
    }
    return (false);
}


void BETask::sviGroupUpdateOut(void)
{
    /** Check if group already exist */
    for (std::vector<AbstractSviGroup*>::iterator it = pGroups->begin(); it != pGroups->end(); ++it)
    {
        if ((*it)->isActive())
        {
            try
            {
                (*it)->updateOut();
            }
            catch (SviException const& e)
            {
                warn("Could not perform updateout on group " << (*it)->getName() << "due to: " << e.what());
            }
            catch(std::exception& e) {
                warn("Could not perform updateout on group " << (*it)->getName() << "due to: " << e.what());
            }
            catch(...) {
                warn("Could not perform updateout on group " << (*it)->getName() << " due to unknown exception");
            }
        }
    }
}

void BETask::refreshSviGroups(void)
{
    /** Check if group already exist */
    for (std::vector<AbstractSviGroup*>::iterator it = pGroups->begin(); it != pGroups->end(); ++it)
    {
        if ((*it)->isActive())
        {
            try
            {
                (*it)->refresh();
            }
            catch (SviException const& e)
            {
            	warn("Could not update group " << (*it)->getName() << "due to: " << e.what());
            }
            catch(std::exception& e) {
                warn("Could not update group " << (*it)->getName() << "due to: " << e.what());
            }
            catch(...) {
                warn("Could not update group " << (*it)->getName() << " due to unknown exception");
            }
        }
    }
}

void BETask::initIO(){
	if(this->pIOConfiguration != NULL) {
		throw std::invalid_argument("IO configuration was already initialized. Please only call initIO once.");
	}
	this->pIOConfiguration = pIOFactory->createConfiguration(pIOFactory->createIOStrategy(this));
}

void BETask::setStateSemaphore(SEM_ID* pStateSema)
{
    this->pStateSema = pStateSema;
}

void BETask::setDebugMode(UINT32 debugMode)
{
    this->debugMode = debugMode;
}

void BETask::setState(BETaskState* const pState)
{
    this->pState = pState;
}

UINT32 BETask::getDebugMode(void)
{
    return (debugMode);
}

void BETask::run(void)
{

	if (getDebugMode() == APP_DBG_INFO1)
    {
        info("Task: " << getTaskName() << " started in state: " << pState->getName());
    }

    /** Initialize ticks when running cyclic task */
    if (cycleSema)
    {
        tickNext = tickGet() + sampleTicks;
    }

    while (!isTerminated())
    {
        if (pState == BETaskState::STATE_SUSPENDED)
        {
            if (semTake(*pStateSema, WAIT_FOREVER) == OK)
            {
                if (isTerminated())
                {
                    break;
                }
                else
                {
                    doEOI();
                    setState(BETaskState::STATE_RUN);
                }
            }
        }

        /** if the cycle time is set call cycleDelay otherwise cycle end */
        if (cycleSema)
        {
            cycleDelay();
        }
        else
        {
        	/** User delay function */
        	doEventDelay();
        }

        cycleStart();

        if(isTerminated() == false){
            /** refresh groups which have been set to active. */
            refreshSviGroups();
        }

         /** Notify IO handling to read IO - If a configuration exists for current task*/
        if(pIOConfiguration != NULL){
			try {
				pIOConfiguration->updateIn();
			}
			catch(MIOexception &ex) {
				error("BETask::Could not read IO. " << ex.what() << "from card " << ex.CardNumber());
			}
		}

        /** do the cycle work */
        cycleWork();

        if (isTerminated() == false)
        {
            /** Update out on groups which have been set to active. */
            sviGroupUpdateOut();
        }

        /** Notify IO handling to write IO*/
        if(pIOConfiguration != NULL){
        	try{
        		pIOConfiguration->updateOut();
        	}
        	catch(MIOexception &ex) {
        		error("BETask::Could not write IO. " << ex.what() << " from card " << ex.CardNumber() << ". " << ex.ErrorCode());
        	}
        }

        cycleEnd();
    }
    setState(BETaskState::STATE_TERMINATED);

    /** This method is used in M1Module to delete the own instance */
    terminated();

}

void BETask::start(bool autoSuspend) throw (IllegalStateException)
{
    pState->start(this, autoSuspend);

    if (autoSuspend == false)
    {
        setState(BETaskState::STATE_RUN);
    }
}

void BETask::stop() throw (IllegalStateException)
{
    pState->stop(this);
    setState(BETaskState::STATE_SUSPENDED);
}

void BETask::terminate() throw (IllegalStateException)
{
    pState->terminate(this);
}

bool BETask::isTerminated()
{
    return this->pState == BETaskState::STATE_TERMINATED
            || this->pState == BETaskState::STATE_TERMINATING;
}

std::string BETask::getTaskName()
{
    return (sTaskName);
}

SINT32 BETask::getTaskId(void)
{
    return (taskId);
}

BEModule* BETask::getModule(VOID)
{
    return (pModule);
}

BETaskState* BETask::getTaskState(void)
{
    return (pState);
}

std::vector<SmiRequest*>* BETask::getSmiRequestList(void)
{
    return (pLocalSmiRequestList);
}

std::vector<SviExportDescriptor*>* BETask::getSviDescriptorList()
{
    return pLocalSviExportList;
}

void BETask::terminated()
{
    std::stringstream ss;
           ss << "Task " << this->getTaskName().c_str() << " is Terminated! " << this->getTaskState()->getName().c_str();
           log_Wrn("%s", ss.str().c_str());
    if (getDebugMode() == APP_DBG_INFO1)
    {
        info(getTaskName() << " (" << this << ") terminated!");
    }
}

void BETask::cycleStart()
{
    /** get start ticks */
    tickNext += sampleTicks;

    /** inform system about cycle start */
    if(cycleTime){
        if(cycleTime < 30000000){
            sys_CycleStart();
        }
        else {
            sys_CycleStart2();
        }
    }
}

void BETask::cycleEnd()
{
    /** inform system about cycle end */
    sys_CycleEnd();
}

void BETask::cycleDelay()
{
    tickWait = tickNext - tickGet();
    if (tickWait < 0)
    {
        tickWait = 0;
    }

    /** check if the task was interrupted */
    if (!semTake(cycleSema, tickWait))
    {
        if (getDebugMode() == APP_DBG_INFO2)
        {
            info(getTaskName() << " task was interrupted!");
        }
    }
}

void BETask::doEventDelay(void)
{
    log_Err("When setting cycletime to 0, an implementation of doEventDelay(void) is needed");
    taskDelay(sysClkRateGet());
}

void BETask::doTerminate(void)
{
	if (cycleSema)
	{
		/** release the cycle task semaphore */
		semFlush(cycleSema);
	}
    else
    {
        /** Print error message for event task */
    	log_Err("Task %s is missing an implementation of doTerminate(void)", sTaskName.c_str());
    }
}

void BETask::doEOI(void)
{
}

void BETask::addSmiRequest(SmiRequest *pRequest)
{
    pLocalSmiRequestList->push_back(pRequest);
}

void BETask::exportToSvi(SviExportDescriptor *pDescriptor)
{
    this->pLocalSviExportList->push_back(pDescriptor);
}

void BETask::exportToSvi(std::vector<SviExportDescriptor*> descriptors)
{

	std::vector<SviExportDescriptor*>::iterator ite;
    for (ite = descriptors.begin(); ite != descriptors.end(); ++ite)
    {
        exportToSvi((*ite));
    }
}

MIOConfiguration* BETask::getIOConfiguration() {
	return pIOConfiguration;
}

