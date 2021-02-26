/*
 * ResProcLogoutCall.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: madsen
 */

#include <ResProcLogoutCall.hpp>
#include <cstring>

ResProcLogoutCall::ResProcLogoutCall() : SmiCall(RES_PROC_LOGOUT, "RES_PROC_LOGOUT")
{
    call.Parm = 0;
}

ResProcLogoutCall::~ResProcLogoutCall()
{
}

UINT32 ResProcLogoutCall::getDataSize() {
    return sizeof(call);
}

void ResProcLogoutCall::setAuthentData(UINT8 data[128]) {
    memcpy(call.Authent, data, 128);
}

void ResProcLogoutCall::setAuthentDataFromVector(std::vector<CHAR8> data) {
    memcpy(call.Authent, data.data(), 128);
}

UINT8* ResProcLogoutCall::getData() {
    return (UINT8*)&call;
}
