/**
 ********************************************************************************
 * @file     LocalSmiClient.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 9, 2016 8:47:42 AM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_LOCALSMICLIENT_HPP_
#define BEFC_SMI_CLIENT_LOCALSMICLIENT_HPP_

#include "BaseSMIClient.hpp"
#include "SmiHandler.hpp"

class LocalSmiClient: public BaseSMIClient
{
public:
    LocalSmiClient(SmiHandler *pSmiHandler);

    void connect();

    void disconnect();

    void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener);

    void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply);

    virtual ~LocalSmiClient();

private:
    SmiHandler *pSmiHandler;
};

#endif /* BEFC_SMI_CLIENT_LOCALSMICLIENT_HPP_ */
