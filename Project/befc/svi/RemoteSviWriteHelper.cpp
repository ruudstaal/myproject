/*
 * RemoteSviWriteHelper.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: madsen
 */

#include <RemoteSviWriteHelper.hpp>
#include "../smi/calls/svi/SviProcSetValCall.hpp"
#include "../smi/calls/svi/SviProcSetValReply.hpp"
#include "../smi/calls/svi/SviProcSetBlkCall.hpp"
#include "../smi/calls/svi/SviProcSetBlkReply.hpp"
#include "AbstractSviItem.hpp"
#include "SmiException.hpp"
#include <cstring>

RemoteSviWriteHelper::RemoteSviWriteHelper(SmiClient *pClient) :
        currentIndex(0)
{
    this->pSmiClient = pClient;

    /* create a binary semaphore that is initially full */
    commMutex = semBCreate(SEM_Q_PRIORITY, SEM_FULL);

    memset(currentItems,0, MAXITEMSINCALL * 4);
    memset(currentAdr,0, MAXITEMSINCALL * sizeof(SVI_ADDR));
    memset(currentValues,0, MAXITEMSINCALL * sizeof(UINT32));

}

RemoteSviWriteHelper::~RemoteSviWriteHelper()
{
    semDelete(commMutex);
}

void RemoteSviWriteHelper::writeItems(std::vector<AbstractSviItem*> toWrite)
{
    std::string module = "";
    if (toWrite.size() > 0)
    {
        module = toWrite.at(0)->getModuleName();
    }

    for (std::vector<AbstractSviItem*>::iterator ite = toWrite.begin(); ite != toWrite.end(); ++ite)
    {
        if ((*ite)->isInitialized() && (*ite)->isDirty() && !(*ite)->isFailed())
        {

            //Smi calls has to be specific sent to SW modules. Gather all we can to one SW module and send
            if (module.compare((*ite)->getModuleName()) != 0)
            {
                sendListCall(module); //function will lock
                currentIndex = 0;
                module = (*ite)->getModuleName();
            }

            currentAdr[currentIndex] = (*ite)->getSviAddr();
            currentItems[currentIndex] = (*ite);
            currentValues[currentIndex] = *((UINT32*) (*ite)->getValueAddress());
            currentIndex++;

            if (currentIndex == MAXITEMSINCALL)
            {
                sendListCall(module);
                currentIndex = 0;
            }
        }
    }

    if (currentIndex > 0)
    {
        sendListCall(module);
        currentIndex = 0;
    }
}

void RemoteSviWriteHelper::sendListCall(std::string module)
{
    STATUS status = semTake(commMutex, WAIT_FOREVER);
    if (status != OK)
    {
        std::stringstream ss;
        ss << "Could not get Mutex for writing remote SVI values. Reason : " << status;
        log_Err("%s", ss.str().c_str());
        throw SviException(ss.str().c_str());
    }

    try
    {
        call.setValues(currentAdr, currentValues, currentIndex);
        pSmiClient->sendCall(module, &call, &reply, this);
        status = semTake(commMutex, WAIT_FOREVER);
        if (status != OK)
        {
            throw SviException("Could not get Mutex for writing remote SVI values");
        }
    }
    catch (SmiException &smiException)
    {
        log_Err("SMI handler returned exception at writing SVI list. %s", smiException.what());
    }
    catch (...)
    {
        log_Err("Unknown failure sending setValLst call");
    }

    status = semGive(commMutex);
}

void RemoteSviWriteHelper::replyRecieved(SmiCallReply *pReply, UINT32 procID)
{
    if (procID == SVI_PROC_SETBLK)
    {
        SviProcSetBlkReply *pCastedReply = (SviProcSetBlkReply*) pReply;
        if (pCastedReply->useMultiBlk())
        {
            log_Info("Recieved MultiBLK reponse when writing remote SVI - NOT SUPPORTED. ");
            //MUltiBLK calls should be used for writing larger amounts of data (split calls.. ).
        }
    }

    if (procID == SVI_PROC_SETVALLST)
    {

        SINT32 returncode = pReply->getReturnCode();
        if (returncode == SMI_E_OK)
        {
            for (UINT32 i = 0; i < currentIndex; ++i)
            {
                currentItems[i]->setDirty(false);
            }
        }

        //We need to release before notifying. This could potentially bind the SMI handler.
        STATUS status = semGive(commMutex);
        if (status != OK)
        {
            log_Err("Could not release mutex for handling of Write SVI values returns. %d", status);
        }

        if (returncode != SMI_E_OK)
        {
            for (UINT32 i = 0; i < currentIndex; ++i)
            {
                currentItems[i]->notifyFailedWrite(returncode);

            }
        }
    }
}

void RemoteSviWriteHelper::callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason)
{

    if (procID != SVI_PROC_SETVAL && procID != SVI_PROC_SETBLK && procID != SVI_PROC_SETVALLST)
    {
        log_Err("Got write call failed response for unknown call. %d, err: %d", procID, reason);
        return;
    }

    STATUS status = semGive(commMutex);
    if (status != OK)
    {
        log_Err("RemoteSviWriteHelper::Releasing mutex at unknown answer failed . %d", status);
    }

    if (procID == SVI_PROC_SETBLK)
    {
        for (UINT32 i = 0; i < currentIndex; ++i)
        {
            currentItems[i]->setDirty(false);
            currentItems[i]->notifyFailedWrite(reason);

        }
    }
}
