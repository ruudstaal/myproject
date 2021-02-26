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

/** Avoid problems with multiple inclusion */
#ifndef TASK_RUNSTATE_HPP_
#define TASK_RUNSTATE_HPP_

#include "BETaskState.hpp"

/**
 * @addtogroup TASK
 * @{
 */

namespace Task
{

class RunState: public BETaskState
{

public:
    RunState() :
            BETaskState("RUN")
    {
    }

    /**
     ********************************************************************************
     * @brief      Behaviour of stop in run state
     *
     * @param[in]  pTask		Pointer to BETask
     *******************************************************************************/
    void stop(BETask *pTask);

    /**
     ********************************************************************************
     * @brief      Behaviour of terminate in run state
     *
     * @param[in]  pTask		Pointer to BETask
     *******************************************************************************/
    void terminate(BETask *pTask);
};

}
/** @} */

#endif  /*TASK_RUNSTATE_HPP_*/
