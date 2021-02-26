/**
 ********************************************************************************
 * @file     RunState.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of RunState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "task/RunState.hpp"
#include "BETask.hpp"

void Task::RunState::stop(BETask *pTask)
{
    /** release the cycle semaphore */
    if (pTask->cycleSema)
    {
        semGive(pTask->cycleSema);
    }
}

void Task::RunState::terminate(BETask *pTask)
{
    pTask->setState(BETaskState::STATE_TERMINATING);

    // Wakeup task for termination
    pTask->doTerminate();
}
