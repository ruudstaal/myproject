/*
 * SviProcSetValLstReply.cpp
 *
 *  Created on: Mar 23, 2018
 *      Author: madsen
 */

#include "SviProcSetValLstReply.hpp"

SviProcSetValLstReply::SviProcSetValLstReply() : returnCode(0)
{
}

SviProcSetValLstReply::~SviProcSetValLstReply()
{
}

void SviProcSetValLstReply::readReply(SmiStream *pStream) {
    returnCode = pStream->readSINT32();
}


void SviProcSetValLstReply::callFailed(UINT32 reason) {
    returnCode = reason;
}


SINT32 SviProcSetValLstReply::getReturnCode() {
    return returnCode;
}

int SviProcSetValLstReply::getReplySize() {
    return 4;
}
