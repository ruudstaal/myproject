/**
 ********************************************************************************
 * @file     SingleItemReadStrategyImpl.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SingleItemReadStrategyImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SINGLEITEMREADSTRATEGYIMPL_HPP_
#define SINGLEITEMREADSTRATEGYIMPL_HPP_

#include <SviGroupItemStrategy.hpp>
#include "SviSystem.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SingleItemStrategyImpl: public SviGroupItemStrategy
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of SingleItemStrategyImpl. This instance will
     *             make use of setVal and getVal, which means that for every item in
     *             the group, a SMI call will be sent for getVal and setVal.
     *
     * @param[in]  pSystem   Pointer to the SviSystem
     *******************************************************************************/
    SingleItemStrategyImpl(SviSystem *pSystem) : pSviSystem(pSystem){}

    TFailList readValues(AbstractSviGroup *pGroup);

    TFailList writeValues(AbstractSviGroup *pGroup);

private:

    SviSystem *pSviSystem;

};
/** @} */

#endif  /*SINGLEITEMREADSTRATEGYIMPL_HPP_*/
