/*
 * SviProcGetBlkReply.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: madsen
 */

#include <svi/SviProcGetBlkReply.hpp>
#include "mcpp.hpp"

SviProcGetBlkReply::SviProcGetBlkReply() :returnCode(0), dataLength(0), data(NULL), isMultiBlk(false), bufferId(0), bufferlength(0){
}

SviProcGetBlkReply::~SviProcGetBlkReply(){
    SAFE_DELETE(data);
}

void SviProcGetBlkReply::readReply(SmiStream *pStream){

    this->returnCode = pStream->readSINT32();
    if(returnCode == SVI_E_OK) {
        this->dataLength = pStream->readUINT32();
        SAFE_DELETE(data);
        data = new UINT8[dataLength];
        pStream->read((char*)data, dataLength);
    }
    else if (returnCode == SVI_E_MBTRANS) {
        bufferlength = pStream->readUINT32();
        bufferId = pStream->readUINT32();
    }
}

void SviProcGetBlkReply::callFailed(UINT32 reason){
    this->returnCode = reason;
}

SINT32 SviProcGetBlkReply::getReturnCode(){
    return this->returnCode;
}

UINT32 SviProcGetBlkReply::getDataLength() {
    return this->dataLength;
}

int SviProcGetBlkReply::getReplySize(){
    if(returnCode == SVI_E_OK) {
        return 4 + 4 + dataLength; //4 bytes from the returncode
    }
    else {
        return sizeof(SVI_GETXBLK_R);
    }
}

UINT8* SviProcGetBlkReply::getData(){
    return this->data;
}
