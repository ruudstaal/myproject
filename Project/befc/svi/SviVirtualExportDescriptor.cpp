/**
 ********************************************************************************
 * @file     SviVirtualExportDescriptor.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviVirtualExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SviVirtualExportDescriptor.hpp"
#include "SviException.hpp"
#include "SviServer.hpp"

#include "mcpp.hpp"
#include <iostream>

SviVirtualExportDescriptor::SviVirtualExportDescriptor(std::string varName, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler) :
        SviExportDescriptor(varName, datatype, readable, writeable), pHandler(pHandler), pParameter(
                NULL), id(0), mode(0)
{
}

SviVirtualExportDescriptor::SviVirtualExportDescriptor(std::string varName, UINT32 datatype,
        bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id, void *pParameter) :
        SviExportDescriptor(varName, datatype, readable, writeable), pHandler(pHandler), pParameter(
                pParameter), id(id), mode(0)
{
}

SviVirtualExportDescriptor::SviVirtualExportDescriptor(std::string varName, UINT32 datatype,
        UINT32 dataLength, bool readable, bool writeable, VirtualSviHandler *pHandler) :
        SviExportDescriptor(varName, datatype, readable, writeable, dataLength), pHandler(pHandler), pParameter(
                NULL), id(0), mode(0)
{
}

SviVirtualExportDescriptor::SviVirtualExportDescriptor(std::string varName, UINT32 datatype,
        UINT32 dataLength, bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id,
        void *pParameter) :
        SviExportDescriptor(varName, datatype, readable, writeable, dataLength), pHandler(pHandler), pParameter(
                pParameter), id(id), mode(0)
{
}

SviVirtualExportDescriptor::~SviVirtualExportDescriptor()
{
}

void SviVirtualExportDescriptor::doRegister(SviServer *pServer)
{
    pServer->registerVirtualSvi(this);
}
