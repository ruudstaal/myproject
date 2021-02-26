/**
 ********************************************************************************
 * @file     Real64Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Real64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef REAL64VALUE_HPP_
#define REAL64VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Real64Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The REAL64 value
     *******************************************************************************/
    VOID setValue(REAL64 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The REAL64 value
     *******************************************************************************/
    REAL64 getValue();

    /**
     ********************************************************************************
     * @brief      Creates an instance of Real64Value
     *
     * @param[in]  value    The REAL64 value
     *******************************************************************************/
    explicit Real64Value(REAL64 value);

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
    Real64Value();
    REAL64 val;
};
/** @} */

#endif  /**REAL64VALUE_HPP_*/
