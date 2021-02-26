
/*
 * RemoteSviGroup.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: madsen
 */
#include <RemoteSviGroup.hpp>
#include <RemoteSviListReadStrategy.hpp>
#include <RemoteSviReadStrategy.hpp>
#include <SmiHandler.hpp>
#include <SviException.hpp>
#include "SviSystemException.hpp"


RemoteSviGroup::RemoteSviGroup(std::string name, BETask* pTask, std::string ip,
        std::string username, std::string password) :
        name(name), initialized(false), active(false), pTask(pTask), ip(ip), username(username), password(
                password), items(TStrVecItems()), doInit(true), clientConnected(false), commActive(
                false), pClient(
                pTask->getModule()->getSmiHandler()->createClient(ip, username, password, name)), getAddrCall(
                SviProcGetXAddrCall()), getAddrReply(SviProcGetXAddrReply()), connecting(false), remoteSystemReady(
                false), waitingForRemoteSystem(false)
{
    pClient->addEventListener(this);

    pItemStrategy = new RemoteSviListReadStrategy(pClient);

    /* create a binary semaphore that is initially full */
    commMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
}

RemoteSviGroup::~RemoteSviGroup(){
    TStrVecItems::iterator p;
    for (p = items.begin(); p != items.end(); ++p)
    {
        deleteVector(p->second);
    }
    items.clear();

    SAFE_DELETE(pItemStrategy);
    SAFE_DELETE(pClient);
    semDelete(commMutex);
}


void RemoteSviGroup::deleteVector(std::vector<AbstractSviItem*> list) {
    std::vector<AbstractSviItem*>::iterator ite;

    for (ite = list.begin(); ite != list.end(); ++ite)
    {
        SAFE_DELETE((*ite));
    }
    list.clear();
}

std::string RemoteSviGroup::getName(){
    return this->name;
}

bool RemoteSviGroup::isActive() {
    return active;
}

void RemoteSviGroup::setActive(bool active) {


    if(this->active == active) {
        if(active == false && clientConnected) {
            pClient->disconnect();
        }
        return;
    }

    if(this->active && connecting) { //We are already connecting - no need to do it again..
        return;
    }

    if(hasValidItems() == false) {
        if(active){
            log_Wrn("Remote group %s has no valid items. Setting it active would have no effect", getName().c_str());
        }
        this->active = false;
        return;
    }
    else {
        this->active = active;
    }

    try
    {
        if (active)
        {
            connecting = true;
            pClient->connect();
        }
        else
        {
            connecting = false;
            pClient->disconnect();
        }
    }
    catch (std::exception &ex){
        this->active = false;
        this->connecting = false;
        throw SviException(ex.what());
    }
    catch(...) {
        this->active = false;
        this->connecting = false;
        throw SviException("Fatal exception occured in setting remote SVI group to active");
    }


}

void RemoteSviGroup::reset() {
    //Force initialization once again.
    std::vector<AbstractSviItem*> result;
    TStrVecItems::iterator p;
    std::vector<AbstractSviItem*> vector;
    for (p = items.begin(); p != items.end(); ++p)
    {
        vector = p->second;
        for(std::vector<AbstractSviItem*>::iterator p1 = vector.begin(); p1 != vector.end(); ++p1) {
            (*p1)->reset();
        }
    }
    //pClient->disconnect();
}

void RemoteSviGroup::init()
{
    if (initialized)
    {
        return;
    }

    if(clientConnected == false) {
        doInit = true;
        return;
    }

    if(remoteSystemReady == false && waitingForRemoteSystem == false){
        waitingForRemoteSystem = true;
        getRemoteSysInfo();
        return;
    }

    if(remoteSystemReady == false){
        return;
    }

    TStrVecItems::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    std::vector<AbstractSviItem*> itemsList;

    /** Go through all modules and get addresses for module and pItems */
    for (p = items.begin(); p != items.end(); ++p)
    {
        itemsList = p->second;

        /** Go through all pItems and get address and format */
        for (ite = itemsList.begin(); ite != itemsList.end(); ++ite)
        {
            try
            {
                if((*ite)->isInitialized() || (*ite)->isFailed()) {
                    continue;
                }
                /** Initialize the single item (svi_GetAddr) */

                initializeItem((*ite));
            }
            catch (SviException const& svie)
            {
                error(svie.what());
                return;
            }
        }
    }

}

