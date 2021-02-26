/**
 ********************************************************************************
 * @file     ResProcLoginCall.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 30, 2016 1:41:56 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include "ResProcLoginCall.hpp"
#include "string.h"

ResProcLoginCall::ResProcLoginCall(std::string Username, std::string Password, UINT32 UserParm, UINT32 LoginSessId, std::string toolName) :
    SmiCall(RES_PROC_LOGIN2, "RES_PROC_LOGIN2")
{
    m_data = (RES_LOGIN2_C) {0};

    m_data.UserParm = UserParm;
    m_data.MainVers = 0;
    m_data.SubVers = 0;
    m_data.Local = FALSE;
    strncpy(m_data.UserName, Username.c_str(), sizeof(m_data.UserName));
    strncpy((CHAR8 *)m_data.Password, Password.c_str(), sizeof(m_data.Password));
    strncpy(m_data.ToolName, toolName.c_str(), toolName.size() >= M_MODNAMELEN_A ? M_MODNAMELEN_A : toolName.size());
}

UINT32 ResProcLoginCall::getDataSize()
{
    return(sizeof(m_data));
}

UINT8* ResProcLoginCall::getData()
{
    return((UINT8*)&m_data);
}
