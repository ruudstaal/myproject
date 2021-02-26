/**
 ********************************************************************************
 * @file     SmiHandler.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiHandler
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include <sysSymTbl.h>
#include <syslib.h>

#include "SmiHandler.hpp"
#include "Smi_ProcDeinit.hpp"
#include "Smi_ProcEndOfInit.hpp"
#include "Smi_ProcGetInfo.hpp"
#include "Smi_ProcNewCfg.hpp"
#include "Smi_ProcNull.hpp"
#include "Smi_ProcReset.hpp"
#include "Smi_ProcRun.hpp"
#include "Smi_ProcSetDbg.hpp"
#include "Smi_ProcStop.hpp"
#include "SmiException.hpp"
#include "BETaskConfiguration.hpp"
#include "RemoteSmiClient.hpp"
#include "LocalSmiClient.hpp"
#include "socklib.h"

SmiHandler::SmiHandler(BETaskConfiguration conf) :
        BETask(conf)
{
    initInternal(conf.getModule());

    /* create a binary semaphore that is initially full */
    commMutex = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
}

void SmiHandler::aquireCommLock() {
    STATUS status = semTake(commMutex, WAIT_FOREVER);
    if (status != OK)
    {
        std::stringstream ss;
        ss << "Failed to aquire lock for making SMIHandler threadsafe. " << status;
        throw SmiException(ss.str());
    }
}

void SmiHandler::releaseCommLock()
{
    STATUS status = semGive(commMutex);
    if (status != OK)
    {
        std::stringstream ss;
        ss << "Failed to release lock for making SMIHandler threadsafe. " << status;
        throw SmiException(ss.str());
    }
}

void SmiHandler::initInternal(BEModule *pModule)
{
    sAppName = pModule->getAppName();
    priority = SMI_SRV_PRIO;
    stackSize = SMI_SRV_STACK;
    pSmiRequestList = new std::vector<SmiRequest*>();
    pSystemRequestList = new std::vector<SmiRequest*>();
    callReplyMap = new TXidReplyMap();
    currentXid = 0;
    SYM_TYPE symType;
    SINT32 ret = 0;

    pSviServer = NULL;
    pSmiReceive = NULL;
    pSmiID = NULL;
    smiReceiveStatus = 0;
    userSessionId = 0;
    char functionName[] = "_smi_Receive2";
    ret = symFindByName(sysSymTbl, functionName, (char**) &pSmiReceive, &symType);
    if (ret == ERROR)
    {
        warn("smi_Receive2! _pSmiReceive is used!");
        char functionName[] = "_smi_Receive";
        symFindByName(sysSymTbl, functionName, (char**) &pSmiReceive, &symType);
    }

    // Register module related SMI calls
    pSystemRequestList->push_back(new Smi_ProcDeinit(pModule));
    pSystemRequestList->push_back(new Smi_ProcEndOfInit(pModule));
    pSystemRequestList->push_back(new Smi_ProcGetInfo(pModule));
    pSystemRequestList->push_back(new Smi_ProcNewCfg(pModule));
    pSystemRequestList->push_back(new Smi_ProcNull());
    pSystemRequestList->push_back(new Smi_ProcReset(pModule));
    pSystemRequestList->push_back(new Smi_ProcRun(pModule));
    pSystemRequestList->push_back(new Smi_ProcSetDbg(pModule));
    pSystemRequestList->push_back(new Smi_ProcStop(pModule));
}

SmiHandler::~SmiHandler()
{
    deInitSvi();

    //Clear and delete the list used collecting all SMI requests
    pSmiRequestList->clear();
    SAFE_DELETE(pSmiRequestList);

    //Clear and delete the SMI Handler specific calls
    for (std::vector<SmiRequest*>::iterator proc = pSystemRequestList->begin();
            proc != pSystemRequestList->end(); ++proc)
    {
        SAFE_DELETE(*proc);
    }
    pSystemRequestList->clear();
    SAFE_DELETE(pSystemRequestList);

    TXidReplyMap::iterator ite = callReplyMap->begin();
    while (ite != callReplyMap->end())
    {
        callReplyMap->erase(ite++);
    }

    SAFE_DELETE(callReplyMap);
    replyListeners.clear();
    semDelete(commMutex);
}

VOID SmiHandler::initSmi(VOID)
{
    registerSmiRequest(this->pSystemRequestList);

    /** Add SMI requests from all tasks in module */
    for (std::list<BETask*>::iterator appTask = pModule->getAppTasklist()->begin();
            appTask != pModule->getAppTasklist()->end(); ++appTask)
    {
        registerSmiRequest((*appTask)->getSmiRequestList());
    }
}

