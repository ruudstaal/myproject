/**
 ********************************************************************************
 * @file     Uint32Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef UINT32VALUE_HPP_
#define UINT32VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Uint32Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Uint32Value
     *
     * @param[in]  value    The UINT32 value
     *******************************************************************************/
    explicit Uint32Value(UINT32 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The UINT32 value
     *******************************************************************************/
    VOID setValue(UINT32 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The UINT32 value
     *******************************************************************************/
    UINT32 getValue();

    /**
     ********************************************************************************
     * @brief      Get the value address
     *
     * @retval     The value address as UINT32
     *******************************************************************************/
    UINT32 getValueAddress();

    UINT32 getLength()
    {
        return 4;
    }

    void setValue(SviValue *pValue);

private:
    Uint32Value();
    UINT32 val;
};
/** @} */

#endif  /*UINT32VALUE_HPP_*/
