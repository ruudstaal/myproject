/**
********************************************************************************
* @file     SMIClientEventListener.hpp
* @author   madsen
* @version  $Revision: 000 $ $LastChangedBy: XXXX $
* @date     $LastChangeDate: Sep 16, 2016 10:49:37 AM 11:00:00 $
*
* @brief
*
********************************************************************************
* COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
*******************************************************************************/

#ifndef BEFC_SMI_CLIENT_SMICLIENTEVENTLISTENER_HPP_
#define BEFC_SMI_CLIENT_SMICLIENTEVENTLISTENER_HPP_

/**
 * Interface for listening to SMI client states
 */
class SMIClientEventListener
{
public:

    enum ClientState {DISCONNECTING = 2, ONLINE = 1, OFFLINE = 0, LOGIN_FAILED = -1, BAD_LOGIN = -2, TIMEOUT = -3, ERR = -10};

    SMIClientEventListener(){};

    virtual void eventRecieved(ClientState state) = 0;

    virtual ~SMIClientEventListener(){};
};


#endif /* BEFC_SMI_CLIENT_SMICLIENTEVENTLISTENER_HPP_ */
