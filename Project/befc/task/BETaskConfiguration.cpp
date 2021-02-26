/**
 ********************************************************************************
 * @file     BETaskConfiguration.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Nov 4, 2015 1:06:19 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <BETaskConfiguration.hpp>
#include "ConfigurationException.hpp"
#include "BEModule.hpp"

BETaskConfiguration::BETaskConfiguration(BEModule *pModule, std::string sTaskName, UINT32 priority)
{
    init(pModule, sTaskName);
    this->priority = priority;
    this->type = EVENT;
}

BETaskConfiguration::BETaskConfiguration(BEModule *pModule, std::string sTaskName, UINT32 priority, UINT32 cycleTime)
{
    init(pModule, sTaskName);
    this->priority = priority;
    this->cycleTime = cycleTime;
    this->type = CYCLIC;
}

BETaskConfiguration::BETaskConfiguration(BEModule *pModule, std::string sTaskName)
{
    init(pModule, sTaskName);
    this->type = CYCLIC;
    initDataFromCRU();
}

void BETaskConfiguration::init(BEModule *pModule, std::string sTaskName)
{
    this->pModule = pModule;
    this->cycleTime = 0;
    this->sTaskName = sTaskName;
    this->stackSize = DEF_STACK_SIZE;
    this->priority = pModule->getTaskPrior();
    this->pIOFactory = NULL; //Will force the BETask to initialize/create some default
    this->coreCategory = "";
}

void BETaskConfiguration::initDataFromCRU() {
    ModuleConfiguration conf(pModule->getAppName());

    SINT32 prior = conf.getConfigAsInt("BaseParms", "Priority");
    if(isPriorityValid(prior)) {
        this->priority = prior;
    }
    else {
        this->priority = pModule->getTaskPrior(); //Default is application task priority
        log_Wrn("Ignoring priority from CRU since value is not in interval UINT32(20 .. 255). Value was: %d", prior);
    }

    UINT32 cycle = conf.getConfigAsInt("ControlTask", "CycleTime");
    if(isCycleTimeValid(cycle)) {
        this->cycleTime = cycle;
    }
    else {
        this->cycleTime = 100000; //Default: 100 ms
        log_Wrn("Ignoring cycletime from CRU since value is not in interval UINT32(500 .. 1000000). Value was: %d", cycle);
    }
}



bool BETaskConfiguration::isCycleTimeValid(UINT32 cycleTime)
{
    if (cycleTime <= 60000000 && cycleTime >= 500)
    {
        return true;
    }
    return false;
}

bool BETaskConfiguration::isPriorityValid(UINT32 prior)
{
    if (prior >= 20 && prior <= 255)
    {
        return true;
    }
    return false;
}

void BETaskConfiguration::setCycleTime(UINT32 cycleTime)
{
    if (type == EVENT)
    {
        throw ConfigurationException(
                "Cannot set cycletime when type has been set to EVENT from constructor");
    }

    if(isCycleTimeValid(cycleTime)){
        this->cycleTime = cycleTime;
    }
    else{
        throw ConfigurationException("Cycletime not within limit");
    }
}

void BETaskConfiguration::setIOConfigurationFactory(IOConfigurationFactory *pFactory)
{
    this->pIOFactory = pFactory;
}

void BETaskConfiguration::setPriority(UINT32 priority)
{
    if(isPriorityValid(priority)){
        this->priority = priority;
    }
    else{
        throw ConfigurationException("Priority not within limits");
    }
}

void BETaskConfiguration::setStackSize(UINT32 stackSize)
{
    this->stackSize = stackSize;
}

BETaskConfiguration::TaskType BETaskConfiguration::getTaskType()
{
    return this->type;
}

std::string BETaskConfiguration::getTaskName()
{
    return this->sTaskName;
}

BEModule* BETaskConfiguration::getModule()
{
    return this->pModule;
}

UINT32 BETaskConfiguration::getPriority()
{
    return this->priority;
}

UINT32 BETaskConfiguration::getStackSize()
{
    return this->stackSize;
}

UINT32 BETaskConfiguration::getCycleTime()
{
    return this->cycleTime;
}

IOConfigurationFactory* BETaskConfiguration::getIOConfigurationFactory()
{
    return this->pIOFactory;
}
