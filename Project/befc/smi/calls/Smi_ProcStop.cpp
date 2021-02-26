/**
 ********************************************************************************
 * @file     Smi_ProcStop.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcStop
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcStop.hpp"

Smi_ProcStop::Smi_ProcStop(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_STOP), pModule(pModule), retCode(OK)
{
}

Smi_ProcStop::~Smi_ProcStop()
{
}

void Smi_ProcStop::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: Stop");
    }

    if (pModule->doStop())
    {
        retCode = SMI_E_OK;
    }
    else
    {
        retCode = SMI_E_FAILED;
    }
}

SmiStream* Smi_ProcStop::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    return (pStream);
}
