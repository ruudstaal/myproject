/*
 * SviProcGetValLstReply.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#include "SviProcGetValLstReply.hpp"
#include "mcpp.hpp"

SviProcGetValLstReply::SviProcGetValLstReply() : pValues(NULL), listSize(0), returnCode(0)
{
}

SviProcGetValLstReply::~SviProcGetValLstReply()
{
    if (pValues != NULL){
        SAFE_DELETE(pValues);
    }
}


void SviProcGetValLstReply::readReply(SmiStream *pStream) {
    returnCode = pStream->readSINT32();
    pStream->read((char*)pValues, listSize *4); //
}

SINT32 SviProcGetValLstReply::getReturnCode() {
    return returnCode;
}

int SviProcGetValLstReply::getReplySize() {
    return 4 + (listSize *4);
}

void SviProcGetValLstReply::callFailed(UINT32 reason) {
    returnCode = reason;
}

void SviProcGetValLstReply::setListSize(UINT32 size){
    listSize = size;
    if(pValues != NULL) {
        SAFE_DELETE(pValues);
    }
    pValues = new UINT32[size];
}
