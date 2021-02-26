/*
 * ResProcSysInfoReply.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: madsen
 */

#include <ResProcSysInfoReply.hpp>
#include "string.h"

ResProcSysInfoReply::ResProcSysInfoReply()
{
    memset(&reply, 0, sizeof(reply));
}

ResProcSysInfoReply::~ResProcSysInfoReply()
{
}

void ResProcSysInfoReply::readReply(SmiStream *pStream)
{
    pStream->read((char*)&reply, sizeof(reply));
}

void ResProcSysInfoReply::callFailed(UINT32 reason)
{
    reply.RetCode = reason;
}

int ResProcSysInfoReply::getReplySize()
{
    return sizeof(reply);
}

SINT32 ResProcSysInfoReply::getReturnCode()
{
    return reply.RetCode;
}
