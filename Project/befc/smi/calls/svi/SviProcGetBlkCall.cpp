/*
 * SviProcGetBlkCall.cpp
 *
 *  Created on: Mar 13, 2017
 *      Author: madsen
 */

#include <svi/SviProcGetBlkCall.hpp>

SviProcGetBlkCall::SviProcGetBlkCall() : SmiCall(SVI_PROC_GETBLK, "SVI_PROC_GETBLK")
{
}

SviProcGetBlkCall::~SviProcGetBlkCall()
{
}

void SviProcGetBlkCall::setAddr(SVI_ADDR address) {
    this->data.Addr = address;
}

SVI_ADDR SviProcGetBlkCall::getAddr() {
    return this->data.Addr;
}

UINT32 SviProcGetBlkCall::getLength() {
    return this->data.BuffLen;
}

void SviProcGetBlkCall::setLength(UINT32 length) {
    this->data.BuffLen = length;
}


UINT32 SviProcGetBlkCall::getDataSize() {
    return sizeof(this->data);
}

UINT8* SviProcGetBlkCall::getData() {
    return (UINT8*)&this->data;
}
