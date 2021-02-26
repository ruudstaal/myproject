/**
 ********************************************************************************
 * @file     Uint8Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef UINT8VALUE_HPP_
#define UINT8VALUE_HPP_

#include "SviValue.hpp"
#include <string>

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Uint8Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Uint8Value
     *
     * @param[in]  value    The Uint8 value
     *******************************************************************************/
    explicit Uint8Value(UINT8 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The UINT8 value
     *******************************************************************************/
    VOID setValue(UINT8 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The UINT8 value
     *******************************************************************************/
    UINT8 getValue();

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
        return 1;
    }

private:
    Uint8Value();

    UINT8 val;
};
/** @} */

#endif  /*UINT8VALUE_HPP_*/