VOID SmiHandler::initSvi(VOID)
{
    /** Create SVI server, and add handling of SVI request */
    pSviServer = new SviServer(pModule);

    pSviServer->registerSviExportDescriptors(pModule->getModuleSvi());

    std::list<BETask*> *tasks = pModule->getAppTasklist();
    /** Add descriptors for export to SVI layer */
    for (std::list<BETask*>::iterator appTask = tasks->begin(); appTask != tasks->end(); ++appTask)
    {
        pSviServer->registerSviExportDescriptors((*appTask)->getSviDescriptorList());
    }
}

VOID SmiHandler::deInitSmi(VOID)
{
    unregisterSmiRequest(pSystemRequestList);

    for (std::list<BETask*>::iterator appTask = pModule->getAppTasklist()->begin();
            appTask != pModule->getAppTasklist()->end(); ++appTask)
    {
        unregisterSmiRequest((*appTask)->getSmiRequestList());
    }
}

VOID SmiHandler::deInitSvi(VOID)
{
    SAFE_DELETE(pSviServer);
}

bool SmiHandler::registerSmiRequest(SmiRequest *pRequest)
{
    /** Check if request with same proc ID has already been added */
    for (std::vector<SmiRequest*>::iterator proc = pSmiRequestList->begin();
            proc != pSmiRequestList->end(); ++proc)
    {
        if ((*proc)->getProcId() == pRequest->getProcId())
        {
            return false;
        }
    }
    pSmiRequestList->push_back(pRequest);
    return true;
}

void SmiHandler::unregisterSmiRequest(SmiRequest *pRequest)
{
    for (std::vector<SmiRequest*>::iterator smiRequest = pSmiRequestList->begin();
            smiRequest != pSmiRequestList->end(); ++smiRequest)
    {
        if (pRequest->getProcId() == (*smiRequest)->getProcId())
        {
            pSmiRequestList->erase(smiRequest);
            return;
        }
    }
}

void SmiHandler::registerSmiRequest(std::vector<SmiRequest*>* pLocalList)
{

    for (std::vector<SmiRequest*>::iterator smiRequest = pLocalList->begin();
            smiRequest != pLocalList->end(); ++smiRequest)
    {
        if (registerSmiRequest(*smiRequest) == false)
        {
            log_Err("SmiHandler::registerSmiRequest::Detected duplicate SMI request. Proc ID = %d ", (*smiRequest)->getProcId());
        }
    }
}

void SmiHandler::unregisterSmiRequest(std::vector<SmiRequest*>* pLocalList)
{
    for (std::vector<SmiRequest*>::iterator smiRequest = pLocalList->begin();
            smiRequest != pLocalList->end(); ++smiRequest)
    {
        unregisterSmiRequest(*smiRequest);
    }
}

void SmiHandler::processRequest(SMI_MSG smiMsg)
{
    SmiRequest* proc = NULL;

    std::vector<SmiRequest*>::iterator itProc = pSmiRequestList->begin();

    /** Search registered SMI request, to find request from input */
    do
    {
        if ((*itProc)->getProcId() == smiMsg.ProcRetCode)
            proc = *itProc;

        ++itProc;
    } while (itProc != pSmiRequestList->end() && proc == NULL);

    /** Handle request, or report an error */
    if (proc)
    {
        /** Handle SMI requests */
        proc->handleRequest(&smiMsg, pModule->getSmiID());
    }
    else
    {
        error("Unsupported Smi request (" << smiMsg.ProcRetCode << ")");
    }
}

void SmiHandler::sendReply(SmiStream *pStream, SMI_MSG* pMsg, SMI_ID* pSmiID)
{
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
            return;
        }

        /** copy data from stream to allocated memory */
        pStream->read((char*) pReply, replySize);

        /** send the reply */
        smi_SendReply(pSmiID, pMsg, SMI_E_OK, pReply, replySize);
    }
}

