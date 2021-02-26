/**
 ********************************************************************************
 * @file     SuspendedState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SuspendedState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SUSPENDEDSTATE_HPP_
#define SUSPENDEDSTATE_HPP_

#include "BETaskState.hpp"

/**
 * @addtogroup TASK
 * @{
 */

class SuspendedState: public BETaskState
{

public:
    SuspendedState() :
            BETaskState("SUSPENDED")
    {
    }

    /**
     ********************************************************************************
     * @brief      Behavior of start in suspended state
     *
     * @param[in]  pTask			   Pointer to BETask
     * @param[in]  autoSuspend         Auto suspend flag (true = start task suspended,
     *                                 false = start tasks running).
     *******************************************************************************/
    void start(BETask *pTask, bool autoSuspend);

    /**
     ********************************************************************************
     * @brief      Behavior of terminate in suspended state
     *
     * @param[in]  pTask			   Pointer to BETask
     *******************************************************************************/
    void terminate(BETask *pTask);
};
/** @} */

#endif  /*SUSPENDEDSTATE_HPP_*/
