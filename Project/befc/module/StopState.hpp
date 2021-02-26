/**
 ********************************************************************************
 * @file     StopState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StopState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef STOPSTATE_HPP_
#define STOPSTATE_HPP_

#include "BEModuleState.hpp"
#include "BEModule.hpp"
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

class StopState: public BEModuleState
{
public:
    StopState() :
            BEModuleState("STOP", RES_S_STOP)
    {
        ;
    }

    /**
     ********************************************************************************
     * @brief      Handling of end of init in state STOP state
     *
     *             Starts all suspended application tasks
     *
     * @param[in]  pModule         Pointer to BEModule class
     *******************************************************************************/
    void doRun(BEModule *pModule);

};
/** @} */

#endif  /**STOPSTATE_HPP_*/
