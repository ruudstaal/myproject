/**
 ********************************************************************************
 * @file     StopState.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StopState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "StopState.hpp"

void StopState::doRun(BEModule *pModule)
{
    pModule->startTasks();
}
