/**
 ********************************************************************************
 * @file     Sint8Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SINT8VALUE_HPP_
#define SINT8VALUE_HPP_

#include "SviValue.hpp"
#include <string>

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Sint8Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Sint8Value
     *
     * @param[in]  value    The SINT8 value
     *******************************************************************************/
    explicit Sint8Value(SINT8 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The SINT8 value
     *******************************************************************************/
    VOID setValue(SINT8 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The SINT8 value
     *******************************************************************************/
    SINT8 getValue();

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
    Sint8Value();
    SINT8 val;
};
/** @} */

#endif  /*SINT8VALUE_HPP_*/
