/**
 ********************************************************************************
 * @file     RemoteSmiClient.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 9, 2016 9:03:53 AM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_REMOTESMICLIENT_HPP_
#define BEFC_SMI_CLIENT_REMOTESMICLIENT_HPP_

#include "BaseSMIClient.hpp"
#include "SmiReplyListener.hpp"
#include "SmiHandler.hpp"
#include "ResProcLoginCall.hpp"
#include "ResProcLoginReply.hpp"
#include "ResProcModNBCall.hpp"
#include "ResProcModNBReply.hpp"
#include "ResProcLogoutCall.hpp"
#include "ResProcLogoutReply.hpp"

class RemoteSmiClient: public BaseSMIClient, public SmiReplyListener, public SmiHandlerErrorListener
{
public:
    RemoteSmiClient(SmiHandler *pSmiHandler, std::string ip, std::string username, std::string password);

    RemoteSmiClient(SmiHandler *pSmiHandler, std::string ip, std::string username, std::string password, std::string toolName);

    void connect();

    void disconnect();

    bool isConnected();

    void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener);

    void sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply);

protected:
    void replyRecieved(SmiCallReply *pReply, UINT32 procID);

    void callFailed(UINT32 procID, SINT32 reason) {};

    void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason);

    void systemFailureRecieved(SINT32 failure, SmiHandler *pInstance);

    struct queuedCall{
        std::string module;
        SmiCall *pCall;
        SmiCallReply *pReply;
        SmiReplyListener *pListener;
    };

private:

    SmiHandler *pSmiHandler;
    std::string ip;
    std::string username;
    std::string password;

    //Client needs modulenumbers for each module which should be sent
    //calls to. They will be cached to optimize performance.
    std::map<std::string, UINT32> moduleNbrMap;
    std::vector<std::string> nonExistingModules;

    //Queued calls due to retrieval of module number
    std::vector<queuedCall> queuedCalls;
    bool checkQueueAgain;
    bool checkingQueue;
    SEM_ID semMutex;

    // Calls needed for communication regarding modulenumber and login
    ResProcLoginCall loginCall;
    ResProcLoginReply loginReply;
    ResProcModNBCall modNBCall;
    ResProcModNBReply modNBReply;
    ResProcLogoutCall logoutCall;
    ResProcLogoutReply logoutReply;


    virtual ~RemoteSmiClient();

    UINT32 getModuleNumber(std::string moduleName);

    BOOL8 hasModuleNumber(std::string moduleName);

    void putToQueue(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener);

    void checkQueue();

    void requestModuleNumber(std::string moduleName);

    bool isModuleNotPresent(std::string moduleName);
};

#endif /* BEFC_SMI_CLIENT_REMOTESMICLIENT_HPP_ */
