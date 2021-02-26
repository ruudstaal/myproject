/*
 * SviProcSetValReply.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: madsen
 */

#include <svi/SviProcSetValReply.hpp>

SviProcSetValReply::SviProcSetValReply() : ParametrizedObject(),  retCode(0)
{
}

SviProcSetValReply::~SviProcSetValReply()
{
}

void SviProcSetValReply::readReply(SmiStream *pStream){
    this->retCode = pStream->readSINT32();
}

void SviProcSetValReply::callFailed(UINT32 reason){

}

SINT32 SviProcSetValReply::getReturnCode(){
    return this->retCode;
}

int SviProcSetValReply::getReplySize(){
    return sizeof(this->retCode);
}
