/**
 ********************************************************************************
 * @file     SviExportDescriptor.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIEXPORTDESCRIPTOR_HPP_
#define SVIEXPORTDESCRIPTOR_HPP_

#include <mtypes.h>
#include <string>
#include "svi/atomic/Lockable.hpp"
/**
 * @addtogroup SVI
 * @{
 */

class SviServer;

class SviExportDescriptor
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of SviExportDescriptor for simple values
     *             (this also includes UINT64, SINT64, REAL64)
     *
     * @param[in]  varName		Name of the SVI variable
     * @param[in]  datatype		Datatype of the SVI variable
     * @param[in]  readable		Whether or not SVI variable should be readable
     * @param[in]  writeable	Whether or not SVI variable should be writable
     *******************************************************************************/
    SviExportDescriptor(std::string varName, UINT32 datatype, bool readable, bool writeable);

    /**
     ********************************************************************************
     * @brief      Create an instance of SviExportDescriptor for arrays
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  dataLength   Length of the data in bytes
     *******************************************************************************/
    SviExportDescriptor(std::string varName, UINT32 datatype, bool readable, bool writeable,
            UINT32 dataLength);

    /**
     ********************************************************************************
     * @brief      Gets the datalength for the simple datatypes
     *
     * @param[in]  datatype     The datatype (ex. SVI_F_UINT32)
     * @throws     SviException If datatype is unknown or block type
     * @retval     The length of the datatype in bytes.
     *******************************************************************************/
    static UINT32 getDataLength(UINT32 datatype);

    /**
     ********************************************************************************
     * @brief      Returns if datatype should be treated as an array/block
     *
     * @param[in]  datatype  The datatype
     * @retval     True if datatype should be treated as an array, false if not.
     *******************************************************************************/
    static bool isArrayDatatype(UINT32 datatype);

    /**
     ********************************************************************************
     * @brief      Gets the format for the SVI export
     *
     * @param[in]  pDescriptor  Pointer to the descriptor
     * @retval     The format for the SVI export
     *******************************************************************************/
    static UINT32 getFormat(SviExportDescriptor *pDescriptor);

    virtual ~SviExportDescriptor(){}

    bool isReadable()
    {
        return readable;
    }

    bool isWriteable()
    {
        return writeable;
    }

    bool isArray()
    {
        return isArrayType;
    }

    std::string getVarName()
    {
        return varName;
    }

    UINT32 getDatatype()
    {
        return datatype;
    }

    UINT32 getDataLength()
    {
        return dataLength;
    }

    void setLockable(Lockable *pLockable)
    {
        this->pLockable = pLockable;
    }

    Lockable* getLockable()
    {
        return this->pLockable;
    }

    virtual void doRegister(SviServer *server) = 0;

private:
    std::string varName;
    UINT32 datatype;
    bool readable;
    bool writeable;
    UINT32 dataLength;
    bool isArrayType;

    Lockable *pLockable;
};
/** @} */

#endif  /*SVIEXPORTDESCRIPTOR_HPP_*/
