/**
 ********************************************************************************
 * @file     Sint64Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SINT64VALUE_HPP_
#define SINT64VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Sint64Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Sint64Value
     *
     * @param[in]  value    The SINT64 value
     *******************************************************************************/
    explicit Sint64Value(SINT64 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The SINT64 value
     *******************************************************************************/
    VOID setValue(SINT64 value);

    SINT64 getValue();
    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The SINT64 value
     *******************************************************************************/

    /**
     ********************************************************************************
     * @brief      Get the value address
     *
     * @retval     The value address as UINT32
     *******************************************************************************/
    UINT32 getValueAddress();

    void setValue(SviValue *pValue);

    UINT32 getLength()
    {
        return 8;
    }

private:
    Sint64Value();
    SINT64 val;
};
/** @} */

#endif  /*SINT64VALUE_HPP_*/
