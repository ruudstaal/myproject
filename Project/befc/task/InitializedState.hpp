/**
 ********************************************************************************
 * @file     InitializedState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of InitializedState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef INITIALIZEDSTATE_HPP_
#define INITIALIZEDSTATE_HPP_

#include "BETaskState.hpp"

/**
 * @addtogroup TASK
 * @{
 */

class InitializedState: public BETaskState
{
public:
    InitializedState() :
            BETaskState("INITIALIZED")
    {
    }

    /**
     ********************************************************************************
     * @brief      Behaviour of start in initialized state
     *
     * @param[in]  pTask     Pointer of BETask class.
     * @param[in]  autoSuspend         Auto suspend flag (true = start task suspended,
     *                                 false = start tasks running).
     *******************************************************************************/
    void start(BETask *pTask, bool autoSuspend);
};
/** @} */

#endif  /*INITIALIZEDSTATE_HPP_*/
