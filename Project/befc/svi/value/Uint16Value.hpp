/**
 ********************************************************************************
 * @file     Uint16Value.hpp
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
#ifndef UINT16VALUE_HPP_
#define UINT16VALUE_HPP_

#include "SviValue.hpp"
#include <string>

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Uint16Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Uint16Value
     *
     * @param[in]  value    The UINT16 value
     *******************************************************************************/
    explicit Uint16Value(UINT16 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The UINT16 value
     *******************************************************************************/
    VOID setValue(UINT16 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The UINT16 value
     *******************************************************************************/
    UINT16 getValue();

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
        return 2;
    }

private:
    Uint16Value();

    UINT16 val;
};
/** @} */

#endif  /*UINT16VALUE_HPP_*/
