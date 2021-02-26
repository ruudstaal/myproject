/**
 ********************************************************************************
 * @file     DeInitState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DeInitState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef DEINITSTATE_HPP_
#define DEINITSTATE_HPP_

#include "BEModuleState.hpp"
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

/**
 * Temporary state. No operations are allowed in this state
 */
class DeInitState: public BEModuleState
{
public:
    DeInitState() :
            BEModuleState("DEINIT", RES_S_DEINIT)
    {
    }

    /**
     ********************************************************************************
     * @brief      Handling of new cfg in state DEINIT state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doCfgNew(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Handling of deinit in state DEINIT state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doDeInit(BEModule *pModule);
};
/** @} */

#endif  /**DEINITSTATE_HPP_*/