void SmiHandler::processCallAnswer(SMI_MSG smiMsg)
{
    try
    {
        aquireCommLock();
        TXidReplyMap::iterator ite = callReplyMap->find((UINT16) smiMsg.XId);

        if (ite != callReplyMap->end())
        {
            std::map<UINT16, ListenerProcIDPair>::iterator it = replyListeners.find((UINT16)smiMsg.XId);

            SmiCallReply *pCallReply = ite->second.getCallReply();

            if (smiMsg.ProcRetCode == M_E_OK)
            {
                SmiStream *pReplyStream = new SmiStream(&smiMsg);
                pCallReply->readReply(pReplyStream);
                SAFE_DELETE(pReplyStream);

            }
            callReplyMap->erase(ite);
            replyListeners.erase(it);
            releaseCommLock();

            if (smiMsg.ProcRetCode == M_E_OK)
            {

                if (it != replyListeners.end())
                {
                    try{
                        it->second.pListener->replyRecieved(pCallReply, it->second.proc_id);
                        //replyListeners.erase(it);
                        evaluateIfSystemError(pCallReply->getReturnCode());
                    }
                    catch(...){}
                }
                else{
                    log_Err("SmiHandler::Reply listener not found - not calling anything for call %d", (UINT16)smiMsg.XId);
                }
            }
            else
            {
                log_Err("SMI call with procedure id %d failed with returncode %x", it->second.proc_id, smiMsg.ProcRetCode);
                if (it != replyListeners.end())
                {
                    try{
                        it->second.pListener->callFailed(pCallReply, it->second.proc_id, smiMsg.ProcRetCode);
                        it->second.pListener->callFailed(it->second.proc_id, smiMsg.ProcRetCode);
                        evaluateIfSystemError(smiMsg.ProcRetCode);
                    }catch(...){}
                }
            }
        }
        else
        {
            releaseCommLock();
            warn("Could not find handler to parse SMI response for xID " << (UINT16)smiMsg.XId);
        }
    }
    catch (SmiException &ex)
    {
        releaseCommLock();
        log_Wrn("Encountered SMI Exception in SMI call answer. %s", ex.what());
    }
    catch (...)
    {
        releaseCommLock();
        log_Wrn("Encountered exception in call answer...");
    }
}

void SmiHandler::evaluateIfSystemError(SINT32 returnCode) {
    if(returnCode == RES_E_BADNAME) {
        return;
    }
    if((returnCode & M_ES_SMI)) {


        for(std::vector<SmiHandlerErrorListener*>::iterator ite = errorListeners.begin(); ite != errorListeners.end(); ++ite) {
            (*ite)->systemFailureRecieved(returnCode, this);
        }
    }
}

SmiClient* SmiHandler::createClient(std::string ip, std::string username, std::string password)
{
    return createClient(ip, username, password, "BEFCSMI");
}

SmiClient* SmiHandler::createClient(std::string ip, std::string username, std::string password, std::string toolName)
{
    return new RemoteSmiClient(this, ip, username, password, toolName);
}

SmiClient* SmiHandler::createClient()
{
    return new LocalSmiClient(this);
}

void SmiHandler::addErrorListener(SmiHandlerErrorListener *pListener) {
    errorListeners.push_back(pListener);
}

void SmiHandler::sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply,
        SmiReplyListener *pListener)
{
    sendCall(moduleName, pCall, pReply, DEFAULT_CALL_TIMEOUT_INTERNAL, pListener);
}


// Send SMI call to internal on controller
void SmiHandler::sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout, SmiReplyListener *pListener) {

    UINT32 ModNb;
    struct timespec RtcTime;

    /** Not allowed to wait forever */
    if (timeout == 0)
    {
        throw SmiException("It is not allowed to wait forever for a response");
    }

    aquireCommLock();

    //Increment to the next XID in line
    currentXid++;

    /** Check if a reponse for this id is already mapped */
    TXidReplyMap::iterator ite = callReplyMap->find(currentXid);
    if (ite != callReplyMap->end())
    {
        warn(
                "Reply mapping already exists with id " << currentXid <<". Deleting in response queue.");
        callReplyMap->erase(ite);
    }

    if (currentXid == _ARCH_USHRT_MAX)
    {
        currentXid = 0;
    }

    if (res_GetModNb((char*) moduleName.c_str(), &ModNb))
    {
        throw SmiException("Could not get modulenumber for sending SMI call");
    }

    /** First allocate the memory for the call */
    void* pCallMem = smi_MemAlloc(pCall->getDataSize());

    if (pListener != NULL)
    {
        replyListeners.insert(
                std::make_pair(currentXid, ListenerProcIDPair(pListener, pCall->getProcedureId())));
    }

    /** Now copy the memory there. */
    memcpy(pCallMem, pCall->getData(), pCall->getDataSize());

    sys_GetClockMonotonic(&RtcTime);

    callReplyMap->insert(std::make_pair(currentXid, SmiReplyWrapper(pReply, RtcTime.tv_sec + timeout)));
    SINT32 ret = smi_SendCall(getModule()->getSmiID(), SMI_LOCALCPU, currentXid, ModNb, 2, pCall->getProcedureId(), pCallMem, pCall->getDataSize());
    if (ret != SMI_E_OK)
    {
        callReplyMap->erase(currentXid);
        releaseCommLock();
        throw SmiException("Could not send SMI call. Error in function.");
    }

    releaseCommLock();
}

