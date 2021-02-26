/*
 * SviProcSetBlkReply.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: madsen
 */

#include <svi/SviProcSetBlkReply.hpp>

SviProcSetBlkReply::SviProcSetBlkReply() :
        retCode(0), isMultiBlk(false), bufferId(0)
{
}

SviProcSetBlkReply::~SviProcSetBlkReply()
{
}

void SviProcSetBlkReply::readReply(SmiStream *pStream)
{
    this->retCode = pStream->readSINT32();
    if(this->retCode == SVI_E_MBTRANS) {
        this->isMultiBlk = true;
        this->bufferId = pStream->readUINT32();
    }
}

void SviProcSetBlkReply::callFailed(UINT32 reason)
{
    retCode = reason;
}

SINT32 SviProcSetBlkReply::getReturnCode()
{
    return retCode;
}

int SviProcSetBlkReply::getReplySize()
{
    if(retCode == SVI_E_MBTRANS) {
        return sizeof(SVI_SETXBLK_R);
    }
    else {
        return sizeof(SVI_SETBLK_R);
    }

}

