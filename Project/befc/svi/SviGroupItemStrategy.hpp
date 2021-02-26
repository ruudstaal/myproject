/**
 ********************************************************************************
 * @file     SviGroupItemStrategy.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviGroupItemStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIGROUPITEMSTRATEGY_HPP_
#define SVIGROUPITEMSTRATEGY_HPP_

/**
 * @addtogroup SVI
 * @{
 */

#include "AbstractSviGroup.hpp"

class SviGroupItemStrategy
{
public:
    /**
     ********************************************************************************
     *
     * @brief      Strategy implementation should perform an update of the svi values
     *             in the group. Hence, read values from the svi layers and update the
     *             objects
     *
     * @param[in]  pGroup  The group to update
     *******************************************************************************/
    virtual TFailList readValues(AbstractSviGroup *pGroup) = 0;

    /**
     ********************************************************************************
     *
     * @brief      Strategy implementation should perform a write to the SVI layer using
     *             values from the object in the group.
     *
     * @param[in]  pGroup  The group to get values from
     *******************************************************************************/

    virtual TFailList writeValues(AbstractSviGroup *pGroup) = 0;

    virtual ~SviGroupItemStrategy(){}

protected:

    static TErrPair makePair(SINT32 errorCode, AbstractSviItem *pItem) {
#if __cplusplus >= 201103L
        return std::make_pair(errorCode, pItem);
#else
        return std::make_pair<SINT32, AbstractSviItem*>(errorCode, pItem);
#endif
    }
};
/** @} */

#endif  /*SVIGROUPITEMSTRATEGY_HPP_*/
