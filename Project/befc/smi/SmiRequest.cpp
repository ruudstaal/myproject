/**
 ********************************************************************************
 * @file     SmiRequest.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiRequest
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>

#include "mcpp.hpp"
#include "SmiRequest.hpp"

SmiRequest::SmiRequest(UINT32 procId) :
        procId(procId)
{
}

SmiRequest::~SmiRequest()
{
}

void SmiRequest::handleRequest(SMI_MSG* pMsg, SMI_ID* pSmiID)
{
    /** Process incoming data */
    readRequest(pMsg);
    smi_FreeData(pMsg);

    /** Generate and send smi reply */
    SmiStream *pStream = getReply();

    /** Only send a reply if an output stream is available */
    if (pStream)
    {
        /** get the reply size and allocate memory */
        void* pReply = NULL;
        int replySize = pStream->tellp();
        if (!(pReply = smi_MemAlloc(replySize)))
        {
            error("No memory!");
            smi_SendCReply(pSmiID, pMsg, SMI_E_NOMEM, NULL, 0);
            SAFE_DELETE(pStream);
            return;
        }

        /** copy data from stream to allocated memory */
        pStream->read((char*) pReply, replySize);

        /** send the reply */
        smi_SendReply(pSmiID, pMsg, SMI_E_OK, pReply, replySize);
    }
    SAFE_DELETE(pStream);
}

UINT32 SmiRequest::getProcId()
{
    return procId;
}
