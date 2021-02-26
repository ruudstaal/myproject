/**
 ********************************************************************************
 * @file     SviItem.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviItem
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIITEM_HPP_
#define SVIITEM_HPP_

#include "AbstractSviItem.hpp"
#include "value/SviValue.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SviItem: public AbstractSviItem
{
public:

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value as SviValue type
     *******************************************************************************/
    virtual SviValue* getValue() = 0;

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  pValue   The new value
     *******************************************************************************/
    virtual VOID setValue(SviValue *pValue) = 0;

    /**
     ********************************************************************************
     * @brief      Operator overload for comparing SviItems
     *
     * @retval     True if other has same moduleName and varName
     *******************************************************************************/
    bool operator==(const SviItem &other) const;

};
/** @} */

#endif  /*SVIITEM_HPP_*/
