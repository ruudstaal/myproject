/**
 ********************************************************************************
 * @file     InitializedState.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of InitializedState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <taskLib.h>
#include <sysLib.h>
#include "InitializedState.hpp"
#include "TaskException.hpp"
#include "BETask.hpp"
#include "mcpp.hpp"

/**
 ********************************************************************************
 * @brief     C-function for to be called by taskSpawn and then calling the
 *            main function of the BETask class.
 *
 *            ATTENTION:  This way to call BETask::Main() is chosen in order
 *                        to make it possible that the member BETask::Main
 *                        has not to be MLOCAL.
 *
 *******************************************************************************/
extern "C" SINT32 CallBack_Run(BETask &pTask)
{
    try
    {
        pTask.run();
    }
    catch (...)
    {
        //catch any unhandled exception: this should lead to an entry in the logbook
        log_Err("Task failed. The task %s throwed an unhandled exception", pTask.getTaskName().c_str());
    }
    /** VXWorks task dies after this */
    return OK;
}

void InitializedState::start(BETask *pTask, bool autoSuspend)
{
    if (autoSuspend)
    {
        pTask->setState(BETaskState::STATE_SUSPENDED);
    }

    pTask->sysClkRate = sysClkRateGet();

    /** for handling larger cycletimes, which can result in an overflow of UINT32 calculation*/
    unsigned long long clkRate = pTask->sysClkRate;
    unsigned long long cycleTime = pTask->cycleTime;
    pTask->sampleTicks = clkRate * cycleTime / 1000000ULL;

    SINT32 taskId;
    if (pTask->coreCategory.compare("") == 0)
    {
        taskId = sys_TaskSpawn((char*) pTask->sAppName.c_str(), (char*) pTask->sTaskName.c_str(),
                pTask->priority, pTask->options | VX_FP_TASK, pTask->stackSize,
                (FUNCPTR) CallBack_Run, pTask);
    }
    else
    {
        //If core category has been specified
        taskId = sys_TaskSpawnCategory((char*) pTask->sAppName.c_str(),
                (char*) pTask->sTaskName.c_str(), (char*)pTask->coreCategory.c_str(), pTask->priority,
                pTask->options | VX_FP_TASK, pTask->stackSize, (FUNCPTR) CallBack_Run, pTask);
    }







    if (taskId == ERROR)
    {
        std::stringstream ss;
        ss << "Error when spawning  " << pTask->sTaskName << std::endl;
        error(ss.str());
        throw(TaskException(ss.str()));
    }
    pTask->taskId = taskId;

}