void RemoteSviGroup::initializeItem(AbstractSviItem *pItem) {

    if(getSysInfoReply.getReply().AppState != RES_S_RUN) {
        return;
    }

    STATUS status = semTake(commMutex, WAIT_FOREVER);
    if (status == OK)
    {
        getAddrCall.SetSVIVarName(pItem->getVarName());
        getAddrReply.setParameter(pItem);
        pClient->sendCall(pItem->getModuleName(), &getAddrCall, &getAddrReply, this);
    }
    else
    {
        log_Err("Could not get mutex for initializing Remote SVI variables. %x", status);
    }
}

bool RemoteSviGroup::hasValidItems(){
    TStrVecItems::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    std::vector<AbstractSviItem*> itemsList;

    /** Go through all modules and get addresses for module and pItems */
    for (p = items.begin(); p != items.end(); ++p)
    {
        itemsList = p->second;

        for (ite = itemsList.begin(); ite != itemsList.end(); ++ite)
        {
            if((*ite)->isFailed()) { //If it is failed, we have tried to initialize it..
                continue;
            }
            else {
                return true;
            }
        }
    }
    return false;

}

bool RemoteSviGroup::isInitialized()
{
    TStrVecItems::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    std::vector<AbstractSviItem*> itemsList;

    /** Go through all modules and get addresses for module and pItems */
    for (p = items.begin(); p != items.end(); ++p)
    {
        itemsList = p->second;

        for (ite = itemsList.begin(); ite != itemsList.end(); ++ite)
        {
            if((*ite)->isFailed()) { //If it is failed, we have tried to initialize it..
                continue;
            }

            if((*ite)->isInitialized() == false) {
                return false;
            }
        }
    }
    return true;
}

bool RemoteSviGroup::removeItem(AbstractSviItem* pSviItem) {
    TStrVecItems::iterator ite = items.find(pSviItem->getModuleName());

    if (ite == items.end() ) {
       //item does not exist since module is not created
        return true;
    } else {
        std::vector<AbstractSviItem*> items = (*ite).second;
        for (std::vector<AbstractSviItem*>::iterator p = items.begin(); p != items.end(); ){
            if((*p)->getVarName().compare(pSviItem->getVarName()) == 0) {
                p = items.erase(p);
                //return, or maybe more with same name is created..
            }
            else {
                ++p;
            }
        }
    }
    return true;
}

bool RemoteSviGroup::addItem(AbstractSviItem* pSviItem) {
    if(pSviItem == NULL) {
        log_Err("RemoteSviGroup::NullPointer attempted to be added");
        return false;
    }

    TStrVecItems::iterator ite = items.find(pSviItem->getModuleName());

    if (ite == items.end() ) {
        std::vector<AbstractSviItem*> vec;
        vec.push_back(pSviItem);
        items.insert(TStrVecPair(pSviItem->getModuleName(), vec));
    } else {
      (*ite).second.push_back(pSviItem);
    }
    pSviItem->addItemEventListener(this);
    return true;
}

std::vector<AbstractSviItem*> RemoteSviGroup::getItems()
{
    std::vector<AbstractSviItem*> result;
    TStrVecItems::iterator p;
    std::vector<AbstractSviItem*> vector;
    for (p = items.begin(); p != items.end(); ++p)
    {
        vector = p->second;
        for(std::vector<AbstractSviItem*>::iterator p1 = vector.begin(); p1 != vector.end(); ++p1) {
            if((*p1)->isFailed() == false && (*p1)->isInitialized()) {
                result.push_back((*p1));
                //result.insert(result.end(), vector.begin(), vector.end());
            }
        }
    }
    return result;
}


void RemoteSviGroup::setInitialized(bool initialized) {
    if(initialized == false) {
        reset();
    }
    this->initialized = initialized;
}


void RemoteSviGroup::updateOut()
{
    if (clientConnected == false)
    {
        return;
    }

    if (hasValidItems() == false)
    {
        active = false;
        return;
    }

    if (isInitialized() == false)
    {
        return;
    }


    if (active)
    {
        try
        {
            notifyFailList(this->pItemStrategy->writeValues(this));

        }
        catch (SviSystemException &se)
        {
            log_Wrn("Could not write values in remote group %s. %s (%x)", getName().c_str(), se.what(),
                    se.getErrorCode());
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }
        catch (SviException &se)
        {
            log_Wrn("Could not write values in remote group %s. %s", getName().c_str(), se.what());
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }
        catch (...)
        {
            log_Wrn("Could not write values in remote group %s due to general exception.",
                    getName().c_str());
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }

    }
}

