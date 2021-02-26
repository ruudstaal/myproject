/*
 * ResProcLogoutReply.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: madsen
 */

#include <ResProcLogoutReply.hpp>

ResProcLogoutReply::ResProcLogoutReply() : SmiCallReply()
{
    reply.RetCode = 0;
    reply.Spare1 = 0;
    reply.Spare2 = 0;
}


ResProcLogoutReply::~ResProcLogoutReply()
{
}

void ResProcLogoutReply::readReply(SmiStream *pStream){
    reply.RetCode = pStream->readSINT32();
    reply.Spare1 = pStream->readUINT32();
    reply.Spare2 = pStream->readUINT32();
}

void ResProcLogoutReply::callFailed(UINT32 reason) {
}

SINT32 ResProcLogoutReply::getReturnCode() {
    return reply.RetCode;
}

int ResProcLogoutReply::getReplySize() {
    return sizeof(reply);
}
