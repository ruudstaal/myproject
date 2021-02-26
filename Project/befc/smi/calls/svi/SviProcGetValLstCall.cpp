/*
 * SviProcGetValLstCall.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#include "SviProcGetValLstCall.hpp"
#include "SmiException.hpp"
#include "mcpp.hpp"
#include <cstring>

SviProcGetValLstCall::SviProcGetValLstCall() : SmiCall(SVI_PROC_GETVALLST, "SVI_PROC_GETVALLST")
{
    call.ListLen = 0;
}

SviProcGetValLstCall::~SviProcGetValLstCall()
{
}

UINT32 SviProcGetValLstCall::getDataSize()
{
    return 4 + (call.ListLen * sizeof(SVI_ADDR));
}

UINT8* SviProcGetValLstCall::getData()
{
    return (UINT8*)&call;
}

void SviProcGetValLstCall::setAddresses(SVI_ADDR *pList, UINT32 size) {
    if(size > GETVALLST_MAXITEMSINCALL) {
        throw SmiException("Only 64 SVI values is allowed at each call SVI_PROC_GETVALLST call ");
    }
    call.ListLen = size;
    memcpy(&call.addr, pList, size * sizeof(SVI_ADDR));
}
