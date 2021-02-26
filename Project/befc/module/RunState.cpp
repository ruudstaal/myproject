/**
 ********************************************************************************
 * @file     RunState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of RunState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "module/RunState.hpp"
#include "BEModule.hpp"

void Module::RunState::doStop(BEModule *pModule)
{
    /** Stop all application tasks */
    pModule->stopTasks();
}
