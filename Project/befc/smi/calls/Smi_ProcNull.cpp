/**
 ********************************************************************************
 * @file     Smi_ProcNull.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcNull
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "Smi_ProcNull.hpp"

Smi_ProcNull::Smi_ProcNull() :
        StreamedSmiRequest(SMI_PROC_NULL)
{
}

Smi_ProcNull::~Smi_ProcNull()
{
}

void Smi_ProcNull::readRequest(SmiStream *pStream)
{
}

SmiStream* Smi_ProcNull::getReply(void)
{
    return (NULL);
}
