/**
 ********************************************************************************
 * @file     Smi_ProcDeinit.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcDeinit
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "SmiHandler.hpp"
#include "Smi_ProcDeinit.hpp"

Smi_ProcDeinit::Smi_ProcDeinit(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_DEINIT), pModule(pModule), retCode(OK)
{
}

Smi_ProcDeinit::~Smi_ProcDeinit()
{
}

void Smi_ProcDeinit::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: DeInit");
    }

    if (pModule->doDeinit())
    {
        retCode = SMI_E_OK;
    }
    else
    {
        /** Deinstallation failed. */
        retCode = SMI_E_FAILED;
    }
}

SmiStream* Smi_ProcDeinit::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    pModule->getSmiHandler()->terminate();

    return (pStream);
}
