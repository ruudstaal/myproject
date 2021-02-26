/**
 ********************************************************************************
 * @file     SviValue.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIVALUE_HPP_
#define SVIVALUE_HPP_

#include <mtypes.h>
#include <string.h>
#include "log_e.h"
#include <sstream>
/**
 * @addtogroup SVI-VALUE
 * @{
 */

/**
 * The abstract class which all datatype objects derive from.
 */
class SviValue
{
public:

    /**
     ********************************************************************************
     * @brief      Abstract class constructor. Datatype is common for all values
     *
     * @param[in]  datatype     The datatype as SVI_F_xxx
     *******************************************************************************/
    explicit SviValue(UINT32 datatype)
    {
        this->datatype = datatype;
    }

    /**
     ********************************************************************************
     * @brief      Gets the datatype. See SVI_F_xxx
     *
     * @retval     SVI_F_xxx
     *******************************************************************************/
    UINT32 getDatatype()
    {
        return datatype;
    }

    /**
     ********************************************************************************
     * @brief      Gets the length of data
     *******************************************************************************/
    virtual UINT32 getLength() = 0;

    /**
     ********************************************************************************
     * @brief      Gets the value pointer adress
     *******************************************************************************/
    virtual UINT32 getValueAddress() = 0;

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *             Copies the value, and does not delete the object given as input
     *
     * @param[in]  pValue     The value to set to this value.
     *******************************************************************************/
    virtual void setValue(SviValue *pValue)
    {
        log_Wrn("SetValue for datatype %d not implemented", datatype);
    }

    /**
     ********************************************************************************
     * @brief      Equals function to dertermine equality for two SviValues
     *             Compares on datatype, length and memory compare.
     *
     * @param[in]  pSviVal     The value to compare to this
     *******************************************************************************/
    bool equals(SviValue *pSviVal)
    {
        if (this->getDatatype() != pSviVal->getDatatype())
        {
            return false;
        }
        return (memcmp((void*) this->getValueAddress(), (void*) pSviVal->getValueAddress(),
                this->getLength())) == 0;
    }

    virtual ~SviValue()
    {
    }
    ;

private:
    SviValue()
    {
        datatype = 0;
    }
    ;

    UINT32 datatype;
};
/** @} */

#endif  /*SVIVALUE_HPP_*/
