/**
 ********************************************************************************
 * @file     SmiClient.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 8, 2016 1:17:18 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_SMICLIENT_HPP_
#define BEFC_SMI_CLIENT_SMICLIENT_HPP_

#include <string>
#include "SmiReplyListener.hpp"
#include "SmiCall.hpp"
#include "SmiCallReply.hpp"
#include "SMIClientEventListener.hpp"

class SmiClient
{
public:

    virtual void connect() = 0;

    virtual void disconnect() = 0;

    virtual void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener) = 0;

    virtual void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply) = 0;

    virtual void addEventListener(SMIClientEventListener *pListener) = 0;

    virtual void removeEventListener(SMIClientEventListener *pListener) = 0;

    virtual ~SmiClient(){};

protected:
    SmiClient(){};
private:
};

#endif /* BEFC_SMI_CLIENT_SMICLIENT_HPP_ */
