/**
 ********************************************************************************
 * @file     BEModule.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BEModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#pragma implementation "BEModule.hpp"

/** Includes */
#include <iostream>
#include <taskLib.h>

#include "ModuleConfiguration.hpp"
#include "BEModule.hpp"
#include "BEModuleState.hpp"
#include "ModuleException.hpp"
#include "SviException.hpp"
#include "SmiException.hpp"
#include "SmiHandler.hpp"
#include "mcpp.hpp"
#include "BETaskConfiguration.hpp"
#include "M1SviSystem.hpp"
#include "log_e.h"

BEModule::BEModule() :
        fpPanicHandler(NULL)
{
    initValues();
}

BEModule::BEModule(SviSystem *pSviSystem) : fpPanicHandler(NULL), pSviSystem(pSviSystem)
{
    initValues();
}

BEModule::BEModule(VOIDFUNCPTR fpPanicHandler) :
        fpPanicHandler(fpPanicHandler)
{
    initValues();
}

VOID BEModule::initValues(VOID)
{
    cfgLine = 0;
    debug = 0;
    minVers = 0;
    maxVers = 0;
    memPart = 2;
    taskPrior = DEF_TASK_PRIO;
    pApplication_tasks = NULL;
    pLibMap = NULL;
    pLocalSviExportList = NULL;
    pModuleState = NULL;
    pSmiHandler = NULL;
    pSmiID = NULL;
    stateSema = NULL;
    pModuleConf = NULL;

    pSviSystem = new M1SviSystem();
}

BEModule::~BEModule()
{
    SAFE_DELETE(pModuleConf);
    SAFE_DELETE(pSviSystem);
}

VOID BEModule::init(MOD_CONF *pConf, MOD_LOAD *pLoad)
{
    /** Print info 'Module alive'. */
    if (pConf->DebugMode & APP_DBG_INFO1)
    {
        info(
                "Starting '" << pConf->TypeName << "', App='" << pConf->AppName << "', Part=" << pConf->MemPart);
    }
    pLibMap = new TStrLibMap();
    pModuleState = BEModuleState::STATE_INIT;

    /** store the application name */
    sAppName = pConf->AppName;
    debug = pConf->DebugMode;
    memPart = pConf->MemPart;
    sProfileName = pConf->ProfileName;
    taskPrior = pConf->TskPrior;

    /** Set version number of software module */
    RES_MODXINFO modInfo;
    res_ModXInfo(pConf->AppName, &modInfo);
    setVersion(Version(modInfo.Version));

    /** set minimum and maximum rpc version */
    minVers = 2;
    maxVers = 2;

    /** Semaphore for halting of module (start/stop) */
    if (!(stateSema = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY)))
    {
        error("Error in semBCreate!");
        throw(ERROR);
    }

    /** Deliver module parameters to resource management. */
    if (res_ModParam((CHAR*) sAppName.c_str(), minVers, maxVers, RES_UNLIMITUSR, &pSmiID))
    {
        error("Module not registered!");
        throw(ERROR);
    }

    /** set the module state to init */
    setModState(BEModuleState::STATE_INIT);

    /** Create list of BETasks for all application tasks */
    pApplication_tasks = new std::list<BETask*>;

    /** Create list of all module related SVI */
    pLocalSviExportList = new std::vector<SviExportDescriptor*>();

    try
    {
        /** Initializes the configuration for the tasks/module to use **/
        initConfiguration(pConf->LineNbr);

        /** Starting task for handling of SMI queries. */
        pSmiHandler = new SmiHandler(BETaskConfiguration(this,"b" + getAppName(), SMI_SRV_PRIO));

        /** Call doInit for basic initializing */
        doInit();

        /** Initialise module related SMI calls */
        pSmiHandler->initSmi();

        /** Initialise SVI server, and add SVI variables */
        pSmiHandler->initSvi();

        /** Start bTask for SMI communication */
        pSmiHandler->start(false);

        /** Start all the application tasks in suspended mode */
        startTasksInternal(true);

    }
    catch (SviException const& e)
    {
        error("Error in SVI when initializing module. " << e.what());
        throw(ERROR);
    }
    catch (SmiException const& e)
    {
        error("Error in SMI when initializing module. " << e.what());
        throw(ERROR);
    }
    catch (ModuleException const& e)
    {
        error("Error when accessing CRU for configuration. " << e.what());
        throw(ERROR);
    }
    catch (...)
    {
        error("Error when initializing module...");
        throw(ERROR);
    }

    if (pSmiHandler->getTaskId() == ERROR)
    {
        setModState(BEModuleState::STATE_ERROR);
        throw(ERROR);
    }
    else
    {
        if (pConf->DebugMode & APP_DBG_INFO1)
        {
            info(sAppName << ": successfully started.");
        }

        setModState(BEModuleState::STATE_EOI);

        /** Freeing no longer required memory.
         *
         *  ATTENTION: In case of an error the module handler
         *             will free this memory.
         */
        if (pLoad->pCfg && pLoad->LenCfg)
        {
            sys_MemPFree(pConf->MemPart, pLoad->pCfg);
        }

        if (pLoad->pAttr && pLoad->LenAttr)
        {
            sys_MemPFree(pConf->MemPart, pLoad->pAttr);
        }
    }
}

