/**
 ********************************************************************************
 * @file     ErrorState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ErrorState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef ERRORSTATE_HPP_
#define ERRORSTATE_HPP_

#include "BEModuleState.hpp"
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

class ErrorState: public BEModuleState
{
public:
    ErrorState() :
            BEModuleState("ERROR", RES_S_ERROR)
    {
        ;
    }

private:

};
/** @} */

#endif  /**ERRORSTATE_HPP_*/
