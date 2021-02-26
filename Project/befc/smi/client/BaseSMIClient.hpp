/**
 ********************************************************************************
 * @file     BaseSMIClient.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 16, 2016 10:47:18 AM 11:00:00 $
 *
 * @brief    This class is a base SMI client class, which provides the options for
 *           adding listeners to client events.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_BASESMICLIENT_HPP_
#define BEFC_SMI_CLIENT_BASESMICLIENT_HPP_

#include <SmiClient.hpp>
#include "SMIClientEventListener.hpp"
#include <vector>

/**
 *
 */
class BaseSMIClient: public SmiClient
{
public:
    BaseSMIClient();

    void addEventListener(SMIClientEventListener *pListener);

    void removeEventListener(SMIClientEventListener *pListener);

    virtual void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener) = 0;

    virtual void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply) = 0;

    virtual ~BaseSMIClient();

    SMIClientEventListener::ClientState getState(){ return this->state; }

protected:
    void notifyListeners(SMIClientEventListener::ClientState state);

    void setState(SMIClientEventListener::ClientState state, bool notify);

private:
    SMIClientEventListener::ClientState state;

    std::vector<SMIClientEventListener*> *m_pListeners;
};

#endif /* BEFC_SMI_CLIENT_BASESMICLIENT_HPP_ */
