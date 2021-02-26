/*
 * SviProcSetBlkCall.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: madsen
 */

#include <svi/SviProcSetBlkCall.hpp>
#include "mcpp.hpp"
#include <cstring>

SviProcSetBlkCall::SviProcSetBlkCall() : SmiCall(SVI_PROC_SETBLK, "SVI_PROC_SETBLK"), pPayload(NULL)
{
    this->data.data = NULL;
}

SviProcSetBlkCall::~SviProcSetBlkCall()
{
    SAFE_DELETE(this->data.data);
    SAFE_DELETE(this->pPayload);
}

UINT32 SviProcSetBlkCall::getDataSize() {
    return this->data.buffLength + sizeof(SVI_ADDR) + 4;
}

UINT8* SviProcSetBlkCall::getData() {

    return pPayload;
}

void SviProcSetBlkCall::setSVIAddr(SVI_ADDR address) {
    this->data.addr = address;
}

void SviProcSetBlkCall::setData(UINT8* data, UINT32 length) {
    this->data.buffLength = length;

    if(this->data.data != NULL) {
        SAFE_DELETE(this->data.data);
    }
    this->data.data = new UINT8[length];
    memcpy(this->data.data, data, length);

    if(pPayload != NULL) {
        SAFE_DELETE(pPayload);
    }

    //Need to allocate call in memory in one block, since SMI handler uses memcpy also.
    pPayload = new UINT8[getDataSize()];
    memcpy(pPayload, &this->data.addr, sizeof(this->data.addr));
    memcpy((pPayload + sizeof(this->data.addr)), &this->data.buffLength,
            sizeof(this->data.buffLength));
    memcpy((pPayload + sizeof(this->data.addr) + sizeof(this->data.buffLength)),
            this->data.data, this->data.buffLength);
}
