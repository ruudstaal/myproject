/**
 ********************************************************************************
 * @file     Smi_ProcGetInfo.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcGetInfo
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "BEModule.hpp"
#include "Smi_ProcGetInfo.hpp"

Smi_ProcGetInfo::Smi_ProcGetInfo(BEModule *pModule) :
        StreamedSmiRequest(SMI_PROC_GETINFO), pModule(pModule), retCode(OK)
{
}

Smi_ProcGetInfo::~Smi_ProcGetInfo()
{
}

void Smi_ProcGetInfo::readRequest(SmiStream *pStream)
{
    if (pModule->getDebugMode() == APP_DBG_SMI1)
    {
        info("Smi request: GetInfo");
    }
}

SmiStream* Smi_ProcGetInfo::getReply(void)
{
    SmiStream *pStream = new SmiStream();

    /** write module name and comment to stream */
    pStream->write((SINT32) SMI_E_OK); /**< Return Code */
    pStream->write(pModule->getAppName(), M_MODNAMELEN_A); /**< Name of module instance */
    pStream->write(pModule->getDescription(), SMI_DESCLEN_A); /**< Deccription of module */
    pStream->write((UINT32) pModule->getVersion().getType()); /**< Version type; M_VER_ALPHA,.. */
    pStream->write(pModule->getVersion().getMajor()); /**< Major version code */
    pStream->write(pModule->getVersion().getMinor()); /**< Minor version code */
    pStream->write(pModule->getVersion().getRevision()); /**< Revision version code */
    pStream->write((UINT32) pModule->getModState().getResState()); /**< Status of module; possible is RES_S_RUN, RES_S_ERROR, ... */
    pStream->write(pModule->getDebugMode()); /**< Bit image of debug mode */

    return (pStream);
}
