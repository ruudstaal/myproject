/**
 ********************************************************************************
 * @file     RunState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of RunState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef MODULE_RUNSTATE_HPP_
#define MOUDULE_RUNSTATE_HPP_

#include "BEModuleState.hpp"
#include <mtypes.h>
#include <res_e.h>

/**
 * @addtogroup MOD
 * @{
 */

namespace Module
{
class RunState: public BEModuleState
{
public:
    RunState() :
            BEModuleState("RUN", RES_S_RUN)
    {
    }

    /**
     ********************************************************************************
     * @brief      Handling of stop in state RUN state
     *
     *             Suspends all application tasks
     *
     * @param[in]  pModule         Pointer to BEModule class
     * @throws     IllegalStateException
     *******************************************************************************/
    void doStop(BEModule *pModule);
};
}
/** @} */

#endif  /**MODULE_RUNSTATE_HPP_*/
