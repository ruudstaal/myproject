/**
 ********************************************************************************
 * @file     Sint16Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint16Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SINT16VALUE_HPP_
#define SINT16VALUE_HPP_

#include "SviValue.hpp"
#include <string>

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Sint16Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Sint16Value
     *
     * @param[in]  value    The SINT16 value
     *******************************************************************************/
    explicit Sint16Value(SINT16 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The SINT16 value
     *******************************************************************************/
    VOID setValue(SINT16 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The SINT16 value
     *******************************************************************************/
    SINT16 getValue();

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
    Sint16Value();
    SINT16 val;
};
/** @} */

#endif  /*SINT16VALUE_HPP_*/