void SmiHandler::sendCall(std::string moduleName, SmiCall *pCall, SmiCallReply *pReply,
        UINT32 timeout)
{
    sendCall(moduleName, pCall, pReply, timeout, NULL);
}

// Send SMI call to remote controller
void SmiHandler::sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout, SmiReplyListener *pListener)
{
    if(isTerminated()) {
        throw SmiException("Cannot send Remote SMI calls when SMI handler is terminated");
    }

    SINT32 CpuNb;
    struct timespec RtcTime;

    /** Not allowed to wait forever */
    if (timeout == 0)
    {
        throw SmiException("It is not allowed to wait forever for a response");
    }

    /** Check if a response for this id is already mapped */

    aquireCommLock();

    currentXid++;

    if (currentXid == _ARCH_USHRT_MAX)
    {
        currentXid = 0;
    }

    TXidReplyMap::iterator ite = callReplyMap->find(currentXid);
    if (ite != callReplyMap->end())
    {
        warn(
                "Reply mapping already exists with id " << currentXid <<". Deleting in response queue.");
        callReplyMap->erase(ite);
    }

    if (pListener != NULL)
    {
        replyListeners.insert(
                std::make_pair(currentXid, ListenerProcIDPair(pListener, pCall->getProcedureId())));
    }

    // Convert IP address string to CpuNb
    CpuNb = ntohl(inet_addr((char* )remoteIP.c_str()));
    if (CpuNb == -1)
    {
        std::stringstream ss;
        ss << "Input provided IP, is not a valid IP addr: '" << remoteIP << "'";
        throw SmiException(ss.str());
    }

    //First allocate the memory for the call
    void* pCallMem = smi_MemAlloc(pCall->getDataSize());

    //Now copy the memory there.
    memcpy(pCallMem, pCall->getData(), pCall->getDataSize());

    sys_GetClockMonotonic(&RtcTime);

    callReplyMap->insert(
            std::make_pair(currentXid, SmiReplyWrapper(pReply, (RtcTime.tv_sec) + timeout)));

    SINT32 ret = smi_SendCall(getModule()->getSmiID(), CpuNb, currentXid, remoteModNb, 2,
            pCall->getProcedureId(), pCallMem, pCall->getDataSize());
    if (ret < 0)
    {
        callReplyMap->erase(currentXid);
        releaseCommLock();
        throw SmiException("Could not send SMI call. Error in function.");
    }

    releaseCommLock();
}

void SmiHandler::sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout)
{
    sendCall(remoteIP, remoteModNb,  pCall,  pReply, timeout, NULL);
}

