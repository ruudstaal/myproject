/**
 ********************************************************************************
 * @file     SviExportHelper.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviExportHelper
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SviExportHelper.hpp"
#include "SviValueExportDescriptor.hpp"
#include "SviVirtualExportDescriptor.hpp"
#include <string>
#include "SviException.hpp"
#include <iostream>
#include <svi.h>

#include <stdio.h>


SviExportDescriptor* SviExportHelper::exportValue(std::string name, UINT32 datatype, bool readable,
        bool writeable, UINT32* pVal)
{
    return exportValue(name, datatype, readable, writeable, pVal, NULL);
}

SviExportDescriptor* SviExportHelper::exportValue(std::string name, UINT32 datatype, bool readable, bool writeable, UINT32 *pVal, Lockable *pLockable) {
    SviValueExportDescriptor *pDesc = new SviValueExportDescriptor(name, datatype, readable, writeable, pVal);
    if(pLockable != NULL) {
        pDesc->setLockable(pLockable);
    }
    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportHiddenValue(std::string name, UINT32 datatype, bool readable,
        bool writeable, UINT32 *pVal)
{
    SviValueExportDescriptor *pDesc = static_cast<SviValueExportDescriptor*>(exportValue(name,
            datatype, readable, writeable, pVal));
    pDesc->setHidden();

    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportValue(std::string name, UINT32 datatype, bool readable,
        bool writeable, UINT32 *pVal, REAL64 min, REAL64 max)
{
    SviValueExportDescriptor *pDesc = static_cast<SviValueExportDescriptor*>(exportValue(name,
            datatype, readable, writeable, pVal));
    pDesc->setMinValue(min);
    pDesc->setMaxValue(max);
    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportHiddenValue(std::string name, UINT32 datatype, bool readable,
        bool writeable, UINT32 *pVal, REAL64 min, REAL64 max)
{
    SviValueExportDescriptor *pDesc = static_cast<SviValueExportDescriptor*>(exportValue(name,
            datatype, readable, writeable, pVal));
    pDesc->setMinValue(min);
    pDesc->setMaxValue(max);
    pDesc->setHidden();

    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportVirtualValue(std::string name, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id, void* pParameter)
{
    return new SviVirtualExportDescriptor(name, datatype, readable, writeable, pHandler, id,
            pParameter);
}

SviExportDescriptor* SviExportHelper::exportHiddenVirtualValue(std::string name, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id, void* pParameter)
{
    SviVirtualExportDescriptor *pDesc = static_cast<SviVirtualExportDescriptor*>(exportVirtualValue(
            name, datatype, readable, writeable, pHandler, id, pParameter));
    pDesc->setHidden();
    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportVirtualValue(std::string name, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler)
{
    return new SviVirtualExportDescriptor(name, datatype, readable, writeable, pHandler);
}

SviExportDescriptor* SviExportHelper::exportHiddenVirtualValue(std::string name, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler)
{
    SviVirtualExportDescriptor *pDesc = static_cast<SviVirtualExportDescriptor*>(exportVirtualValue(
            name, datatype, readable, writeable, pHandler));
    pDesc->setHidden();
    return(pDesc);
}

SviExportDescriptor* SviExportHelper::exportVirtualArray(std::string name, UINT32 datatype,
        UINT32 dataLength, bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id,
        void* pParameter)
{
    return new SviVirtualExportDescriptor(name, datatype, dataLength, readable, writeable, pHandler,
            id, pParameter);
}

SviExportDescriptor* SviExportHelper::exportString(std::string name, UINT32 *pString, UINT32 length)
{
    SviValueExportDescriptor *pDesc = new SviValueExportDescriptor(name, SVI_F_STRING, length, true,
            true, pString);
    return pDesc;
}

SviExportDescriptor* SviExportHelper::exportHiddenString(std::string name, UINT32 *pString, UINT32 length)
{
    SviValueExportDescriptor *pDesc = static_cast<SviValueExportDescriptor*>(exportString(name, pString, length));
    pDesc->setHidden();
    return pDesc;
}

std::vector<SviExportDescriptor*> SviExportHelper::exportStringArray(std::string name,
        UINT32 *aArray, UINT32 elementLength, UINT32 stringLength, bool exportIndividual,
        bool readable, bool writeable)
{
    std::vector<SviExportDescriptor*> res;
    res.push_back(
            new SviValueExportDescriptor(name, SVI_F_STRINGLST, elementLength * stringLength,
                    readable, writeable, aArray));
    if (exportIndividual)
    {
        char* pChar = (char*) aArray;
        std::stringstream ss;
        for (UINT32 i = 0; i < elementLength; i++)
        {
            ss << name.c_str() << "." << i;
            res.push_back(exportString(ss.str(), (UINT32*) pChar, stringLength));
            ss.str(std::string());
            pChar += stringLength;
        }
    }
    return res;
}

std::vector<SviExportDescriptor*> SviExportHelper::exportArray(std::string name, UINT32 *aArray,
        UINT32 datatype, UINT32 size, bool readable, bool writeable, bool exportIndividual)
{
    UINT32 dataTypeLength = SviExportDescriptor::getDataLength(datatype);

    if (size == SviExportDescriptor::getDataLength(datatype))
    {
        throw SviException("To export array, the total size must be larger than datatype");
    }

    if (size % dataTypeLength != 0)
    {
        throw SviException("Arraysize % datatypelength must be 0");
    }

    std::vector<SviExportDescriptor*> res;

    /** Export the array itself*/
    res.push_back(new SviValueExportDescriptor(name, datatype, size, readable, writeable, aArray));

    if (exportIndividual)
    {
        /** Export the single items.*/
        int cycles = size / dataTypeLength;
        char* pChar = (char*) aArray;

        std::stringstream ss;
        for (int i = 0; i < cycles; i++)
        {
            ss << name.c_str() << "." << i;
            res.push_back(exportValue(ss.str(), datatype, readable, writeable, (UINT32*) pChar));
            pChar += dataTypeLength;
            ss.str(std::string());
        }
    }
    return res;

}

