/**
 ********************************************************************************
 * @file     Smi_ProcSetDbg.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcSetDbg
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcSetDbg.hpp"

Smi_ProcSetDbg::Smi_ProcSetDbg(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_SETDBG), pModule(pModule)
{
}

Smi_ProcSetDbg::~Smi_ProcSetDbg()
{
}

void Smi_ProcSetDbg::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: SetDbg");
    }
    pStream->readString(M_MODNAMELEN_A);

    pModule->setDebugMode(pStream->readUINT32()); /** Read debug level */
}

SmiStream* Smi_ProcSetDbg::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write error code to reply */
    pStream->write((SINT32) SMI_E_OK);

    return (pStream);
}
