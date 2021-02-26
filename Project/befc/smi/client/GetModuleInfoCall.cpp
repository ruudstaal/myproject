/**
 ********************************************************************************
 * @file     GetModuleInfoCall.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of GetModuleInfoCall
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "GetModuleInfoCall.hpp"

GetModuleInfoCall::GetModuleInfoCall(UINT8 *pName) :
        SmiCall(SMI_PROC_GETINFO, "GetModuleInfoCall"), pName(pName)
{
}

UINT32 GetModuleInfoCall::getDataSize()
{
    return M_MODNAMELEN_A;
}

UINT8* GetModuleInfoCall::getData()
{
    return this->pName;
}