std::vector<SviExportDescriptor*> SviExportHelper::exportArray(std::string name, UINT32 *aArray,
        UINT32 datatype, UINT32 size, bool exportIndividual)
{
    return exportArray(name, aArray, datatype, size, true, true, exportIndividual);
}

std::vector<SviExportDescriptor*> SviExportHelper::exportArray(std::string name, UINT32 *aArray,
        UINT32 datatype, UINT32 size, bool readable, bool writeable, bool exportIndividual, Lockable *pLockable)
{
    UINT32 dataTypeLength = SviExportDescriptor::getDataLength(datatype);

    if (size == SviExportDescriptor::getDataLength(datatype))
    {
        throw SviException("To export array, the total size must be larger than datatype");
    }

    if (size % dataTypeLength != 0)
    {
        throw SviException("Arraysize % datatypelength must be 0");
    }

    std::vector<SviExportDescriptor*> res;

    SviExportDescriptor *pDesc;
    /** Export the array itself*/
    pDesc = new SviValueExportDescriptor(name, datatype, size, readable, writeable, aArray);
    pDesc->setLockable(pLockable);
    res.push_back(pDesc);

    if (exportIndividual)
    {
        /** Export the single items.*/
        int cycles = size / dataTypeLength;
        char* pChar = (char*) aArray;

        std::stringstream ss;
        for (int i = 0; i < cycles; i++)
        {
            ss << name.c_str() << "." << i;
            pDesc = exportValue(ss.str(), datatype, readable, writeable, (UINT32*) pChar);
            if(dataTypeLength > 4) {
                pDesc->setLockable(pLockable);
            }
            res.push_back(pDesc);
            pChar += dataTypeLength;
            ss.str(std::string());
        }
    }
    return res;

}
