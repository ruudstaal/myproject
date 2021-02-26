/*
 * RemoteSviReadStrategy.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: madsen
 */

#include <RemoteSviReadStrategy.hpp>

RemoteSviReadStrategy::RemoteSviReadStrategy(SmiClient *pClient) : refreshing(false), writing(false), pRefreshGroup(NULL),pWriteGroup(NULL),
    getValCall(SviProcGetValCall()), getValReply(SviProcGetValReply()), getBlkCall(SviProcGetBlkCall()), getBlkReply(SviProcGetBlkReply()), numOfFailures(0), numOfWriteFailures(0)
{
    this->pClient = pClient;
    /* create a binary semaphore that is initially full */
    commMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
    writecommMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);

}

RemoteSviReadStrategy::~RemoteSviReadStrategy()
{
    semDelete(commMutex);
}

void RemoteSviReadStrategy::replyRecieved(SmiCallReply *pReply, UINT32 procID)
{

    if (procID == SVI_PROC_GETVAL)
    {
        SviProcGetValReply *castedReply = (SviProcGetValReply*) pReply;
        AbstractSviItem* param = (AbstractSviItem*) castedReply->getParameter();
        if (pReply->getReturnCode() == SVI_E_OK)
        {
            param->updateInternalValue(castedReply->getReply().Value);
        }
        else
        {
            curFailList.push_back(makePair(pReply->getReturnCode(), param));
        }

        STATUS status = semGive(commMutex);

        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema  when updating %s", param->getVarName().c_str());
        }

        param->handleErrorCode(pReply->getReturnCode());
    }
    else if (procID == SVI_PROC_GETBLK)
    {
        SviProcGetBlkReply *castedReply = (SviProcGetBlkReply*) pReply;
        AbstractSviItem* param = (AbstractSviItem*) castedReply->getParameter();

        if(castedReply->useMultiBlk()) {
            //MUltiBLK calls should be used for getting larger amounts of data.
            //Currently not supported remotely
        }

        if (pReply->getReturnCode() == SVI_E_OK)
        {
            param->updateInternalValue(castedReply->getData(), castedReply->getDataLength());
        }
        else
        {
            curFailList.push_back(makePair(pReply->getReturnCode(), param));
        }
        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema  when updating BLK %s", param->getVarName().c_str());
        }

        param->handleErrorCode(pReply->getReturnCode());
    }
    else if (procID == SVI_PROC_SETVAL || procID == SVI_PROC_SETBLK)
    {
        AbstractSviItem* param = NULL;
        if(procID == SVI_PROC_SETVAL) {
            param = (AbstractSviItem*)((SviProcSetValReply*) pReply)->getParameter();
        }
        else {
            param = (AbstractSviItem*)((SviProcSetBlkReply*) pReply)->getParameter();
        }

        SINT32 returnCode = pReply->getReturnCode();
        if (returnCode == SVI_E_OK)
        {
            param->setDirty(false);
        }
        else
        {
            curWriteFailList.push_back(makePair(returnCode, param));
            param->handleErrorCode(returnCode);
        }
        STATUS status = semGive(writecommMutex);
        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema when writing %s", param->getVarName().c_str());
        }
    }
    else
    {
        log_Err("RemoteSviReadStrategy::Recieved reply for unknown SMI command: %d", procID);
        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema recieved invalid response");
        }
    }
}

void RemoteSviReadStrategy::callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason)
{
    if (procID == SVI_PROC_GETVAL || procID == SVI_PROC_GETBLK)
    {
        SviProcGetBlkReply *castedReply = (SviProcGetBlkReply*) pReply;
        AbstractSviItem* param = (AbstractSviItem*) castedReply->getParameter();

        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema  when updating %s", param->getVarName().c_str());
        }
        curFailList.push_back(makePair(reason, param));
        try{
            param->handleErrorCode(reason);
        }
        catch (...){}
    }
    else if (procID == SVI_PROC_SETVAL || procID == SVI_PROC_SETBLK)
    {
        SviProcGetBlkReply *castedReply = (SviProcGetBlkReply*) pReply;
        AbstractSviItem* param = (AbstractSviItem*) castedReply->getParameter();

        STATUS status = semGive(writecommMutex);
        if (status != OK)
        {
            log_Err("RemoteSviReadStrategy::Could not release sema when writing %s", param->getVarName().c_str());
        }
        curWriteFailList.push_back(makePair(reason, param));
        try{
            param->handleErrorCode(reason);
        }
        catch(...){}
    }
    else
    {
        log_Err("Unknown call failed in updating remote SVI: %d -> failure: %x", procID, reason);
        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Info("RemoteSviReadStrategy::Could not release sema at call failed. Status: %i", status);
        }
    }
}

