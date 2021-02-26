/**
 ********************************************************************************
 * @file     Sint32Value.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SINT32VALUE_HPP_
#define SINT32VALUE_HPP_

#include "SviValue.hpp"
#include <string>

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class Sint32Value: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of Sint32Value
     *
     * @param[in]  value    The SINT32 value
     *******************************************************************************/
    explicit Sint32Value(SINT32 value);

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The SINT32 value
     *******************************************************************************/
    VOID setValue(SINT32 value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The SINT32 value
     *******************************************************************************/
    SINT32 getValue();

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
        return 4;
    }

private:
    Sint32Value();
    SINT32 val;
};
/** @} */

#endif  /*SINT32VALUE_HPP_*/
