/**
 ********************************************************************************
 * @file     TerminatedState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of TerminatedState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef TERMINATEDSTATE_HPP_
#define TERMINATEDSTATE_HPP_

#include "BETaskState.hpp"

/**
 * @addtogroup TASK
 * @{
 */

/**
 * Terminated state for a BETask. When a Task is terminated, it cannot be started again.
 */
class TerminatedState: public BETaskState
{

public:
    TerminatedState() :
            BETaskState("TERMINATED")
    {
    }
};
/** @} */

#endif  /*TERMINATEDSTATE_HPP_*/
