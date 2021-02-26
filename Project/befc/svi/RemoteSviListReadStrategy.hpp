/*
 * RemoteSviListReadStrategy.hpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SVI_REMOTESVILISTREADSTRATEGY_HPP_
#define RES_BEFC_SVI_REMOTESVILISTREADSTRATEGY_HPP_

#include <SviGroupItemStrategy.hpp>
#include "SmiClient.hpp"
#include "../smi/calls/svi/SviProcGetValLstCall.hpp"
#include "../smi/calls/svi/SviProcGetValLstReply.hpp"
#include "SmiReplyListener.hpp"
#include "AbstractSviGroup.hpp"
#include "RemoteSviWriteHelper.hpp"

class RemoteSviListReadStrategy: public SviGroupItemStrategy, public SmiReplyListener
{
public:
    static const UINT32 MAXITEMSINCALL = 64;

    /**
     ********************************************************************************
     * @brief      Creates an instance of RemoteSviListReadStrategy. This instance will
     *             make use of setValLst and getValList for optimizing setting up to 64
     *             SVI values with just one SMI call.,
     *
     * @param[in]  SmiClient   Pointer to the SMI client.
     *******************************************************************************/
    RemoteSviListReadStrategy(SmiClient *pClient);

    TFailList readValues(AbstractSviGroup *pGroup);

    TFailList writeValues(AbstractSviGroup *pGroup);

    void replyRecieved(SmiCallReply *pReply, UINT32 procID);

    void callFailed(UINT32 procID, SINT32 reason){}

    void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason);

    /**
     ********************************************************************************
     * @brief      Destroys the RemoteSviListReadStrategy
     *******************************************************************************/
    virtual ~RemoteSviListReadStrategy();

private:

    void getRemoteValues(std::string module, std::vector<AbstractSviItem*> list);

    void writeDirtyItems(AbstractSviGroup *pGroup);

    TFailList getFailListFromVector(std::vector<AbstractSviItem*> vec, SINT32 errorCode);

    SmiClient *pClient;

    SEM_ID commMutex;

    SviProcGetValLstCall getValLstCall;

    SviProcGetValLstReply getValLstReply;

    std::vector<AbstractSviItem*> currentItems;

    SVI_ADDR *pCurrentAddressArray;

    RemoteSviWriteHelper writeHelper;

};

#endif /* RES_BEFC_SVI_REMOTESVILISTREADSTRATEGY_HPP_ */