void RemoteSviReadStrategy::refresh() {

    if(pRefreshGroup == NULL) {
        log_Info("Did not refresh.. Group for refreshing is NULL");
        return;
    }
    if(pRefreshGroup->isInitialized() == false) {
        return;
    }

    if(items.size() == 0) {
        log_Info("Did NOT read from SVI for group %s, no valid items. ", pRefreshGroup->getName().c_str());
    }
    curFailList.clear();

    std::vector<AbstractSviItem*>::iterator ite;
    AbstractSviItem *pItem;
    for(ite = items.begin(); ite != items.end(); ++ite) {


        pItem = (*ite);

        if(pItem->isInitialized() == false){
            continue;
        }
        STATUS status = semTake(commMutex, WAIT_FOREVER);
        if (status != OK)
        {
            throw SviException("Could not get semaphor when connecting client");
        }


        if (this->pRefreshGroup->isActive() == false)
        {
            //We need to do this check here , since thread can be waiting in semTake above
            status = semGive(commMutex);
            if (status != OK)
            {
                throw SviException(
                        "Could not release semaphor when returning due to group is not active anymore");
            }
            refreshing = false;
            log_Info("RemoteSviReadStrategy::Setting refreshing to false");
            return;
        }
        if (pItem->isArrayItem())
        {
            getBlkCall.setAddr(pItem->getSviAddr());
            getBlkCall.setLength(pItem->getDataLength());
            getBlkReply.setParameter(pItem);
            pClient->sendCall(pItem->getModuleName(), &getBlkCall, &getBlkReply, this);

        }
        else
        {
            getValCall.setAddr(pItem->getSviAddr());
            getValReply.setParameter(pItem);
            pClient->sendCall(pItem->getModuleName(), &getValCall, &getValReply, this);
        }
    }

    //We need to wait for the response and let the last entry get updated, before returning
    semTake(commMutex, WAIT_FOREVER);
    semGive(commMutex);

    pRefreshGroup = NULL;
    refreshing = false;
}


void RemoteSviReadStrategy::writeValuesInternal()
{

    if(pWriteGroup == NULL) {
        log_Info("Did not write values.. Group for writing is NULL");
        return;
    }
    if(pWriteGroup->isInitialized() == false) {
        return;
    }
    curWriteFailList.clear();

    std::vector<AbstractSviItem*>::iterator ite;
    AbstractSviItem *pItem;
    for(ite = items.begin(); ite != items.end(); ++ite) {


        pItem = (*ite);

        if(pItem->isInitialized() == false || pItem->isWriteable() == false){
            continue;
        }

        STATUS status = semTake(writecommMutex, WAIT_FOREVER);
        if (status != OK)
        {
            throw SviException("Could not get semaphor when connecting client");
        }


        if (this->pWriteGroup->isActive() == false)
        {
            //We need to do this check here , since thread can be waiting in semTake above
            status = semGive(writecommMutex);
            if (status != OK)
            {
                throw SviException(
                        "Could not release semaphor when returning due to group is not active anymore");
            }
            writing = false;
            return;
        }

        if (pItem->isArrayItem())
        {
            setBlkCall.setSVIAddr(pItem->getSviAddr());
            setBlkCall.setData((UINT8*)pItem->getValueAddress(), pItem->getDataLength());
            setBlkReply.setParameter(pItem);
            pClient->sendCall(pItem->getModuleName(), &setBlkCall, &setBlkReply, this);
        }
        else
        {
            setValCall.setSVIAddr(pItem->getSviAddr());
            UINT32 val = 0;
            memcpy(&val, (UINT32*)pItem->getValueAddress(), 4);
            setValCall.setValue(val);
            setValReply.setParameter(pItem);
            pClient->sendCall(pItem->getModuleName(), &setValCall, &setValReply, this);
        }
    }

    pWriteGroup = NULL;
    writing = false;
}

TFailList RemoteSviReadStrategy::writeValues(AbstractSviGroup *pGroup){
    if (writing)
    {
        return TFailList();
    }

    pWriteGroup = dynamic_cast<RemoteSviGroup*>(pGroup);
    //We only start updating if the group is a remote group
    if (pWriteGroup != NULL)
    {
        writing = true;
        numOfWriteFailures = 0;
        this->writeItems = pGroup->getItems();
        if (items.size() == 0)
        {
            writing = false;
            return TFailList();
        }
        curWriteFailList.clear();
        writeValuesInternal();
    }
    else
    {
        log_Err("RemoteSviGroup needed in the RemoteSviReadStrategy for writing values remotely");
    }
    return curWriteFailList;
}

TFailList RemoteSviReadStrategy::readValues(AbstractSviGroup *pGroup)
{
    if(refreshing) {
        return TFailList();
    }
    pRefreshGroup = dynamic_cast<RemoteSviGroup*>(pGroup);
    //We only start updating if the group is a remote group
    if(pRefreshGroup != NULL ) {
        refreshing = true;
        numOfFailures = 0;
        this->items = pGroup->getItems();
        if(items.size() == 0) {
            refreshing = false;
            return TFailList();
        }
        refresh();
    }
    else {
        log_Err("RemoteSviGroup needed in the RemoteSviReadStrategy for getting values remotely");
    }
    return curFailList;
}
