/**
 ********************************************************************************
 * @file     StreamedSmiRequest.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StreamedSmiRequest
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <smi_e.h>
#include "mcpp.hpp"
#include "StreamedSmiRequest.hpp"
#include "SmiStream.hpp"

StreamedSmiRequest::StreamedSmiRequest(UINT32 procId) :
        SmiRequest(procId)
{
}

StreamedSmiRequest::~StreamedSmiRequest()
{
}

void StreamedSmiRequest::readRequest(SMI_MSG* pMsg)
{
    SmiStream *pStream = new SmiStream(pMsg);
    readRequest(pStream);
    SAFE_DELETE(pStream);
}
