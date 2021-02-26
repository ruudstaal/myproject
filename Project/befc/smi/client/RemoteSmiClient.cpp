/**
 ********************************************************************************
 * @file     RemoteSmiClient.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 9, 2016 9:03:53 AM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <stdexcept>
#include <RemoteSmiClient.hpp>
#include "SmiException.hpp"
#include <cstring>
#include <algorithm>
#include <stdio.h>

RemoteSmiClient::RemoteSmiClient(SmiHandler *pSmiHandler, std::string ip, std::string username,
        std::string password) :
        pSmiHandler(pSmiHandler), ip(ip), username(username), password(password), checkQueueAgain(false),checkingQueue(false),
            loginCall(ResProcLoginCall(username, password, 0, rand(), "BEFCSMI")), loginReply(ResProcLoginReply()), modNBCall(ResProcModNBCall()),
                modNBReply(ResProcModNBReply())
{

    /* create a binary semaphore that is initially full */
    semMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
    setState(SMIClientEventListener::OFFLINE, false);

    pSmiHandler->addErrorListener(this);
}

RemoteSmiClient::RemoteSmiClient(SmiHandler *pSmiHandler, std::string ip, std::string username,
        std::string password, std::string toolName) :
        pSmiHandler(pSmiHandler), ip(ip), username(username), password(password), checkQueueAgain(false),checkingQueue(false),
            loginCall(ResProcLoginCall(username, password, 0, rand(), toolName)), loginReply(ResProcLoginReply()), modNBCall(ResProcModNBCall()),
                modNBReply(ResProcModNBReply())
{

    /* create a binary semaphore that is initially full */
    semMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
    setState(SMIClientEventListener::OFFLINE, false);

    pSmiHandler->addErrorListener(this);
}


RemoteSmiClient::~RemoteSmiClient()
{
    semDelete(semMutex);
}

void RemoteSmiClient::connect()
{
    if (getState() != SMIClientEventListener::ONLINE)
    {
        STATUS status = semTake(semMutex, WAIT_FOREVER);
          if(status != OK) {
              log_Err("RemoteSmiClient::Failed to get Sema at Remote SmiClient connect. %d", status);
          }

        try
        {
            //When connecting to a remote controller, the RES module of the controller must be contacted first with login info.
            pSmiHandler->sendCall(ip, (UINT32) RES_PROGNB, &loginCall, &loginReply, SmiHandler::DEFAULT_CALL_TIMEOUT_EXTERNAL, this);
        }
        catch (SmiException &ex)
        {
            log_Err("RemoteSmiClient::Failed to connect remote SMI client. %s", ex.what());
            setState(SMIClientEventListener::ERR, true);
        }
        catch (...)
        {
            log_Err("RemoteSmiClient::Failed to connect remote SMI client");
            setState(SMIClientEventListener::ERR, true);
        }
    }
    else
    {
        notifyListeners(SMIClientEventListener::ONLINE);
    }
}

bool RemoteSmiClient::isConnected()
{
    if (getState() == SMIClientEventListener::ONLINE)
    {
        return true;
    }
    return false;
}

void RemoteSmiClient::disconnect()
{
    if (getState() == SMIClientEventListener::ONLINE)
    {
        setState(SMIClientEventListener::DISCONNECTING, true);
        STATUS status = semTake(semMutex, WAIT_FOREVER);
        if (status != OK)
        {
            log_Err("RemoteSmiClient::Failed to get Sema at Remote SmiClient logout. %d", status);
        }

        //logout call sent to the RES module
        pSmiHandler->sendCall(ip, (UINT32) RES_PROGNB, &logoutCall, &logoutReply,
                SmiHandler::DEFAULT_CALL_TIMEOUT_EXTERNAL, loginReply.getAuthent(), this);
    }
    else
    {
        notifyListeners(SMIClientEventListener::OFFLINE);
    }

    moduleNbrMap.clear();
    nonExistingModules.clear();
    //semGive(semMutex);
}

BOOL8 RemoteSmiClient::hasModuleNumber(std::string moduleName)
{
    std::map<std::string, UINT32>::iterator ite = moduleNbrMap.find(moduleName);
    if (ite != moduleNbrMap.end())
    {
        return true;
    }
    return false;
}


UINT32 RemoteSmiClient::getModuleNumber(std::string moduleName)
{

    std::map<std::string, UINT32>::iterator ite = moduleNbrMap.find(moduleName);
    if(ite != moduleNbrMap.end()) {
        return (*ite).second;
    }
    char err[70];
    sprintf(err, "Module name was not found in list %s ", moduleName.c_str());
    throw std::invalid_argument(err);
}

