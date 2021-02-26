/**
 ********************************************************************************
 * @file     StringValue.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StringValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef STRINGVALUE_HPP_
#define STRINGVALUE_HPP_

#include <string>
#include "SviValue.hpp"

/**
 * @addtogroup SVI-VALUE
 * @{
 */

class StringValue: public SviValue
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of StringValue
     *
     * @param[in]  value    The string value
     *******************************************************************************/
    explicit StringValue(std::string value);

    ~StringValue();

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value    The string value
     *******************************************************************************/
    VOID setValue(std::string value);

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The string value
     *******************************************************************************/
    std::string getValue();

    /**
     ********************************************************************************
     * @brief      Get the value address
     *
     * @throws     SviException due to not supported (yet)
     * @retval     The value address as UINT32
     *******************************************************************************/
    UINT32 getValueAddress();

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The string value
     *******************************************************************************/
    UINT32 getLength();

    void setValue(SviValue *pValue);

private:
    StringValue();
    std::string value;
};
/** @} */

#endif  /*STRINGVALUE_HPP_*/
