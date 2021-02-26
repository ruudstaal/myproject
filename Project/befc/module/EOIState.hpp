/**
 ********************************************************************************
 * @file     EOIState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of EOIState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef EOISTATE_HPP_
#define EOISTATE_HPP_

#include "BEModuleState.hpp"
#include <iostream>
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

class EOIState: public BEModuleState
{
public:
    EOIState() :
            BEModuleState("EOI", RES_S_EOI)
    {
    }

    /**
     ********************************************************************************
     * @brief      Handling of run in state EOI state
     *
     *
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doRun(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Handling of end of init in state EOI state
     *
     *             Starts all suspended application tasks
     *
     * @param[in]  pModule         Pointer to BEModule class
     *******************************************************************************/
    void doEOI(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Handling of new cfg in state EOI state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doCfgNew(BEModule *pModule);
};
/** @} */

#endif  /**EOISTATE_HPP_*/