void RemoteSmiClient::requestModuleNumber(std::string moduleName) {

    STATUS status = semTake(semMutex, WAIT_FOREVER);
    if (status == OK)
    {
        //Send a call to the RES task, to get the module number we which to send SMI calls to.
        modNBCall.setModuleName(moduleName);

        pSmiHandler->sendCall(ip, (UINT32) RES_PROGNB, &modNBCall, &modNBReply,
                SmiHandler::DEFAULT_CALL_TIMEOUT_EXTERNAL, this);
    }
    else
    {
        log_Err("RemoteSmiClient::Failed to get mutex for getting module number. %d", status);
    }
}

void RemoteSmiClient::putToQueue(std::string module, SmiCall *pCall, SmiCallReply *pReply,
        SmiReplyListener *pListener)
{
    queuedCall req;
    req.module = module;
    req.pCall = pCall;
    req.pReply = pReply;
    req.pListener = pListener;
    queuedCalls.push_back(req);
}

void RemoteSmiClient::checkQueue()
{
    if(checkingQueue) {
        checkQueueAgain = true;
        return;
    }

    checkingQueue = true;
    for (std::vector<queuedCall>::iterator it = queuedCalls.begin(); it != queuedCalls.end(); )
    {
        try
        {
            it = queuedCalls.erase(it);
            sendCall((*it).module, (*it).pCall, (*it).pReply, (*it).pListener);
        }
        catch (std::invalid_argument &arg)
        {
            //Module number still not ready
            ++it;
        }
    }
    checkingQueue = false;

    if(checkQueueAgain) {
        checkQueueAgain = false;
        checkQueue();
    }

}


bool RemoteSmiClient::isModuleNotPresent(std::string moduleName) {
    if (std::find(nonExistingModules.begin(), nonExistingModules.end(), moduleName) != nonExistingModules.end())
    {
      return true;
    }
    return false;
}

void RemoteSmiClient::sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply, SmiReplyListener *pListener)
{
    if (getState() == SMIClientEventListener::ONLINE)
    {
        try
        {
            try
            {
                if(isModuleNotPresent(module)) {
                    pReply->callFailed(SVI_E_NOMOD);
                    pListener->callFailed(pReply, pCall->getProcedureId(), SVI_E_NOMOD);
                }
                else{
                    if(hasModuleNumber(module) == false){
                        putToQueue(module, pCall, pReply, pListener);
                        requestModuleNumber(module);
                        return;
                    }


                    UINT32 moduleNumber = getModuleNumber(module);
                    pSmiHandler->sendCall(ip, moduleNumber, pCall, pReply,
                            SmiHandler::DEFAULT_CALL_TIMEOUT_EXTERNAL, loginReply.getAuthent(),
                            pListener);
                }
            }
            catch (std::invalid_argument &arg)
            {
                requestModuleNumber(module);
                putToQueue(module, pCall, pReply, pListener);
            }
        }
        catch (SmiException &ex)
        {
            log_Err("Error sending SMI call with procedure id %d to %s. Reason: %s",
                    pCall->getProcedureId(), ip.c_str(), ex.what());

            setState(SMIClientEventListener::ERR, true);
        }
    }
    else
    {
        throw SmiException("Could not send SMI call when NOT in ONLINE state");
    }
}

void RemoteSmiClient::sendCall(std::string module, SmiCall *pCall, SmiCallReply *pReply)
{
    if (getState() == SMIClientEventListener::ONLINE)
    {
        try
        {
            try
            {
                if (isModuleNotPresent(module))
                {
                    pReply->callFailed(SVI_E_NOMOD);
                }
                else
                {

                    if(hasModuleNumber(module) == false){
                        putToQueue(module, pCall, pReply, NULL);
                        requestModuleNumber(module);
                        return;
                    }

                    UINT32 moduleNumber = getModuleNumber(module);

                    pSmiHandler->sendCall(ip, moduleNumber, pCall, pReply,
                            SmiHandler::DEFAULT_CALL_TIMEOUT_EXTERNAL, loginReply.getAuthent());
                }
            }
            catch (std::invalid_argument &arg)
            {
                putToQueue(module, pCall, pReply, NULL);
                requestModuleNumber(module);
            }

        }
        catch (SmiException &ex)
        {
            log_Err("Error sending SMI call with procedure id %d to %s. Reason: %s",
                    pCall->getProcedureId(), ip.c_str(), ex.what());
        }
    }
    else
    {
        throw SmiException("Could not send SMI call when NOT in ONLINE state");
    }
}

void RemoteSmiClient::systemFailureRecieved(SINT32 failure, SmiHandler *pInstance){
    setState(SMIClientEventListener::ERR, true);
}

