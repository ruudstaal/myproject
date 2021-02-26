/*
 * SviProcGetValReply.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: madsen
 */

#include <svi/SviProcGetValReply.hpp>
#include "log_e.h"

SviProcGetValReply::SviProcGetValReply() : SmiCallReply(), ParametrizedObject()
{
}

SviProcGetValReply::~SviProcGetValReply()
{
}

SVI_GETVAL_R SviProcGetValReply::getReply() {
    return this->reply;
}

void SviProcGetValReply::readReply(SmiStream *pStream) {
    reply.RetCode = pStream->readSINT32();
    reply.Value = pStream->readUINT32();
}

SINT32 SviProcGetValReply::getReturnCode() {
    return reply.RetCode;
}

int SviProcGetValReply::getReplySize() {
    return(sizeof(SVI_GETVAL_R));
}

void SviProcGetValReply::callFailed(UINT32 reason) {
    reply.RetCode = reason;
}