void BEModule::initConfiguration(SINT32 line) {
    SAFE_DELETE(pModuleConf);
    pModuleConf = new ModuleConfiguration(this->sAppName, line);

    /** Read new configuration */
    doCfgRead(*pModuleConf);
}

void BEModule::deinit()
{

    SAFE_DELETE(pSmiHandler);

    SAFE_DELETE(pApplication_tasks);

    /** Freeing resources in case of an error. */
    if (stateSema)
    {
        semDelete(stateSema);
        stateSema = NULL;
    }

    /** remove all Svi descriptors */
    for (std::vector<SviExportDescriptor*>::iterator p = pLocalSviExportList->begin();
            p != pLocalSviExportList->end(); ++p)
    {
        SAFE_DELETE(*p);
    }
    pLocalSviExportList->clear();

    SAFE_DELETE(pLocalSviExportList);

    TStrLibMap::iterator p;
    for (p = pLibMap->begin(); p != pLibMap->end(); ++p)
    {
        if (pSviSystem->UngetLib(p->second) == -1)
        {
            error("Unable to Unget library function pointer");
        }
    }

    pLibMap->clear();
    SAFE_DELETE(pLibMap);

    SINT32 ret = res_ModDelete((CHAR*) sAppName.c_str());
    if (ret)
    {
        error("Unable to delete module in MOD. ret = " << ret);
    }

    /** Delete static module states */
    delete (BEModuleState::STATE_CFG);
    delete (BEModuleState::STATE_DEINIT);
    delete (BEModuleState::STATE_EOI);
    delete (BEModuleState::STATE_ERROR);
    delete (BEModuleState::STATE_INIT);
    delete (BEModuleState::STATE_RESET);
    delete (BEModuleState::STATE_RUN);
    delete (BEModuleState::STATE_STOP);

    delete (this);

}

SINT32 BEModule::getSmiTaskId(VOID)
{
    return (pSmiHandler->getTaskId());
}

void BEModule::setModState(BEModuleState * const pModState)
{
    pModuleState = pModState;
    if (pModuleState->getResState() != 0)
    {
        res_ModState((CHAR*) sAppName.c_str(), pModuleState->getResState());
    }
}

BEModuleState BEModule::getModState(VOID)
{
    return (*pModuleState);
}

SINT32 BEModule::getDebugMode(VOID)
{
    return (debug);
}

VOID BEModule::setDebugMode(UINT32 debugMode)
{
    /** Set debug mode for all tasks */
    debug = debugMode;

    /** set the debug mode to every task */
    for (std::list<BETask*>::iterator itBETask = pApplication_tasks->begin();
            itBETask != pApplication_tasks->end(); ++itBETask)
    {
        (*itBETask)->setDebugMode(debug);
    }
}

std::string BEModule::getDescription(VOID)
{
    return (sDescription);
}

void BEModule::setDescription(std::string sDescription)
{
    this->sDescription = sDescription;
}

Version BEModule::getVersion(VOID)
{
    return (cVersion);
}

void BEModule::setVersion(Version version)
{
    cVersion = version;
}

VOID BEModule::setJumpEnv(jmp_buf JumpEnv)
{
    memcpy(this->JumpEnv, JumpEnv, sizeof(jmp_buf));
}

SmiHandler* BEModule::getSmiHandler(void)
{
    if (NULL == pSmiHandler)
    {
        throw ModuleException("SMI handler not initialized yet!");
    }
    return (pSmiHandler);
}

VOID BEModule::addTask(BETask* pTask)
{
    if(NULL == pTask)
    {
        throw ModuleException("Trying to add task as NULL pointer!");
    }

    pApplication_tasks->push_back(pTask);
}

VOID BEModule::removeTask(BETask* Task)
{
    pApplication_tasks->remove(Task);
}

VOID BEModule::startTasks()
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        (*it)->start(false);
    }

    semFlush(stateSema);
}

void BEModule::startTasksInternal(bool suspend)
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        (*it)->setStateSemaphore(&stateSema);
        (*it)->start(true);
    }

}

VOID BEModule::stopTasks()
{

    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        (*it)->stop();
    }
}

VOID BEModule::terminateTasks()
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        (*it)->terminate();
    }

    /** If tasks were suspended when terminated, they need to be woken up. */
    semFlush(stateSema);

}

bool BEModule::isTasksTerminated(VOID)
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        if ((*it)->getTaskState() == BETaskState::STATE_SUSPENDED
                || (*it)->getTaskState() == BETaskState::STATE_TERMINATING)
        {
            semFlush(stateSema);
            return false;
        }
        if ((*it)->getTaskState() != BETaskState::STATE_TERMINATED)
        {
            return false;
        }
    }
    return true;
}