void RemoteSmiClient::callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason)
{
    if (procID == loginCall.getProcedureId())
    {
        STATUS status = semGive(semMutex);
        if (status != OK)
        {
            log_Err("RemoteSmiClient::Could not release mutex when logging in callfailed (FAIL reason: %d) %d", reason, status);
        }

        //Clear the module maps to force renew of adresses
        moduleNbrMap.clear();
        nonExistingModules.clear();

        if(reason == M_E_TIMEOUT3) {
            setState(SMIClientEventListener::TIMEOUT, true);
        }
        else{
            log_Err("RemoteSmiClient::Remote SMI client login call failed : %x", reason);
            setState(SMIClientEventListener::LOGIN_FAILED, true);
        }
    }
    else if (procID == modNBCall.getProcedureId())
    {
        STATUS status = semGive (semMutex);
        if(status != OK) {
            log_Err("RemoteSmiClient::Could not release mutex for getting module name (FAIL reason: %d) %d", reason, status);
        }

        setState(SMIClientEventListener::ERR, true);
        log_Err("Remote SMI client module number request call failed : %x", reason);
    }
    else if (procID == logoutCall.getProcedureId())
    {
        moduleNbrMap.clear();
        nonExistingModules.clear();
        setState(SMIClientEventListener::ERR, true);
        STATUS status = semGive(semMutex);
        if (status != OK)
        {
            log_Err(
                    "RemoteSmiClient::Could not release mutex for handling failed logout call (FAIL reason: %d) %d",
                    reason, status);
        }
    }
    else
    {
        log_Err("Remote SMI client failure for unknown call %d : %x", procID, reason);
        setState(SMIClientEventListener::ERR, true);
    }
}

/**
 * Function used for login to the remote controller. For this we need to send SMI calls.
 */
void RemoteSmiClient::replyRecieved(SmiCallReply *pReply, UINT32 procID)
{
    if (procID == loginCall.getProcedureId())
    {
        STATUS status = semGive(semMutex);
        if (status != OK)
        {
            log_Err("RemoteSmiClient::Failed to release sema at RemoteSmiClient replyrecieved login call : %d", status);
        }
        //Clear the module maps to force renew of adresses
        moduleNbrMap.clear();
        nonExistingModules.clear();

        if (loginReply.getReturnCode() == SMI_E_OK)
        {
            //We got answer for the login
            setState(SMIClientEventListener::ONLINE, true);
        }
        else
        {
            if(loginReply.getReturnCode() == RES_E_BADLOGIN) {
                setState(SMIClientEventListener::BAD_LOGIN, true);
            }
            else {
                log_Err("Remote SMI client failed to login Reason: %x", loginReply.getReturnCode());
                setState(SMIClientEventListener::LOGIN_FAILED, true);
            }

        }
    }
    else if (procID == modNBCall.getProcedureId())
    {
        if (modNBReply.getReturnCode() == SMI_E_OK)
        {
            //We got answer about the module number
            moduleNbrMap.insert(std::pair<std::string,int>(modNBCall.getModuleName(),modNBReply.getModuleNbr()));
        }
        else
        {
            //Experiencing that a module does not exist is NOT an error cause for the client.
            nonExistingModules.push_back(modNBCall.getModuleName());
            if(modNBReply.getReturnCode() == RES_E_BADNAME) {
                log_Err("Failed to recieve module number for %s. Module does not exist on controller", modNBCall.getModuleName().c_str());
            }
            else{
                log_Err("Failed to recieve module number. %x", modNBReply.getReturnCode());
            }
        }


        checkQueue();

        STATUS status = semGive (semMutex);
        if (status != OK)
        {
            log_Err("RemoteSmiClient::Could not release mutex for getting module name. %d", status);
            setState(SMIClientEventListener::ERR, true);
        }
    }
    else if (procID == logoutCall.getProcedureId()) {

        moduleNbrMap.clear();
        nonExistingModules.clear();

        STATUS status = semGive(semMutex);
        if (status != OK)
        {
            log_Err(
                    "RemoteSmiClient::Failed to release sema at RemoteSmiClient replyreceived logout call : %d",
                    status);

            if (pReply->getReturnCode() == SMI_E_OK)
            {
                setState(SMIClientEventListener::OFFLINE, true);
            }
            else
            {
                log_Err("Semaphor error when disconnecting SMI client to %s. Reason : %x", ip.c_str(),
                        pReply->getReturnCode());
                setState(SMIClientEventListener::ERR, true);
            }
        }
    }
    else {
        log_Err("RemoteSmiClient[%s]::Remote SMI Client recieved response to something it knows nothing about. ProcId %d", this->ip.c_str(), procID);
    }
}
