/*
 * SviProcGetValCall.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: madsen
 */

#include <svi/SviProcGetValCall.hpp>

SviProcGetValCall::SviProcGetValCall() : SmiCall(SVI_PROC_GETVAL, "SVI_PROC_GETVAL")
{
}

SviProcGetValCall::~SviProcGetValCall()
{
}

void SviProcGetValCall::setAddr(SVI_ADDR address) {
    this->addr = address;
}

SVI_ADDR SviProcGetValCall::getAddr() {
    return this->addr;
}

UINT32 SviProcGetValCall::getDataSize()
{
    return(sizeof(this->addr));
}

UINT8* SviProcGetValCall::getData()
{
    return((UINT8*)&this->addr);
}
