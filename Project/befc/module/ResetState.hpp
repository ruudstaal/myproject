/**
 ********************************************************************************
 * @file     ResetState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ResetState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef RESETSTATE_HPP_
#define RESETSTATE_HPP_

#include "BEModuleState.hpp"

/**
 * @addtogroup MOD
 * @{
 */

/**
 * Temporary state. No operations are allowed in this state
 */
class ResetState: public BEModuleState
{
public:
    ResetState() :
            BEModuleState("RESET", 0)
    {
        ;
    }

};
/** @} */

#endif  /**RESETSTATE_HPP_*/
