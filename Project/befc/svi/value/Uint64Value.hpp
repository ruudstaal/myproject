/**
 ********************************************************************************
 * @file     Uint64Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef UINT64VALUE_HPP_
#define UINT64VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Uint64Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Uint64Value
     *
     * @param[in]  value    The UINT64 value
     *******************************************************************************/
    explicit Uint64Value(UINT64 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The UINT64 value
     *******************************************************************************/
    VOID setValue(UINT64 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The UINT64 value
     *******************************************************************************/
    UINT64 getValue();

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
    Uint64Value();
    UINT64 val;
};
/** @} */

#endif  /*UINT64VALUE_HPP_*/
