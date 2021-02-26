/**
 ********************************************************************************
 * @file     ValueFactory.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ValueFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "ValueFactory.hpp"
#include "SviValue.hpp"
#include "Uint8Value.hpp"
#include "Uint16Value.hpp"
#include "Uint32Value.hpp"
#include "Uint64Value.hpp"
#include "Sint8Value.hpp"
#include "Sint16Value.hpp"
#include "Sint32Value.hpp"
#include "Sint64Value.hpp"
#include "Real32Value.hpp"
#include "Real64Value.hpp"
#include "Bool8Value.hpp"
#include "StringValue.hpp"
#include "SviException.hpp"
#include "ArrayValue.hpp"
#include <sstream>

SviValue* ValueFactory::createValue(UINT32 *pValue, UINT32 datatype)
{
    switch (datatype)
    {
        case SVI_F_UINT32:
            return new Uint32Value(*(UINT32*) pValue);
        case SVI_F_REAL32:
            return new Real32Value(*(REAL32*) pValue);
        case SVI_F_BOOL8:
            return new Bool8Value(*(BOOL8*) pValue);
        case SVI_F_UINT1:
        case SVI_F_UINT8:
            return new Uint8Value(*(UINT8*) pValue);
        case SVI_F_UINT16:
            return new Uint16Value(*(UINT16*) pValue);
        case SVI_F_SINT8:
            return new Sint8Value(*(SINT8*) pValue);
        case SVI_F_SINT16:
            return new Sint16Value(*(SINT16*) pValue);
        case SVI_F_SINT32:
            return new Sint32Value(*(SINT32*) pValue);
        case SVI_F_STRING:
            throw SviException("Use createStringValue on factory instead");
        default:
            std::stringstream ss;
            ss << "Datatype not supported when creating SviValue: " << datatype;
            throw SviException(ss.str());

    }
}

SviValue* ValueFactory::createValue(UINT32 *pValue, SviItem *pItem)
{
    return createValue(pValue, pItem->getDatatype());
}

SviValue* ValueFactory::createBLKValue(SviItem *pItem, UINT8 *pBuffer, UINT32 length)
{
    UINT32 val = pItem->getDatatype();

    if (val == SVI_F_STRING)
    {
        char text[length];
        memcpy(text, pBuffer, length);
        return new StringValue(std::string(text));
    }
    else if (val == SVI_F_UINT64 && length == sizeof(UINT64))
    {
        return new Uint64Value(*(UINT64*) pBuffer);
    }
    else if (val == SVI_F_SINT64 && length == sizeof(SINT64))
    {
        return new Sint64Value(*(SINT64*) pBuffer);
    }
    else if (val == SVI_F_REAL64 && length == sizeof(REAL64))
    {
        return new Real64Value(*(REAL64*) pBuffer);
    }
    else
    {
        return new ArrayValue(pBuffer, pItem->getDatatype(), length);
    }
}

SviValue* ValueFactory::createBLKValue(UINT32 datatype, UINT8 *pBuffer, UINT32 length)
{
    UINT32 val = datatype;

    if (val == SVI_F_STRING)
    {
        char text[length];
        memcpy(text, pBuffer, length);
        return new StringValue(std::string(text));
    }
    else if (val == SVI_F_UINT64 && length == sizeof(UINT64))
    {
        return new Uint64Value(*(UINT64*) pBuffer);
    }
    else if (val == SVI_F_SINT64 && length == sizeof(SINT64))
    {
        return new Sint64Value(*(SINT64*) pBuffer);
    }
    else if (val == SVI_F_REAL64 && length == sizeof(REAL64))
    {
        return new Real64Value(*(REAL64*) pBuffer);
    }
    else
    {
        return new ArrayValue(pBuffer, datatype, length);
    }
}



