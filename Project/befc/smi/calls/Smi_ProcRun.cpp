/**
 ********************************************************************************
 * @file     Smi_ProcRun.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcRun
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcRun.hpp"

Smi_ProcRun::Smi_ProcRun(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_RUN), pModule(pModule), retCode(OK)
{
}

Smi_ProcRun::~Smi_ProcRun()
{
}

void Smi_ProcRun::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: Run");
    }

    if (pModule->doRun())
    {
        retCode = SMI_E_OK;
    }
    else
    {
        retCode = SMI_E_FAILED;
    }
}

SmiStream* Smi_ProcRun::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    return (pStream);
}
