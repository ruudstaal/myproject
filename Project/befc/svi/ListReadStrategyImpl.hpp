/**
 ********************************************************************************
 * @file     ListReadStrategyImpl.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ListReadStrategyImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef LISTREADSTRATEGYIMPL_HPP_
#define LISTREADSTRATEGYIMPL_HPP_

#include <SviGroupItemStrategy.hpp>
#include "SviGroup.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class ListReadStrategyImpl: public SviGroupItemStrategy
{
public:

    ListReadStrategyImpl(SviSystem *pSystem);

    /**
     ********************************************************************************
     * @brief      This strategy for reading is only for 32 bit values, where getBlk should not
     *             be used. This means that it can speed up by using the GetValLst function, which
     *             reads 64 values at one time.
     *
     * @param[in]  pGroup       The pointer to the group where values should be refreshed
     * @retval     A TFailList with the items which could not be read.
     * @throws     SviException if one SviItem in the group has an array datatype (64 bit values included)
     *******************************************************************************/
    TFailList readValues(AbstractSviGroup *pGroup);

    /**
     ********************************************************************************
     * @brief      This strategy for writing is only for 32 bit values, where setBlk should not
     *             be used. This means that it can speed up by using the SetValLst function, which
     *             writes up to 64 values at one time.
     *
     * @param[in]  pGroup       The pointer to the group where values should be written to the SVI layer
     * @retval     A TFailList with the items which could not be written.
     * @throws     SviException if one SviItem in the group has an array datatype (64 bit values included)
     *******************************************************************************/
    TFailList writeValues(AbstractSviGroup *pGroup);

private:
    /**
     ********************************************************************************
     * @brief      Helper function to get read the values from SVI
     *
     * @param[in]  lib          The pointer to the module to retrieve values from
     * @param[in]  addresses    The addresses to the SVI variables
     * @param[in]  pItems       The pointer to the SviItems
     * @param[in]  size         The number of elements in the arrays
     *******************************************************************************/
    void fillValuesInternal(pLib lib, SVI_ADDR addresses[], AbstractSviItem* pItems[], int size);

    SviSystem *pSystem;

};
/** @} */

#endif  /*LISTREADSTRATEGYIMPL_HPP_*/
