/**
 ********************************************************************************
 * @file     SviExportDescriptor.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SviExportDescriptor.hpp"
#include "SviException.hpp"
#include "svi.h"

SviExportDescriptor::SviExportDescriptor(std::string varName, UINT32 datatype, bool readable,
        bool writeable) :
        varName(varName), datatype(datatype), readable(readable), writeable(writeable), pLockable(NULL)
{
    this->dataLength = SviExportDescriptor::getDataLength(datatype);

    /** All datatypes over 4 bytes are treated as arrays/blocks. */
    if (this->dataLength > 4)
    {
        this->isArrayType = true;
    }
    else
    {
        this->isArrayType = false;
    }
}

SviExportDescriptor::SviExportDescriptor(std::string varName, UINT32 datatype, bool readable,
        bool writeable, UINT32 dataLength) :
        varName(varName), datatype(datatype), readable(readable), writeable(writeable), dataLength(
                dataLength), pLockable(NULL)
{
    this->isArrayType = true;
}

UINT32 SviExportDescriptor::getFormat(SviExportDescriptor *pDescriptor)
{
    UINT32 format = pDescriptor->getDatatype();
    /** add read access if neccessary */
    format |= pDescriptor->isReadable() ? SVI_F_OUT : 0;
    /** add write access if neccessary */
    format |= pDescriptor->isWriteable() ? SVI_F_IN : 0;
    /** add SVI_F_BLK when array */
    format |= pDescriptor->isArray() ? SVI_F_BLK : 0;

    return format;
}

UINT32 SviExportDescriptor::getDataLength(UINT32 datatype)
{
    switch (datatype)
    {
        case SVI_F_BOOL8:
        case SVI_F_UINT1:
        case SVI_F_UINT8:
        case SVI_F_SINT8:
        case SVI_F_CHAR8:
            return 1;
        case SVI_F_UINT16:
        case SVI_F_SINT16:
        case SVI_F_CHAR16:
            return 2;
        case SVI_F_UINT32:
        case SVI_F_SINT32:
        case SVI_F_REAL32:
            return 4;
        case SVI_F_REAL64:
        case SVI_F_UINT64:
        case SVI_F_SINT64:
            return 8;
        default:
            throw SviException(
                    "Unsupported datatype - Should not ask for datalength for MIXED, BLK, etc.");
    }
}

bool SviExportDescriptor::isArrayDatatype(UINT32 datatype)
{
    switch (datatype)
    {
        case SVI_F_MIXED:
        case SVI_F_BLK:
        case SVI_F_REAL64:
        case SVI_F_UINT64:
        case SVI_F_SINT64:
            return true;
    }
    return false;
}

