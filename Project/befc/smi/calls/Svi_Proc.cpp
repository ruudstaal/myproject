/**
 ********************************************************************************
 * @file     Smi_Proc.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_Proc
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>

#include "mcpp.hpp"
#include "Svi_Proc.hpp"

Svi_Proc::Svi_Proc(SviServer* pSviServer, UINT32 procNb) :
        SmiRequest(procNb), pSviServer(pSviServer)
{
}

Svi_Proc::~Svi_Proc()
{
}

void Svi_Proc::readRequest(SMI_MSG* pMsg)
{
    pSviServer->handleSmiMessage(pMsg);
}

SmiStream* Svi_Proc::getReply(void)
{
    /** no reply is required for SVI, returning NULL */
    return (NULL);
}
