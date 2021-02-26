/**
 ********************************************************************************
 * @file     ValueFactory.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ValueFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef VALUEFACTORY_HPP_
#define VALUEFACTORY_HPP_

#include "SviValue.hpp"
#include "SviItem.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class ValueFactory
{

public:
    /**
     ********************************************************************************
     * @brief      Creates the corresponding SviValue related to the datatype
     *
     * @param[in]  pValue           A pointer to the value
     * @param[in]  datatype         The datatype
     * @throws     SviException     If datatype is not supported
     * @retval     The SviValue
     *******************************************************************************/
    static SviValue* createValue(UINT32 *pValue, UINT32 datatype);

    /**
     ********************************************************************************
     * @brief      Creates the corresponding SviValue related to the datatype
     *
     * @param[in]  pValue           A pointer to the value
     * @param[in]  pItem            A pointer to the SviItem
     * @retval     The SviValue
     *******************************************************************************/
    static SviValue* createValue(UINT32 *pValue, SviItem *pItem);

    /**
     ********************************************************************************
     * @brief      Creates the corresponding SviValue related to the datatype for
     *             block/array values
     *
     * @param[in]  pItem           A pointer to the SviItem
     * @param[in]  pBuffer         The pointer to the data
     * @param[in]  length          The length of the data
     * @retval     The SviValue
     *******************************************************************************/
    SviValue* createBLKValue(SviItem *pItem, UINT8 *pBuffer, UINT32 length);


    /**
     ********************************************************************************
     * @brief      Creates the corresponding SviValue related to the datatype for
     *             block/array values
     *
     * @param[in]  datatype        Datatype as described in SVI_F_xxxx
     * @param[in]  pBuffer         The pointer to the data
     * @param[in]  length          The length of the data
     * @retval     The SviValue
     *******************************************************************************/
    static SviValue* createBLKValue(UINT32 datatype, UINT8 *pBuffer, UINT32 length);
};
/** @} */

#endif  /*VALUEFACTORY_HPP_*/