// Send SMI call to remote controller with Authentication
void SmiHandler::sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall,
        SmiCallReply *pReply, UINT32 timeout, std::vector<CHAR8> authentication,
        SmiReplyListener *pListener)
{
    if(isTerminated()) {
        throw SmiException("Cannot send Remote SMI calls when SMI handler is terminated");
    }

    SINT32 CpuNb;
    struct timespec RtcTime;

    /** Not allowed to wait forever */
    if (timeout == 0)
    {
        throw SmiException("It is not allowed to wait forever for a response");
    }

    aquireCommLock();

    currentXid++;

    if (currentXid == _ARCH_USHRT_MAX)
    {
        currentXid = 0;
    }

    /** Check if a response for this id is already mapped */
    TXidReplyMap::iterator ite = callReplyMap->find(currentXid);
    if (ite != callReplyMap->end())
    {
        warn("Reply mapping already exists with id " << currentXid <<". Deleting in response queue.");
        callReplyMap->erase(ite);
    }

    if (pListener != NULL)
    {
        replyListeners.insert(
                std::make_pair(currentXid, ListenerProcIDPair(pListener, pCall->getProcedureId())));
    }

    // Convert IP address string to CpuNb
    CpuNb = ntohl(inet_addr((char* )remoteIP.c_str()));
    if (CpuNb == -1)
    {
        std::stringstream ss;
        ss << "Input provided IP, is not a valid IP addr: '" << remoteIP << "'";
        throw SmiException(ss.str());
    }

    //First allocate the memory for the call
    void* pCallMem = smi_MemAlloc(pCall->getDataSize());

    //Now copy the memory there.
    memcpy(pCallMem, pCall->getData(), pCall->getDataSize());

    sys_GetClockMonotonic(&RtcTime);

    callReplyMap->insert(std::make_pair(currentXid, SmiReplyWrapper(pReply, RtcTime.tv_sec + timeout)));


    SINT32 ret;
    if (authentication.empty())
    {
        ret = smi_SendCall(getModule()->getSmiID(), CpuNb, currentXid, remoteModNb, SMI_STDPROTVERS,
                pCall->getProcedureId(), pCallMem, pCall->getDataSize());
    }
    else
    {
        ret = smi_SendCall(getModule()->getSmiID(), CpuNb, currentXid, remoteModNb,
                SMI_STDPROTVERS | SMI_AUTH, pCall->getProcedureId(), pCallMem, pCall->getDataSize(),
                authentication.data());
    }


    if (ret < 0)
    {
        callReplyMap->erase(currentXid);
        releaseCommLock();
        throw SmiException("Could not send SMI call. Error in function.");
    }
    releaseCommLock();

}

// Send SMI call to remote controller with Authentication
void SmiHandler::sendCall(std::string remoteIP, UINT32 remoteModNb, SmiCall *pCall, SmiCallReply *pReply, UINT32 timeout, std::vector<CHAR8> authentication)
{
       sendCall(remoteIP, remoteModNb, pCall, pReply, timeout, authentication, NULL);
}

void SmiHandler::findTimeoutResponses()
{
    struct timespec RtcTime;

    sys_GetClockMonotonic(&RtcTime);
    TXidReplyMap::iterator ite = callReplyMap->begin();
    while (ite != callReplyMap->end())
    {
        if (ite->second.getTimeout() <= RtcTime.tv_sec)
        {
            ite->second.getCallReply()->callFailed(M_E_TIMEOUT3);
            std::map<UINT16, ListenerProcIDPair>::iterator it = replyListeners.find(ite->first);
            if (it != replyListeners.end())
            {
                try{
                    it->second.pListener->callFailed(ite->second.getCallReply(), it->second.proc_id, M_E_TIMEOUT3);
                    it->second.pListener->callFailed(it->second.proc_id, M_E_TIMEOUT3);
                }
                catch(...){}

                aquireCommLock();
                replyListeners.erase(it);
                releaseCommLock();
            }

            aquireCommLock();
            callReplyMap->erase(ite++);
            releaseCommLock();
        }
        else
        {
            ++ite;
        }
    }
}

void SmiHandler::doEventDelay(void)
{
    /** check for incoming SMI, use 1 second cycle time for message queue. */
    smiReceiveStatus = pSmiReceive(pModule->getSmiID(), &smiMsg, sysClkRateGet(), &userSessionId);
}

void SmiHandler::cycleWork(void)
{
    findTimeoutResponses(); /** For each cycle find those responses which have timed out. */
    /** Test if SMI request received */
    if (smiReceiveStatus < 0)
    {
        return; /** Nothing is recieved */
    }

    /** process incoming SMI communication, check if it's a call or a reply */
    if (smiMsg.Type & SMI_F_CALL)
    {
        try
        {
            processRequest(smiMsg);
        }
        catch (SmiException const& e)
        {
            warn("Caught SMI exception while processing SMI request. " << e.what());
        }
        catch (std::exception const& e)
        {
            warn("Caught general exception while processing SMI request. " << e.what());
        }
        catch (...)
        {
            warn("Caught unexpected exception while processing SMI call answer");
        }

    }
    else
    {
        try
        {
            processCallAnswer(smiMsg);
        }
        catch (SmiException const& e)
        {
            warn("Caught SMI expception while processing SMI call answer. " << e.what());
        }
        catch (std::exception const& e)
        {
            warn("Caught general exception while processing SMI call answer. " << e.what());
        }
        catch (...)
        {
            warn("Caught unexpected exception while processing SMI call answer");
        }

        smi_FreeData(&smiMsg);
    }
}

void SmiHandler::terminated(void)
{
    pModule->deinit();
}

const UINT32 SmiHandler::getUserSessionId(void)
{
    return (userSessionId);
}
