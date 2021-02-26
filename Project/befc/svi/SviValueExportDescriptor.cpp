/**
 ********************************************************************************
 * @file     SviValueExportDescriptor.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviValueExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SviValueExportDescriptor.hpp"
#include "SviException.hpp"

SviValueExportDescriptor::SviValueExportDescriptor(std::string varName, UINT32 datatype,
        bool readable, bool writeable, UINT32 *pAddr) :
        SviExportDescriptor(varName, datatype, readable, writeable), pAddr(pAddr), min(0.0), max(
                0.0), minMaxSet(false), mode(0)
{
    if (pAddr == NULL)
    {
        throw SviException("Pointer to value must not be NULL");
    }

}

SviValueExportDescriptor::SviValueExportDescriptor(std::string varName, UINT32 datatype,
        UINT32 dataLength, bool readable, bool writeable, UINT32 *pAddr) :
        SviExportDescriptor(varName, datatype, readable, writeable, dataLength), pAddr(pAddr), min(
                0.0), max(0.0), minMaxSet(false), mode(0)
{
    if (pAddr == NULL)
    {
        throw SviException("Pointer to value must not be NULL");
    }
}

void SviValueExportDescriptor::doRegister(SviServer *pServer)
{
    pServer->registerValueSvi(this);
}

