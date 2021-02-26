/**
 ********************************************************************************
 * @file     SmiHandler.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiHandler
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMIHANDLER_HPP_
#define SMIHANDLER_HPP_

/** Includes */
#include "SviServer.hpp"
#include "client/SmiCallReply.hpp"
#include "SmiReplyWrapper.hpp"
#include "SmiClient.hpp"
#include "SmiHandlerErrorListener.hpp"
/**
 * @addtogroup SMI
 * @{
 */

typedef std::map<UINT16, SmiReplyWrapper> TXidReplyMap;
typedef std::pair<UINT16, SmiReplyWrapper> TXidReplyPair;

class ListenerProcIDPair{
public:
    ListenerProcIDPair(SmiReplyListener* pListener, UINT32 proc_id) : pListener(pListener), proc_id(proc_id){}
    SmiReplyListener* pListener;
    UINT32 proc_id;

};

class SmiHandler: public BETask
{
public:

    const static UINT32 DEFAULT_CALL_TIMEOUT_INTERNAL = 1; //Defined in seconds

    const static UINT32 DEFAULT_CALL_TIMEOUT_EXTERNAL = 3; //Defined in seconds

    /**
     ********************************************************************************
     * @brief      Create an instance of SmiHandler
     *
     * @param[in]  conf     The configuration of the SMI task
     *******************************************************************************/
    explicit SmiHandler(BETaskConfiguration conf);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi handler.
     *******************************************************************************/
    ~SmiHandler();

    /**
     ********************************************************************************
     * @brief     Register SMI request with SMI handler.
     *
     *            A check is done to ensure that duplicates of the same proc Id are
     *            not registered.
     *
     * @param[in]  pRequest         Pointer to SMI request to register
     * @retval     true             Request successfully registered
     * @retval     false            Registration of request failed, due to duplicate
     *******************************************************************************/
    bool registerSmiRequest(SmiRequest *pRequest);

    /**
     ********************************************************************************
     * @brief     UnRegister SMI request with SMI handler.
     *
     * @param[in]  pRequest         Pointer to SMI request to unregister
     *******************************************************************************/
    void unregisterSmiRequest(SmiRequest *pRequest);

    /**
     ********************************************************************************
     * @brief     Register a list of SMI requests with SMI handler.
     *
     *            If duplicated are detected, a warning is posted.
     *
     * @param[in]  pLocalList       Pointer to vector of SMI request to register
     *******************************************************************************/
    void registerSmiRequest(std::vector<SmiRequest*> *pLocalList);

    /**
     ********************************************************************************
     * @brief     UnRegister a list of SMI requests with SMI handler.
     *
     * @param[in]  pLocalList     Pointer to vector SMI requests to unregister
     *******************************************************************************/
    void unregisterSmiRequest(std::vector<SmiRequest*> *pLocalList);

