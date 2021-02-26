/*
 * RemoteSviWriteHelper.hpp
 *
 *  Created on: Mar 21, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_REMOTESVIWRITEHELPER_HPP_
#define BEFC_SVI_REMOTESVIWRITEHELPER_HPP_

#include "SmiClient.hpp"
#include "svi/SviProcSetValLstCall.hpp"
#include "svi/SviProcSetValLstReply.hpp"
#include "semLib.h"
#include "svi.h"


class AbstractSviItem;

class RemoteSviWriteHelper: public SmiReplyListener
{
public:

    static const UINT32 MAXITEMSINCALL = 64;

    /**
     ********************************************************************************
     * @brief      Creates an instance of RemoteSviWriteHelper. This instance will
     *             write values to the SVI layer using setValLst.
     *
     * @param[in]  SmiClient   Pointer to the SMI client.
     *******************************************************************************/
    RemoteSviWriteHelper(SmiClient *pClient);

    /**
     ********************************************************************************
     * @brief      Write item values to the SVI layer using SMI.
     *
     * @param[in]  toWrite   std::vector containing AbstractSviItems to write
     *******************************************************************************/
    void writeItems(std::vector<AbstractSviItem*> toWrite);

    /**
     ********************************************************************************
     * @brief      Destroys the RemoteSviWriteHelper
     *
     *******************************************************************************/
    virtual ~RemoteSviWriteHelper();

private:

    void replyRecieved(SmiCallReply *pReply, UINT32 procID);

    void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason);

    void callFailed(UINT32 procID, SINT32 reason){}

    void sendListCall(std::string module);

    SmiClient *pSmiClient;

    struct CallItemPair
    {
        AbstractSviItem *pItem;
        SmiCall *pCall;
    };

    //For initializing communication which needs to be sync.
    SEM_ID commMutex;

    SviProcSetValLstCall call;

    SviProcSetValLstReply reply;

    UINT32 currentIndex;

    AbstractSviItem* currentItems[MAXITEMSINCALL];

    SVI_ADDR currentAdr[MAXITEMSINCALL];

    UINT32 currentValues[MAXITEMSINCALL];

};

#endif /* BEFC_SVI_REMOTESVIWRITEHELPER_HPP_ */
