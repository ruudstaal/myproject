/**
 ********************************************************************************
 * @file     Smi_ProcReset.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcReset
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcReset.hpp"

Smi_ProcReset::Smi_ProcReset(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_RESET), pModule(pModule), retCode(OK)
{
}

Smi_ProcReset::~Smi_ProcReset()
{
}

void Smi_ProcReset::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: Reset");
    }
}

SmiStream* Smi_ProcReset::getReply(void)
{
    retCode = SMI_E_OK;

    /** Deinit application */
    if (pModule->doReset())
    {
        /** Reset successfully done */
        retCode = SMI_E_OK;
    }
    else
    {
        retCode = SMI_E_FAILED;
    }

    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    return (pStream);
}
