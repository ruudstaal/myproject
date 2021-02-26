/**
 ********************************************************************************
 * @file     ResProcModNBCall.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 1, 2016 1:53:54 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <ResProcModNBCall.hpp>
#include "string.h"


ResProcModNBCall::ResProcModNBCall() :
    SmiCall(RES_PROC_MODNB, "RES_PROC_MODNB")
{
    memset(m_data.AppName, 0, sizeof(m_data.AppName));
}

ResProcModNBCall::~ResProcModNBCall()
{
}

void ResProcModNBCall::setModuleName(std::string moduleName) {
    strncpy(m_data.AppName, moduleName.c_str(), sizeof(m_data.AppName));
}

UINT32 ResProcModNBCall::getDataSize()
{
    return(sizeof(m_data));
}

UINT8* ResProcModNBCall::getData()
{
    return((UINT8*)&m_data);
}
