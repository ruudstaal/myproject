/**
 ********************************************************************************
 * @file     GetModuleInfoReply.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of GetModuleInforeply
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <string>
#include <iostream>
#include "log_e.h"
#include "GetModuleInfoReply.hpp"

GetModuleInfoReply::GetModuleInfoReply() :
        SmiCallReply(), returncode(0),moduleName(""),desc(""),vType(0),verscode(0),state(0), debugMode(0)
{
}

void GetModuleInfoReply::readReply(SmiStream *pStream)
{
    this->returncode = pStream->readSINT32();
    moduleName = pStream->readString(M_MODNAMELEN_A);
    desc = pStream->readString(SMI_DESCLEN_A);
    vType = pStream->readUINT32();
    verscode = pStream->readUINT32();
    state = pStream->readUINT32();
    debugMode = pStream->readUINT32();
}

void GetModuleInfoReply::callFailed(UINT32 procID, UINT32 reason) {
    log_Err("Failed sending GetModuleInfoCall. Reason: %x", reason);
}

SINT32 GetModuleInfoReply::getReturnCode()
{
    return this->returncode;
}

int GetModuleInfoReply::getReplySize()
{
    return sizeof(SMI_GETINFO_R);
}