void RemoteSviGroup::refresh()
{
    if(hasValidItems() == false) {
        active = false;
        if(clientConnected){
            try{
                log_Info("RemoteSviGroup::refresh:: Disconnecting SMI client due to no valid items");
                pClient->disconnect();
            }
            catch(...){}
        }
        return;
    }

    if(clientConnected == false) {
        return;
    }

    if (isInitialized() == false)
    {
        if (pTask->getDebugMode() == APP_DBG_SVI1)
        {
            warn("Init not called before refresh. Calling Init()");
        }

        init();
        return; //Init is done async - cannot read immediately after
    }

    if (active)
    {
        try{
            TFailList errorList = this->pItemStrategy->readValues(this);
            notifyFailList(errorList);
            if(errorList.size() == 0 && getState() == SviGroupEventListener::ONLINE){
                notifyAboutGroupRefresh();
            }
        }
        catch(SviSystemException &se) {
            log_Wrn("Could not update remote group %s. %s (%x)", getName().c_str(), se.what(), se.getErrorCode());
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }
        catch (SviException &se)
        {
            log_Wrn("Could not update remote group %s. %s", getName().c_str(), se.what() );
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }
        catch(...) {
            log_Wrn("Could not update remote group %s due to general exception.", getName().c_str());
            active = false;
            setInitialized(false);
            setStateInternal(SviGroupEventListener::ERR);
        }
    }
}

void RemoteSviGroup::eventRecieved(ClientState state)
{
    switch (state) {
        case ONLINE:
            clientConnected = true;
            connecting = false;

            break;
        case OFFLINE:
        case DISCONNECTING:
            clientConnected = false;
            remoteSystemReady = false;
            waitingForRemoteSystem = false;
            setStateInternal(SviGroupEventListener::OFFLINE);
            break;
        case LOGIN_FAILED:
            log_Err("Remote SVI group %s is OFFLINE due to login failure.", this->ip.c_str());
            clientConnected = false;
            setStateInternal(SviGroupEventListener::OFFLINE);
            break;
        case BAD_LOGIN:
            log_Err("Username / Password for remote group %s is not correct. Unable to refresh values.", this->getName().c_str());
            clientConnected = false;
            setStateInternal(SviGroupEventListener::OFFLINE);
            break;
        case TIMEOUT:
            log_Err("%s could not be refreshed. Could not establish connection to %s, connection timed out.", this->getName().c_str(), this->ip.c_str());
            clientConnected = false;
            setStateInternal(SviGroupEventListener::OFFLINE);
            break;
        case ERR:
            if (clientConnected != false)
            {
                log_Err(
                        "%s (%s) group could not be refreshed. Remote SMI client switched into ERR state.",
                        this->getName().c_str(), this->ip.c_str());
                clientConnected = false;
                initialized = false;
                setStateInternal(SviGroupEventListener::ERR);
            }
            break;
        default:
            log_Err("Recieved unknown state from the Remote SMI client. Group will NOT be refreshed. %d", state);
            clientConnected = false;
            setStateInternal(SviGroupEventListener::ERR);
            break;
    }


    connecting = false;
    if(clientConnected) {
        setStateInternal(SviGroupEventListener::ONLINE);
    }
}

void RemoteSviGroup::dataQualityChanged(AbstractSviItem *pItem, DataQuality oldQuality, DataQuality newQuality) {
    if(newQuality == TIMED_OUT) {

        active = false; //setActive(false) would send logout call which would just fail.
        clientConnected = false;
        initialized = false;
        reset();
        setStateInternal(SviGroupEventListener::OFFLINE);
        pClient->disconnect();
    }
}

void RemoteSviGroup::writeFailed(AbstractSviItem *pItem, SINT32 failure) {
    //DataQuality will change if something is wrong with the connection.
}

void RemoteSviGroup::getRemoteSysInfo() {
    STATUS status = semTake(commMutex, WAIT_FOREVER);
       if (status == OK)
       {
           pClient->sendCall("RES", &getSysInfoCall, &getSysInfoReply, this);
       }
       else
       {
           log_Err("Could not get mutex for getting remote system info. %x", status);
       }
}