    /**
     ********************************************************************************
     * @brief      Send SMI call
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  moduleName       The name of the reciever module
     * @param[in]  pCall            Pointer to the call to be sent
     * @param[in]  pReply           Pointer to the reply which should parse the response
     * @param[in]  timeout          Timeout value in ms. To wait for response.
     *
     * @throws     SmiException     If somethings goes wrong during the call.
     *******************************************************************************/
    void sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout);

    void sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener);


    /**
     ********************************************************************************
     * @brief      Send SMI call to remote controller
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  remoteIP         IP address of the receiver controller
     * @param[in]  remoteModNb      Module number on receiver controller
     * @param[in]  pCall            Pointer to the call to be sent
     * @param[in]  pReply           Pointer to the reply which should parse the response
     * @param[in]  timeout          Timeout value in ms. To wait for response.
     *
     * @throws     SmiException     If some things goes wrong during the call.
     *******************************************************************************/
    void sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout);

    /**
     ********************************************************************************
     * @brief      Send SMI call to remote controller
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  remoteIP         IP address of the receiver controller
     * @param[in]  remoteModNb      Module number on receiver controller
     * @param[in]  pCall            Pointer to the call to be sent
     * @param[in]  pReply           Pointer to the reply which should parse the response
     * @param[in]  timeout          Timeout value in ms. To wait for response.
     * @param[in]  pListener        A listener to be notified when call is done (or failed)
     *
     * @throws     SmiException     If some things goes wrong during the call.
     *******************************************************************************/
    void sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply,
            UINT32 timeout, SmiReplyListener *pListener);

    /**
     ********************************************************************************
     * @brief      Send SMI call to remote controller
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  remoteIP         IP address of the receiver controller
     * @param[in]  remoteModNb      Module number on receiver controller
     * @param[in]  pCall            Pointer to the call to be sent
     * @param[in]  pReply           Pointer to the reply which should parse the response
     * @param[in]  timeout          Timeout value in ms. To wait for response.
     * @param[in]  authentication   Authentification bytes.
     *
     * @throws     SmiException     If some things goes wrong during the call.
     *******************************************************************************/
    void sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply,
            UINT32 timeout, std::vector<CHAR8> authentication);

    /**
     ********************************************************************************
     * @brief      Send SMI call to remote controller
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  remoteIP         IP address of the receiver controller
     * @param[in]  remoteModNb      Module number on receiver controller
     * @param[in]  pCall            Pointer to the call to be sent
     * @param[in]  pReply           Pointer to the reply which should parse the response
     * @param[in]  timeout          Timeout value in ms. To wait for response.
     * @param[in]  authentication   Authentification bytes.
     * @param[in]  pListener        A listener to be notified when call is done (or failed)
     *
     * @throws     SmiException     If some things goes wrong during the call.
     *******************************************************************************/
    void sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply,
            UINT32 timeout, std::vector<CHAR8> authentication, SmiReplyListener *pListener);

    /**
     ********************************************************************************
     * @brief      Send SMI reply
     *
     *             The generated reply stream is send as SMI reply. If memory cannot
     *             be allocated, an error reply is send.
     *
     * @param[in]  pStream          Pointer to reply SMI stream
     * @param[in]  pMsg             Pointer to received SMI message
     * @param[in]  pSmiID           Pointer to smi id for SW module
     *******************************************************************************/
    void sendReply(SmiStream *pStream, SMI_MSG* pMsg, SMI_ID* pSmiID);

    /**
     ********************************************************************************
     * @brief     This method is the message handling loop for SMI calls.
     *******************************************************************************/
    void cycleWork(void);

    /**
     ********************************************************************************
     * @brief     This method recieves the incomming SMI request, or timeout every
     * 			  second to check for SMI replies.
     *******************************************************************************/
    void doEventDelay(void);

    /**
     ********************************************************************************
     * @brief     Implement an empty function of doTerminate
     *******************************************************************************/
    void doTerminate(void){};

    /**
     ********************************************************************************
     * @brief      Delete the BEModule when all task is terminated
     *******************************************************************************/
    void terminated(void);

    /**
     ********************************************************************************
     * @brief      Get user session ID
     *
     * @retval     User session ID
     *******************************************************************************/
    const UINT32 getUserSessionId(void);

    /**
     ********************************************************************************
     * @brief     Initialize SMI interface for smi handler.
     *
     *            Register general SMI procedures.
     *******************************************************************************/
    VOID initSmi(VOID);

    /**
     ********************************************************************************
     * @brief     Initialize SVI server.
     *******************************************************************************/
    VOID initSvi(VOID);

    /**
     ********************************************************************************
     * @brief     DeInitialize SMI interface for smi handler.
     *
     *            Unregister all SMI procedures specific for this SW-module.
     *******************************************************************************/
    VOID deInitSmi(VOID);

    /**
     ********************************************************************************
     * @brief     DeInitialize SVI server.
     *******************************************************************************/
    VOID deInitSvi(VOID);

    /**
     ********************************************************************************
     * @brief      Create a SMI client to send SMI calls to a SW module on a remote
     *             controller
     *
     * @param[in]  ip                 Ip address for the remote controller
     * @param[in]  username           Username for login to remote controller
     * @param[in]  password           Password for login to remote controller
     * @param[in]  password           Toolname to be logged at login on remote controller
     *******************************************************************************/
    SmiClient* createClient(std::string ip, std::string username, std::string password, std::string toolName);

    /**
     ********************************************************************************
     * @brief      Create a SMI client to send SMI calls to a SW module on a remote
     *             controller
     *
     * @param[in]  ip                 Ip address for the remote controller
     * @param[in]  username           Username for login to remote controller
     * @param[in]  password           Password for login to remote controller
     *******************************************************************************/
    SmiClient* createClient(std::string ip, std::string username, std::string password);

    /**
     ********************************************************************************
     * @brief      Create a SMI client to send SMI calls to a local SW module. On same M1 controller
     *             as where the SW is deployed
     *******************************************************************************/
    SmiClient* createClient();

    /**
     ********************************************************************************
     * @brief      Add listener to get errors related to the SMI handler
     *
     * @param[in]  pListener           The listener
     *******************************************************************************/
    void addErrorListener(SmiHandlerErrorListener *pListener);

private:

    /**
     ********************************************************************************
     * @brief      Inits the SmiHandler
     *
     * @param[in]  pModule     A BEModule pointer
     *******************************************************************************/
    void initInternal(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief      Process an incoming SMI request.
     *
     *             The registered SMI requests are searched to find the incoming
     *             request. If it is found the request is handled, if it is not found
     *             an error message is written to the logbook.
     *
     * @param[in]  smiMsg     Incoming SMI message
     *******************************************************************************/
    void processRequest(SMI_MSG smiMsg);

    /**
     ********************************************************************************
     * @brief      Helper function which handles a call response
     *
     * @param[in]  smiMsg             Pointer to received SMI message
     *******************************************************************************/
    void processCallAnswer(SMI_MSG smiMsg);

    /**
     ********************************************************************************
     * @brief      Helper function which removes the timed out responses
     *******************************************************************************/
    void findTimeoutResponses();

    /**
     ********************************************************************************
     * @brief      Evaluates if returncode is an SMI System error code (M_ES_SMI)
     *             Notifies the error listeners, if the code is an SMI system error code
     *
     *******************************************************************************/
    void evaluateIfSystemError(SINT32 returnCode);

    std::vector<SmiRequest*>* pSmiRequestList;
    std::vector<SmiRequest*>* pSystemRequestList;

    std::vector<SmiHandlerErrorListener*> errorListeners;

    SMI_ID* pSmiID;
    SINT32 smiReceiveStatus;
    SMI_MSG smiMsg;

    SviServer* pSviServer; /**< SVI server handler */

    FUNCPTR pSmiReceive; /**< Function smi_Receive2 or smi_Receive */
    UINT32 userSessionId; /**< User session ID, for use with smi_Receive2 and svi_MsgHandler2 */

    TXidReplyMap *callReplyMap; /**< Map to handle responses for calls */
    UINT16 currentXid; /**< The current xId */

    std::map<UINT16, ListenerProcIDPair> replyListeners; /** Listeners for replies */

    //For making SMIHandler threadsafe
    SEM_ID commMutex;

    void aquireCommLock();

    void releaseCommLock();

    void sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout, SmiReplyListener *pListener);

};


/** @} */

#endif  /**SMIHANDLER_HPP_*/
