/*
 * RemoteSviListReadStrategy.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#include <RemoteSviListReadStrategy.hpp>
#include "SviException.hpp"
#include "SmiException.hpp"
#include "SviSystemException.hpp"
#include "RemoteSviGroup.hpp"

RemoteSviListReadStrategy::RemoteSviListReadStrategy(SmiClient *pClient) : pClient(pClient), pCurrentAddressArray(NULL), writeHelper(
        RemoteSviWriteHelper(pClient))
{
    commMutex = semBCreate (SEM_Q_PRIORITY, SEM_FULL);
}

RemoteSviListReadStrategy::~RemoteSviListReadStrategy()
{
    semDelete(commMutex);
}

void RemoteSviListReadStrategy::writeDirtyItems(AbstractSviGroup *pGroup) {
    std::vector<AbstractSviItem*> items = pGroup->getItems();
    std::vector<AbstractSviItem*>::iterator ite;
    AbstractSviItem *pRemoteItem;
    std::vector<AbstractSviItem*> toWrite;

    for (ite = items.begin(); ite != items.end(); ++ite) {
        pRemoteItem = (*ite);
        if(pRemoteItem == NULL) {
            continue;
        }

        if(pRemoteItem->isDirty() && !pRemoteItem->isFailed() && pRemoteItem->isInitialized() && pRemoteItem->isWriteable()) {
            if(pGroup->isActive() == false) {
                return; //State can be set while waiting for helper to return
            }
            toWrite.push_back(pRemoteItem);
        }
    }
    writeHelper.writeItems(toWrite);
}


TFailList RemoteSviListReadStrategy::writeValues(AbstractSviGroup *pGroup) {
    writeDirtyItems(pGroup);
    return TFailList();

}

TFailList RemoteSviListReadStrategy::getFailListFromVector(std::vector<AbstractSviItem*> items, SINT32 errorCode) {
    TFailList res;
    std::vector<AbstractSviItem*>::iterator ite;
    for (ite = items.begin(); ite != items.end(); ++ite) {
        res.push_back(makePair(errorCode, (*ite)));
    }
    return res;

}

TFailList RemoteSviListReadStrategy::readValues(AbstractSviGroup *pGroup)
{
    RemoteSviGroup* pRemoteGroup = dynamic_cast<RemoteSviGroup*>(pGroup);
    if (pRemoteGroup == NULL)
    {
        log_Err(
                "RemoteSviListReadStrategy used for group other than remote controller. Group %s not refreshed",
                pGroup->getName().c_str());
        return TFailList();
    }


    //This function call will return the list of items to be refreshed sorted in module order
    std::vector<AbstractSviItem*> items = pRemoteGroup->getItems();

    std::vector<AbstractSviItem*>::iterator itetest;
    UINT32 currentIndex = 0;
    UINT32 currentCount = 0;
    std::vector<AbstractSviItem*>::iterator ite;


    std::string module;
    if(items.size() > 0) {
        module = items.at(0)->getModuleName();
    }

    for (ite = items.begin(); ite != items.end(); ++ite)
    {
        if((*ite)->isInitialized() == false){
            continue;
        }

        //Smi calls has to be specific sent to SW modules. Gather all we can to one SW module and send
        if(module.compare((*ite)->getModuleName()) != 0) {
            currentCount = 0;
            getRemoteValues(module, currentItems); //function will lock
            currentItems.clear();
            module = (*ite)->getModuleName();
            if (getValLstReply.getReturnCode() != SVI_E_OK)
            {
                return getFailListFromVector(currentItems, getValLstReply.getReturnCode());
            }
        }


        currentItems.push_back((*ite));
        currentIndex++;
        currentCount++;

        if (currentCount == MAXITEMSINCALL)
        {
            currentCount = 0;
            getRemoteValues(module, currentItems); //function will lock
            currentItems.clear();
            if(getValLstReply.getReturnCode() != SVI_E_OK) {
                return getFailListFromVector(currentItems, getValLstReply.getReturnCode());
            }
        }

    }

    if (currentCount > 0)
    {
        getRemoteValues(module, currentItems); //function will lock
        currentItems.clear();
        currentIndex = 0;
        currentCount = 0;
        if (getValLstReply.getReturnCode() != SVI_E_OK)
        {
            return getFailListFromVector(currentItems, getValLstReply.getReturnCode());
        }
    }
    return TFailList();
}

void RemoteSviListReadStrategy::getRemoteValues(std::string module, std::vector<AbstractSviItem*> list)
{
    STATUS status = semTake(commMutex, WAIT_FOREVER);
    if (status != OK)
    {
        throw SviException("Could not get updating remote svi list");
    }

    if(pCurrentAddressArray != NULL) {
        SAFE_DELETE(pCurrentAddressArray);
    }

    pCurrentAddressArray = new SVI_ADDR[list.size()];

    int index = 0;
    for (std::vector<AbstractSviItem*>::iterator ite = list.begin(); ite != list.end(); ++ite){
        pCurrentAddressArray[index] = (*ite)->getSviAddr();
        index++;
    }

    getValLstCall.setAddresses(pCurrentAddressArray, list.size());
    getValLstReply.setListSize(list.size());
    getValLstReply.setParameter((void*)&list);

    try{
        pClient->sendCall(module, &getValLstCall, &getValLstReply, this);

        status = semTake(commMutex, WAIT_FOREVER);
        if (status != OK)
        {
            throw SviException("Could not get updating remote svi list");
        }
    }
    catch(SmiException &smiException) {
        log_Err("SMI handler returned exception at refreshing SVI list. %s", smiException.what());
    }
    catch(...) {
        log_Err("Unknown failure sending getValLst call");
    }
    SAFE_DELETE(pCurrentAddressArray);
    semGive(commMutex);
}


void RemoteSviListReadStrategy::replyRecieved(SmiCallReply *pReply, UINT32 procID)
{
    if (procID == SVI_PROC_GETVALLST)
    {
        SviProcGetValLstReply *castedReply = (SviProcGetValLstReply*) pReply;
        std::vector<AbstractSviItem*> *pItems = (std::vector<AbstractSviItem*>*) castedReply->getParameter();

        UINT32 *pValues = castedReply->getValues();
        if (castedReply->getListSize() != pItems->size())
        {
            log_Err("Size of retrieved values is different from list size. %d != %d", castedReply->getListSize(), pItems->size());
            return;
        }

        if (castedReply->getReturnCode() != SVI_E_OK) {
            log_Err("Error occured when getting SVI valueS remotely. %d", castedReply->getReturnCode());
            return;
        }

        AbstractSviItem *pItem;
        for (std::vector<AbstractSviItem*>::iterator ite = pItems->begin(); ite != pItems->end(); ++ite)
        {
            pItem = (*ite);

            if (castedReply->getReturnCode() == SVI_E_OK)
            {
                pItem->updateInternalValue(*pValues);
                pValues++;
            }
            else
            {
                STATUS status = semGive(commMutex);
                if (status != OK)
                {
                    throw SviException("Could not release semaphor when reading remote SVI list");
                }

                //We cannot say which item failed, so none of them is notified - instead exception.
                std::stringstream ss;
                throw SviSystemException("Could not update Remote group. ", castedReply->getReturnCode());
            }

            pItem->handleErrorCode(castedReply->getReturnCode());
        }
    }

    STATUS status = semGive(commMutex);
    if (status != OK)
    {

        log_Info("RemoteSviListReadStrategy::Could not release sema  when updating Svi list");
        throw SviException("Could not release semaphor when reading remote SVI list");
    }

}

void RemoteSviListReadStrategy::callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason)
{
    if (procID == SVI_PROC_GETVALLST)
    {
        SviProcGetValLstReply *castedReply = (SviProcGetValLstReply*) pReply;
        std::vector<AbstractSviItem*> *pItems = (std::vector<AbstractSviItem*>*) castedReply->getParameter();
        for (std::vector<AbstractSviItem*>::iterator ite = pItems->begin(); ite != pItems->end(); ++ite)
        {

            (*ite)->handleErrorCode(reason);
        }

    }

    STATUS status = semGive(commMutex);
    if (status != OK)
    {
        log_Info("RemoteSviReadStrategy::Could not release sema  when updating SVI list");
        throw SviException("Could not release semaphor when reading remote SVI var");
    }

}