void RemoteSviGroup::replyRecieved(SmiCallReply *pReply, UINT32 procID) {
    bool failedInitializing;
    failedInitializing = false;

    if(procID == RES_PROC_SYSINFO) {
        ResProcSysInfoReply *pGetSysInfoReply = (ResProcSysInfoReply*)pReply;
        SINT32 retCode = pGetSysInfoReply->getReturnCode();

        if (retCode == SVI_E_OK)
        {
            if(pGetSysInfoReply->getReply().AppState == RES_S_RUN){
                remoteSystemReady = true;
                waitingForRemoteSystem = false;
            }
            else {
                remoteSystemReady = false;
                waitingForRemoteSystem = false;
            }
        }
        else {
            log_Info("Could not get state on remote controller: %x", pGetSysInfoReply->getReply().RetCode);
            remoteSystemReady = false;
            waitingForRemoteSystem = false;
            setInitialized(false);

        }
        waitingForRemoteSystem = false;
        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("Could not release mutex for initializing Remote SVI variables. %x", status);
        }
    }
    else if(procID == SVI_PROC_GETXADDR) { //Requested an address for SVI variable
        SviProcGetXAddrReply *pGetAddReply = (SviProcGetXAddrReply*)pReply;
        AbstractSviItem* item = (AbstractSviItem*) pGetAddReply->getParameter();
        SINT32 retCode = pGetAddReply->getReturnCode();

        if (retCode == SVI_E_OK)
        {
            try
            {
                UINT32 newFormat = pGetAddReply->getResult().ValLen;
                newFormat = newFormat << 16; //To simulate the response SVI_F_EXTLEN in the format call to svi_getAddr(..)
                newFormat += pGetAddReply->getResult().Format;

                item->initialize( pGetAddReply->getResult().Addr, newFormat, NULL);

                bool listStrat = dynamic_cast<RemoteSviListReadStrategy*>(this->pItemStrategy) != NULL;
                if(item->isArrayItem() && listStrat) { //Force reading single values - one call pr item.
                    SAFE_DELETE(this->pItemStrategy);
                    this->pItemStrategy = new RemoteSviReadStrategy(this->pClient);
                    log_Info("Remote SVI Group %s : Switched to remote single update strategy - performance will decrease. Group by 32 bit values instead", this->getName().c_str());
                }
            }
            catch (SviException &ex)
            {
                failedInitializing = true;
                removeItem(item);
                log_Err("Failed initializing item. %s. Group will not be refreshed in cycle!",
                        ex.what());
            }

        }
        else {
            item->initialize(retCode);
        }

        if(failedInitializing == false){
            if (isInitialized())
            {
                initialized = true;
                doInit = false;
            }
            else {
                initialized = false;
            }
        }

        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("Could not release mutex for initializing Remote SVI variables. %x", status);
            failedInitializing = true;
        }

        if(retCode != SVI_E_OK){
            notifyAboutItemFailed(retCode, item);
        }

    }
    else {
        log_Err("Recieved answer for smi message with proc id %d. Return code was %d", procID, pReply->getReturnCode());
    }
}

void RemoteSviGroup::callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason) {

    if(procID == RES_PROC_SYSINFO) { //Requested an address for SVI variable
        log_Info("RemoteSystemInfo call failed. %x", reason);
        waitingForRemoteSystem = false;
        remoteSystemReady = false;
        semGive(commMutex);
    }
    else if(procID == SVI_PROC_GETXADDR) {
        SviProcGetXAddrReply *pGetAddReply = (SviProcGetXAddrReply*)pReply;
        AbstractSviItem* item = (AbstractSviItem*) pGetAddReply->getParameter();
        item->initialize(reason);


        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("Could not release mutex for initializing Remote SVI variables. %x", status);
            setInitialized(false);
        }
        notifyAboutItemFailed(reason, item);
    }
    else {
        setInitialized(false);
        log_Err("RemoteSviGroup::SMI function failed for smi message with proc id %d. Reason was%d", procID, reason);
    }
}



void RemoteSviGroup::setStateInternal(SviGroupEventListener::GroupState newState)
{

    if (this->active)
    {
        //In cases where group has been set to active but response from SMI client was not OK
        if (newState == SviGroupEventListener::OFFLINE || newState == SviGroupEventListener::ERR)
        {
            this->active = false;
            notifyAboutState(getState());
        }
    }

    if (getState() != newState)
    {
        setState(newState);
    }
}


