/**
 ********************************************************************************
 * @file     ArrayValue.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ArrayValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef ARRAYVALUE_HPP_
#define ARRAYVALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class ArrayValue: public SviValue
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of ArrayValue
     *
     * @param[in]  pArray       The pointer to the array
     * @param[in]  datatype     The datatype of the items in the array
     * @param[in]  arrayLength  The length of the array in bytes
     *******************************************************************************/
    ArrayValue(UINT8 *pArray, UINT32 datatype, UINT32 arrayLength);

    /**
     ********************************************************************************
     * @brief      Destroys the instance and frees the memory
     *******************************************************************************/
    ~ArrayValue();

    /**
     ********************************************************************************
     * @brief      Sets the current value.
     *             It reads the number of bytes configured in constructor from the
     *             input pointer. Data is copied, references is not created.
     *
     * @param[in]  pArray    The pointer to the array where it should read from
     *******************************************************************************/
    VOID setValue(UINT8 *pArray);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The pointer to the current value
     *******************************************************************************/
    UINT8* getValue();

    /**
     ********************************************************************************
     * @brief      Get the value address
     *
     * @retval     The value address as UINT32
     *******************************************************************************/
    UINT32 getValueAddress();

    /**
     ********************************************************************************
     * @brief      Get the length of the data
     *
     * @retval     Gets the length of the data
     *******************************************************************************/
    UINT32 getLength();

    void setValue(SviValue *pValue);

private:
    ArrayValue();
    UINT32 length;
    UINT8* pValue;
};
/** @} */

#endif  /*ARRAYVALUE_HPP_*/
