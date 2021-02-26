/*
 * SviProcSetValLstCall.cpp
 *
 *  Created on: Mar 22, 2018
 *      Author: madsen
 */

#include "SviProcSetValLstCall.hpp"
#include "mcpp.hpp"
#include "SmiStream.hpp"
#include "SmiException.hpp"
#include <cstring>

SviProcSetValLstCall::SviProcSetValLstCall() : SmiCall(SVI_PROC_SETVALLST, "SVI_PROC_SETVALLST")
{
    UINT32 size = 4 + (SETVALLST_MAXITEMSINCALL * sizeof(SVI_ADDR)) + (SETVALLST_MAXITEMSINCALL * sizeof(UINT32));
    data = new UINT8[size];
    memset(data,0, size);
    dataLength = 0;
}

SviProcSetValLstCall::~SviProcSetValLstCall()
{
    SAFE_DELETE(data);
}

UINT32 SviProcSetValLstCall::getDataSize() {
    return dataLength;
}

UINT8* SviProcSetValLstCall::getData() {
    return data;
}


void SviProcSetValLstCall::setValues(SVI_ADDR *pAddrList, UINT32 *pValues, UINT32 length) {
    if(length > SETVALLST_MAXITEMSINCALL) {
        throw SmiException("Only 64 SVI values is allowed at each call SVI_PROC_GETVALLST call ");
    }
    dataLength = 4 + (length * sizeof(SVI_ADDR)) + (length * sizeof(UINT32));
    memcpy(data, &length, 4); //copy the value of length
    memcpy(&data[4], pAddrList, length * sizeof(SVI_ADDR)); //Copy the svi addresses
    memcpy(&data[4 + (length * sizeof(SVI_ADDR))], pValues, length * sizeof(UINT32)); //Copy the values
}