VOID BEModule::clearTasks(VOID)
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        SAFE_DELETE(*it);
    }
    pApplication_tasks->clear();
}

void BEModule::doCfgRead(ModuleConfiguration configuration)
{
    /** Override if needed.. */
}

BOOL8 BEModule::doRun(void)
{
    try
    {
        pModuleState->doRun(this);
        setModState(BEModuleState::STATE_RUN);
        return (true);
    }
    catch(IllegalStateException const& e)
    {
        error("IllegalStateException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }

    return (false);
}

BOOL8 BEModule::doEndOfInit(void)
{
    try
    {
        pModuleState->doEOI(this);
        setModState(BEModuleState::STATE_RUN);
        return (true);
    }
    catch (IllegalStateException const& e)
    {
        error("IllegalStateException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }

    return (false);
}

BOOL8 BEModule::doStop(void)
{
    try
    {
        pModuleState->doStop(this);
        setModState(BEModuleState::STATE_STOP);
        return (true);
    }
    catch (IllegalStateException const& e)
    {
        error("IllegalStateException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }

    return (false);
}

BOOL8 BEModule::doNewCfg(void)
{
    try
    {
        setModState(BEModuleState::STATE_CFG);
        pModuleState->doCfgNew(this);
        setModState(BEModuleState::STATE_EOI);
        return (true);
    }
    catch (IllegalStateException const& e)
    {
        error("IllegalStateException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }

    return (false);
}

BOOL8 BEModule::doReset(void)
{
    try
    {
        setModState(BEModuleState::STATE_RESET);
        pModuleState->doReset(this);
        startTasksInternal(true);
        setModState(BEModuleState::STATE_EOI);
        return (true);
    }
    catch (IllegalStateException const& e)
    {
        error("IllegalStateException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }
    catch (ModuleException const& e)
    {
        error("ModuleException: " << e.what());
        setModState(BEModuleState::STATE_ERROR);
    }

    return (false);
}

void BEModule::doInitInternal(void)
{
    /** Initialize application tasks */
    if (!doInit())
    {
        throw(ModuleException("Application module could not be initialized"));
    }
}

BOOL8 BEModule::doDeinit(void)
{
    try
    {
        pModuleState->doDeInit(this);
        setModState(BEModuleState::STATE_DEINIT);
        return (true);
    }
    catch (const IllegalStateException &e)
    {
        error("IllegalStateException: " << e.what());
    }

    return (false);
}

void BEModule::doDeinitInternal(void)
{
    /** terminate all registered task */
    terminateTasks();
    /** give time for the applications to terminate */
    bool terminated = false;
    for (int i = 0; i < 50; i++)
    {
        terminated = isTasksTerminated();
        if (terminated == false)
        {
            taskDelay(100);
        }
        else
        {
            break;
        }
    }

    if (terminated == false)
    {
        error("Tasks did not terminate in time.");
    }

    forceTaskDelete();

    /** delete all tasks */
    clearTasks();
}

void BEModule::forceTaskDelete(void)
{
    for (std::list<BETask*>::iterator it = pApplication_tasks->begin();
            it != pApplication_tasks->end(); ++it)
    {
        if ((*it)->getTaskState() != BETaskState::STATE_TERMINATED)
        {
        	taskDelete((*it)->getTaskId());
        }
    }
}

pLib BEModule::renewLibAddress(std::string name)
{
    TStrLibMap::iterator p;

    /** Go through all libs which have been initialized */
    for (p = pLibMap->begin(); p != pLibMap->end(); ++p)
    {
        if (p->first.compare(name) == 0)
        {
            pSviSystem->UngetLib(p->second);
            pLibMap->erase(p);
        }
    }
    return getLibAddress(name);
}

pLib BEModule::getLibAddress(std::string name)
{
    TStrLibMap::iterator p;

    /** Go through all libs which have been initialized */
    for (p = pLibMap->begin(); p != pLibMap->end(); ++p)
    {
        if (p->first.compare(name) == 0)
        {
            return (p->second);
        }
    }

    pLib lib = pSviSystem->GetLib((CHAR*) (name.c_str()));
    if (lib == 0)
    {
        std::stringstream buf;
        buf << "Could not get lib for module '" << name.c_str() << "' Software module instance not found.";
        throw(ModuleException(buf.str()));
    }

    TStrLibPair pair = TStrLibPair(name, lib);
    pLibMap->insert(pair);
    return (lib);
}

void BEModule::exportToSvi(SviExportDescriptor *pDescriptor)
{
    if (getModState() == *BEModuleState::STATE_INIT)
    {
        this->pLocalSviExportList->push_back(pDescriptor);
    }
    else
    {
        std::cout << "trying to export svi in different state than init " << std::endl;
    }
}
