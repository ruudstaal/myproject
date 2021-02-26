/*
 * ResProcSysInfoCall.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: madsen
 */

#include <ResProcSysInfoCall.hpp>
#include "string.h"

ResProcSysInfoCall::ResProcSysInfoCall() : SmiCall(RES_PROC_SYSINFO, "RES_PROC_SYSINFO")
{
    data.Parm = 0;
    data.MainVers = 0;
    data.SubVers = 0;
    strncpy (data.ToolName,"CPP", sizeof(data.ToolName));
}

ResProcSysInfoCall::~ResProcSysInfoCall()
{
}

UINT32 ResProcSysInfoCall::getDataSize() {
    return sizeof(data);
}

UINT8*ResProcSysInfoCall::getData() {
    return (UINT8*)&data;
}
