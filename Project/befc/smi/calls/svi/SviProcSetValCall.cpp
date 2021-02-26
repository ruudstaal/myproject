/*
 * SviProcSetValCall.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: madsen
 */

#include <svi/SviProcSetValCall.hpp>

SviProcSetValCall::SviProcSetValCall() : SmiCall(SVI_PROC_SETVAL, "SVI_PROC_SETVAL")
{
}

SviProcSetValCall::~SviProcSetValCall()
{
}

UINT32 SviProcSetValCall::getDataSize() {
    return sizeof(SVI_SETVAL_C);
}

UINT8* SviProcSetValCall::getData() {
    return (UINT8*)&call;
}

void SviProcSetValCall::setSVIAddr(SVI_ADDR address) {
    this->call.Addr = address;
}

void SviProcSetValCall::setValue(UINT32 value) {
    this->call.Value = value;
}

UINT32 SviProcSetValCall::getValue() {
    return this->call.Value;
}
