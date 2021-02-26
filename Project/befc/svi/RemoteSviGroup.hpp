/*
 * RemoteSviGroup.hpp
 *
 *  Created on: Jan 23, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_REMOTESVIGROUP_HPP_
#define BEFC_SVI_REMOTESVIGROUP_HPP_

#include <map>
#include <vector>
#include <AbstractSviGroup.hpp>
#include <SviGroupEventListener.hpp>
#include <SviGroupItemStrategy.hpp>
#include "SmiClient.hpp"
#include "BETask.hpp"
#include "../calls/svi/SviProcGetXAddrCall.hpp"
#include "../calls/svi/SviProcGetXAddrReply.hpp"
#include "ResProcSysInfoCall.hpp"
#include "ResProcSysInfoReply.hpp"
#include "SmiReplyListener.hpp"

typedef std::map<std::string, std::vector<AbstractSviItem*> > TStrVecItems;
typedef std::pair<std::string, std::vector<AbstractSviItem*> > TStrVecPair;

class RemoteSviGroup: public AbstractSviGroup,
        SMIClientEventListener,
        SmiReplyListener,
        SviItemEventListener
{
public:

    friend class RemoteSviReadStrategy;
    friend class RemoteSviListReadStrategy;
    friend class ConcurrentRemoteSviReadStrategy;

    RemoteSviGroup(std::string name, BETask *pTask, std::string ip, std::string username,
            std::string password);

    /**
     ********************************************************************************
     * @brief      Removes the item from the internal lists
     *
     * @param[in]  pSviItem     A pointer to the AbstractSviItem to remove
     *******************************************************************************/
    bool removeItem(AbstractSviItem* pSviItem);

    /**
     ********************************************************************************
     * @brief      Returns the ip to the remote controller, which the group is updating
     *             from.
     *
     * @retval     The ip as std::string
     *******************************************************************************/
    const std::string& getIp() const
    {
        return ip;
    }

    /**
     ********************************************************************************
     * @brief      Returns the username to the remote controller, which the group is updating
     *             from.
     *
     * @retval     The username as std::string
     *******************************************************************************/
    const std::string& getUsername() const
    {
        return username;
    }

    /**
     ********************************************************************************
     * @brief      Destroys the RemoteSviGroup
     *******************************************************************************/
    ~RemoteSviGroup();

    /** Functions implemented from AbstractSviGroup */

    bool addItem(AbstractSviItem* pSviItem);

    std::string getName();

    bool isActive();

    void setActive(bool active);

    void refresh();

    void updateOut();

    std::vector<AbstractSviItem*> getItems();

    void reset();

protected:

    void replyRecieved(SmiCallReply *pReply, UINT32 procID);

    void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason);

    void callFailed(UINT32 procID, SINT32 reason)
    {
    }

    void eventRecieved(ClientState state);

    //SVI items related callbacks

    void dataQualityChanged(AbstractSviItem *pItem, DataQuality oldQuality, DataQuality newQuality);

    void writeFailed(AbstractSviItem *pItem, SINT32 failure);

private:
    std::string name;
    bool initialized;
    bool active;
    BETask *pTask;

    std::string ip;
    std::string username;
    std::string password;
    TStrVecItems items;
    bool doInit;
    bool clientConnected;
    bool commActive;

    SmiClient *pClient;
    SviGroupItemStrategy *pItemStrategy;
    SviProcGetXAddrCall getAddrCall;
    SviProcGetXAddrReply getAddrReply;

    ResProcSysInfoCall getSysInfoCall;
    ResProcSysInfoReply getSysInfoReply;

    //For initializing communication which needs to be sync.
    SEM_ID commMutex;

    bool connecting;

    bool remoteSystemReady;

    bool waitingForRemoteSystem;

    void init();

    bool isInitialized();

    void deleteVector(std::vector<AbstractSviItem*> list);

    void initializeItem(AbstractSviItem *pItem);

    void setStateInternal(SviGroupEventListener::GroupState newState);

    bool sortItems(AbstractSviItem* item1, AbstractSviItem* item2);

    void setInitialized(bool initialized);

    bool hasValidItems();

    void getRemoteSysInfo();
};

#endif /* BEFC_SVI_REMOTESVIGROUP_HPP_ */
