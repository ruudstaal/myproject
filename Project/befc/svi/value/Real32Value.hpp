/**
 ********************************************************************************
 * @file     Real32Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of real32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef REAL32VALUE_HPP_
#define REAL32VALUE_HPP_

#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Real32Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Real32Value
     *
     * @param[in]  value    The REAL32 value
     *******************************************************************************/
    explicit Real32Value(REAL32 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value as REAL32
     *******************************************************************************/
    REAL32 getValue();

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  value    The REAL32 value
     *******************************************************************************/
    VOID setValue(REAL32 value);

    /**
     ********************************************************************************
     * @brief      Gets value address
     *
     * @retval     The value address.
     *******************************************************************************/
    UINT32 getValueAddress();

    void setValue(SviValue *pValue);

    UINT32 getLength()
    {
        return 4;
    }

private:
    Real32Value();
    REAL32 val;
};
/** @} */

#endif  /**REAL32VALUE_HPP_*/
