/*
 * SviProcGetXAddrCall.cpp
 *
 *  Created on: May 21, 2019
 *      Author: madsen
 */

#include <svi/SviProcGetXAddrCall.hpp>
#include "SviProcGetAddrCall.hpp"
#include <svi.h>
#include "string.h"
#include "mcpp.hpp"

SviProcGetXAddrCall::SviProcGetXAddrCall() :
    SmiCall(SVI_PROC_GETXADDR, "SVI_PROC_GETXADDR"),
    m_VarNameLength(0)
{
    m_SVIVarName = new char[MAXVARLENGTH];
}

SviProcGetXAddrCall::~SviProcGetXAddrCall(){
    SAFE_DELETE(m_SVIVarName);
}

void SviProcGetXAddrCall::SetSVIVarName(std::string SVIVarName)
{
    m_VarNameLength = SVIVarName.length() + 1;
    strncpy(m_SVIVarName, SVIVarName.c_str(), MAXVARLENGTH);
}

UINT32 SviProcGetXAddrCall::getDataSize()
{
    return(m_VarNameLength);
}

UINT8* SviProcGetXAddrCall::getData()
{
    return((UINT8*)m_SVIVarName);
}
