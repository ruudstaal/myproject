/**
 ********************************************************************************
 * @file     TerminatingState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of TerminatingState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef TERMINATINGSTATE_HPP_
#define TERMINATINGSTATE_HPP_

#include "BETaskState.hpp"

/**
 * @addtogroup TASK
 * @{
 */

/**
 * State which the Task can be in, when it is terminating. It cannot stay in this state,
 * and no operations are therefore allowed.
 */
class TerminatingState: public BETaskState
{
public:
    TerminatingState() :
            BETaskState("TERMINATING")
    {
    }
};
/** @} */

#endif  /*TERMINATINGSTATE_HPP_*/
