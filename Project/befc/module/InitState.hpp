/**
 ********************************************************************************
 * @file     InitState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of InitState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef INITSTATE_HPP_
#define INITSTATE_HPP_

#include "BEModuleState.hpp"
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

class InitState: public BEModuleState
{
public:
    InitState() :
            BEModuleState("INIT", RES_S_INIT)
    {
    }
    ;

    /**
     ********************************************************************************
     * @brief      Handling of new cfg in state INIT state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doCfgNew(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Handling of reset in state INIT state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doReset(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Handling of deinit in state INIT state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doDeInit(BEModule *pModule);
};
/** @} */

#endif  /**INITSTATE_HPP_*/
