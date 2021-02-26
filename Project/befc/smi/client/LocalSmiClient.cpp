/**
 ********************************************************************************
 * @file     LocalSmiClient.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 9, 2016 8:47:43 AM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <LocalSmiClient.hpp>
#include "SmiException.hpp"


LocalSmiClient::LocalSmiClient(SmiHandler *pSmiHandler) : pSmiHandler(pSmiHandler)
{
}

LocalSmiClient::~LocalSmiClient()
{
}

void LocalSmiClient::connect()
{
    setState(SMIClientEventListener::ONLINE, true);
}

void LocalSmiClient::disconnect()
{
    setState(SMIClientEventListener::OFFLINE, true);
}

void LocalSmiClient::sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener) {
    if (getState() == SMIClientEventListener::ONLINE)
    {
        try
        {
            pSmiHandler->sendCall(module, pCall, pReply, pListener);
        }
        catch (SmiException &ex)
        {
            log_Err("Error sending SMI call with procedure id %d. Reason: %s",
                    pCall->getProcedureId(), ex.what());
            setState(SMIClientEventListener::ERR, true);
        }
    }
    else
    {
        throw SmiException("Could not send SMI call when NOT in ONLINE state");
    }
}

void LocalSmiClient::sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply){
    if (getState() == SMIClientEventListener::ONLINE)
       {
           try
           {
               pSmiHandler->sendCall(module, pCall, pReply, SmiHandler::DEFAULT_CALL_TIMEOUT_INTERNAL);
           }
           catch (SmiException &ex)
           {
               log_Err("Error sending SMI call with procedure id %d. Reason: %s",
                                   pCall->getProcedureId(), ex.what());
               setState(SMIClientEventListener::ERR, true);
           }
       }
       else
       {
           throw SmiException("Could not send SMI call when NOT in ONLINE state");
       }
}
