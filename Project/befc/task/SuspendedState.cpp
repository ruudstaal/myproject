/**
 ********************************************************************************
 * @file     SuspendedState.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SuspendedState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <taskLib.h>
#include <tickLib.h>
#include "SuspendedState.hpp"
#include "BETask.hpp"

void SuspendedState::start(BETask *pTask, bool autoSuspend)
{
    // Reinitialize time to wait after task has been suspended
    pTask->tickNext = tickGet() + pTask->sampleTicks;
}

void SuspendedState::terminate(BETask *pTask)
{
	pTask->setState(BETaskState::STATE_TERMINATING);

    // Wakeup task for termination
    pTask->doTerminate();
}
