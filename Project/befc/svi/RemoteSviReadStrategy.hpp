/*
 * RemoteSviReadStrategy.hpp
 *
 *  Created on: Jan 25, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_REMOTESVIREADSTRATEGY_HPP_
#define BEFC_SVI_REMOTESVIREADSTRATEGY_HPP_

#include "svi/SviProcGetValCall.hpp"
#include "svi/SviProcGetValReply.hpp"
#include "svi/SviProcGetBlkReply.hpp"
#include "svi/SviProcGetBlkCall.hpp"
#include "svi/SviProcSetValCall.hpp"
#include "svi/SviProcSetValReply.hpp"
#include "svi/SviProcSetBlkReply.hpp"
#include "svi/SviProcSetBlkCall.hpp"
#include "RemoteSviGroup.hpp"

class RemoteSviReadStrategy: public SviGroupItemStrategy, public SmiReplyListener
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of RemoteSviReadStrategy. This instance will
     *             make use of setVal and getVal, which means that for every item in
     *             the group, a SMI call will be sent for getVal and setVal.
     *
     * @param[in]  SmiClient   Pointer to the SMI client.
     *******************************************************************************/
    RemoteSviReadStrategy(SmiClient *pClient);

    TFailList readValues(AbstractSviGroup *pGroup);

    TFailList writeValues(AbstractSviGroup *pGroup);

    void replyRecieved(SmiCallReply *pReply, UINT32 procID);

    void callFailed(UINT32 procID, SINT32 reason){}

    void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason);

    /**
     ********************************************************************************
     * @brief      Destroys the RemoteSviReadStrategy
     *******************************************************************************/
    virtual ~RemoteSviReadStrategy();

private:
    SmiClient *pClient;
    bool refreshing;
    bool writing;
    RemoteSviGroup *pRefreshGroup;
    RemoteSviGroup *pWriteGroup;

    SviProcGetValCall getValCall;
    SviProcGetValReply getValReply;
    SviProcGetBlkCall getBlkCall;
    SviProcGetBlkReply getBlkReply;

    SviProcSetValCall setValCall;
    SviProcSetValReply setValReply;
    SviProcSetBlkCall setBlkCall;
    SviProcSetBlkReply setBlkReply;



    std::vector<AbstractSviItem*> items;

    std::vector<AbstractSviItem*> writeItems;

    TFailList curFailList;

    TFailList curWriteFailList;

    UINT32 numOfFailures;

    UINT32 numOfWriteFailures;

    //For initializing communication which needs to be sync.
    SEM_ID commMutex;

    SEM_ID writecommMutex;

    void refresh();

    void writeValuesInternal();
};

#endif /* BEFC_SVI_REMOTESVIREADSTRATEGY_HPP_ */
