/**
 ********************************************************************************
 * @file     BEModuleState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BEModuleState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#include "module/RunState.hpp"
#include "mcpp.hpp"
#include "BEModuleState.hpp"
#include "ModuleException.hpp"
#include "BEModule.hpp"
#include "SmiHandler.hpp"
#include "InitState.hpp"
#include "DeInitState.hpp"
#include "CfgState.hpp"
#include "EOIState.hpp"
#include "ErrorState.hpp"
#include "ResetState.hpp"
#include "StopState.hpp"
#include "IllegalStateException.hpp"
#include "ModuleConfiguration.hpp"

#include <string>
#include <sstream>

BEModuleState* const BEModuleState::STATE_INIT = new InitState();
BEModuleState* const BEModuleState::STATE_EOI = new EOIState();
BEModuleState* const BEModuleState::STATE_RUN = new Module::RunState();
BEModuleState* const BEModuleState::STATE_STOP = new StopState();
BEModuleState* const BEModuleState::STATE_CFG = new CfgState();
BEModuleState* const BEModuleState::STATE_DEINIT = new InitState();
BEModuleState* const BEModuleState::STATE_RESET = new ResetState();
BEModuleState* const BEModuleState::STATE_ERROR = new ErrorState();

BEModuleState::BEModuleState(std::string sStateName, UINT32 resState) :
        name(sStateName), resState(resState)
{
}

void BEModuleState::doInit(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doInit()")));
}

void BEModuleState::doEOI(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doEOI()")));
}

void BEModuleState::doRun(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doRun()")));
}

void BEModuleState::doStop(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doStop()")));
}

void BEModuleState::doCfgNew(BEModule *pModule)
{
    /** Read new configuration */
    try
    {
        pModule->doCfgRead(ModuleConfiguration(pModule->getAppName()));
    }
    catch(ModuleException &exception)
    {
        error("Configuration not found for module in mconfig.ini - Call never forwarded!");
    }
    catch(...)
    {
        error("Exception caught when handling new configuration!");
    }
}

void BEModuleState::doDeInit(BEModule *pModule)
{
    pModule->doDeinitInternal();
}

void BEModuleState::doReset(BEModule *pModule)
{
    /** call smi deinit. This function will remove all smi call which are registered from the tasks */
    pModule->getSmiHandler()->deInitSmi();

    /** Deinit SVI */
    pModule->getSmiHandler()->deInitSvi();

    /** call deinit internal */
    pModule->doDeinitInternal();

    /** call doInit for basic initializing */
    pModule->doInitInternal();

    /** call doSmiInit for adding SMI-Calls */
    pModule->getSmiHandler()->initSmi();

    /** init SVI */
    pModule->getSmiHandler()->initSvi();
}

std::string BEModuleState::getIllegalStateString(std::string sFunctionName)
{
    std::stringstream stream;
    stream << sFunctionName << " not allowed in " << name;
    return (stream.str());
}

bool BEModuleState::operator==(const BEModuleState &other) const
{
    return (other.name == name);
}

bool BEModuleState::operator!=(const BEModuleState &other) const
{
    return !(other == *this);
}
