/**
 ********************************************************************************
 * @file     CfgState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of CfgState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef CFGSTATE_HPP_
#define CFGSTATE_HPP_

#include "BEModuleState.hpp"

/**
 * @addtogroup MOD
 * @{
 */

/**
 * Temporary state. No operations are allowed in this state
 */
class CfgState: public BEModuleState
{
public:
    CfgState() :
            BEModuleState("CFG", 0)
    {
    }

    /**
     ********************************************************************************
     * @brief      Handling of new cfg in state NEWCFG state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doCfgNew(BEModule *pModule);
};
/** @} */

#endif  /**CFGSTATE_HPP_*/
