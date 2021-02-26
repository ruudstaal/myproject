/**
 ********************************************************************************
 * @file     Smi_ProcEndOfInit.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcEndOfInit
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcEndOfInit.hpp"

Smi_ProcEndOfInit::Smi_ProcEndOfInit(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_ENDOFINIT), pModule(pModule), retCode(OK)
{
}

Smi_ProcEndOfInit::~Smi_ProcEndOfInit()
{
}

void Smi_ProcEndOfInit::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: EndOfInit");
    }

    if (pModule->doEndOfInit())
    {
        retCode = SMI_E_OK;
    }
    else
    {
        retCode = SMI_E_FAILED;
    }
}

SmiStream* Smi_ProcEndOfInit::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    return (pStream);
}
