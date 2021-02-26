/**
 ********************************************************************************
 * @file     Bool8Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Bool8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BOOL8VALUE_HPP_
#define BOOL8VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Bool8Value: public SviValue
{
public:

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  value    The boolean value
     *******************************************************************************/
    VOID setValue(bool value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value
     *******************************************************************************/
    bool getValue();

    /**
     ********************************************************************************
     * @brief      Create an instance of Bool8Value
     *
     * @param[in]  value    The value for initialization
     *******************************************************************************/
    explicit Bool8Value(BOOL8 value);

    /**
     ********************************************************************************
     * @brief      Gets the value address
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
    /**
     ********************************************************************************
     * @brief      Create an instance of Bool8Value. Default value is 0
     *******************************************************************************/
    Bool8Value();
    bool val;
};
/** @} */

#endif  /**BOOL8VALUE_HPP_*/
