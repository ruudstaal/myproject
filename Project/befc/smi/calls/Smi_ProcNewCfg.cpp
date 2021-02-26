/**
 ********************************************************************************
 * @file     Smi_ProcNewCfg.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcNewCfg
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcNewCfg.hpp"

Smi_ProcNewCfg::Smi_ProcNewCfg(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_NEWCFG), pModule(pModule), retCode(OK)
{
}

Smi_ProcNewCfg::~Smi_ProcNewCfg()
{
}

void Smi_ProcNewCfg::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: NewCfg");
    }

    if (!pModule->doNewCfg())
    {
        retCode = SMI_E_OK;
    }
    else
    {
        retCode = SMI_E_FAILED;
    }
}

SmiStream* Smi_ProcNewCfg::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write(retCode);

    return (pStream);
}
