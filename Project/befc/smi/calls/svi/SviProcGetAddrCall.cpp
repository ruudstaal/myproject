/**
 ********************************************************************************
 * @file     SviProcGetAddrCall.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 1:05:11 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include "SviProcGetAddrCall.hpp"
#include <svi.h>
#include "string.h"
#include "mcpp.hpp"

SviProcGetAddrCall::SviProcGetAddrCall() :
    SmiCall(SVI_PROC_GETADDR, "SVI_PROC_GETADDR"),
    m_VarNameLength(0)
{
    m_SVIVarName = new char[MAXVARLENGTH];
}

SviProcGetAddrCall::~SviProcGetAddrCall(){
    SAFE_DELETE(m_SVIVarName);
}

void SviProcGetAddrCall::SetSVIVarName(std::string SVIVarName)
{
    m_VarNameLength = SVIVarName.length() + 1;
    strncpy(m_SVIVarName, SVIVarName.c_str(), MAXVARLENGTH);
}

UINT32 SviProcGetAddrCall::getDataSize()
{
    return(m_VarNameLength);
}

UINT8* SviProcGetAddrCall::getData()
{
    return((UINT8*)m_SVIVarName);
}


