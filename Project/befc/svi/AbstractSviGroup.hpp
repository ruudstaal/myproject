/*
 * AbstractSviGroup.hpp
 *
 *  Created on: Jan 23, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_VALUE_ABSTRACTSVIGROUP_HPP_
#define BEFC_SVI_VALUE_ABSTRACTSVIGROUP_HPP_

#include <string>
#include <vector>
#include "SviItem.hpp"
#include "SviGroupEventListener.hpp"
#include "GenericSviItem.hpp"
#include "SviBlkItem.hpp"
#include <utility>
#include <list>


typedef std::pair<SINT32, AbstractSviItem*> TErrPair;

typedef std::list<TErrPair> TFailList;


class SviGroupItemStrategy;


/**
 ********************************************************************************
 * @brief      AbstractSviGroup is a a base class, which is used for accessing
 *             SVI variables from local and remote software modules.
 *
 *******************************************************************************/
class AbstractSviGroup
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of AbstractSviGroup
     *
     *******************************************************************************/
    AbstractSviGroup();

    /**
     ********************************************************************************
     * @brief      Gets the name of the group
     *
     * @retval     The name of the group
     *******************************************************************************/
    virtual std::string getName() = 0;

    /**
     ********************************************************************************
     * @brief      Returns if the group is active or not. If the group is active, it
     *             will update (read/write) the items in the group
     *
     * @retval     Whether the group is active or not
     *******************************************************************************/
    virtual bool isActive() = 0;

    /**
     ********************************************************************************
     * @brief      Returns if the group is active or not. If the group is active, it
     *             will update (read/write) the items in the group
     *
     * @param[in]  active       The new active state for the group
     *******************************************************************************/
    virtual void setActive(bool active) = 0;

    /**
     ********************************************************************************
     * @brief      Returns the AbstractSviItems in the group.
     *
     * @retval     std::vector  A vector containing AbstractSviItems in the group
     *******************************************************************************/
    virtual std::vector<AbstractSviItem*> getItems() = 0;

    /**
     ********************************************************************************
     * @brief      Inserts an AbstractSviItem into the group. Consider using the
     *             template functions instead.
     *
     * @param[in]  pSviItem     A pointer to the AbstractSviItem
     *******************************************************************************/
    virtual bool addItem(AbstractSviItem* pSviItem) = 0;

    /**
     ********************************************************************************
     * @brief      Inserts an GenericSviItem<T> to the group. This function should be
     *             used for simple values like SVI_F_UINT32, SVI_F_UINT64, etc. It cannot
     *             be used for added array types, where type is SVI_F_BLK.
     *
     * @retval     A pointer to GenericSviItem<T>
     *******************************************************************************/
    template<typename T>
    GenericSviItem<T>* addValueItem(std::string moduleName, std::string varName)
    {
        GenericSviItem<T> *res = new GenericSviItem<T>(moduleName, varName);
        addItem(res);
        return res;
    }

    /**
     ********************************************************************************
     * @brief      Inserts an SviBlkItem<T> to the group. This function should be
     *             used for array / BLK values where type is SVI_F_BLK.
     *
     * @retval     A pointer to SviBlkItem<T>
     *******************************************************************************/
    template<typename T>
    SviBlkItem<T>* addArrayItem(std::string moduleName, std::string varName)
    {
        SviBlkItem<T> *res = new SviBlkItem<T>(moduleName, varName);
        addItem(res);
        return res;
    }

    /**
     ********************************************************************************
     * @brief      Trigger a refresh of the group. All items added to the group will
     *             get updated values from SVI
     *******************************************************************************/
    virtual void refresh() = 0;

    /**
     ********************************************************************************
     * @brief      Trigger a write of the group. All the items current state will be
     *             written to the SVI layer
     *******************************************************************************/
    virtual void updateOut() = 0;

    /**
     ********************************************************************************
     * @brief      Resets the group. This means that the items added to the group
     *             will be initialized again.
     *******************************************************************************/
    virtual void reset() = 0;

    /**
     ********************************************************************************
     * @brief      Adds a SviGroupEventListener to the group, to get events from the
     *             group
     *
     * @param[in]  pListener     A pointer the the SviGroupEventListener
     *******************************************************************************/
    void addEventListener(SviGroupEventListener *pListener);

    /**
     ********************************************************************************
     * @brief      Gets the current state of the group
     *
     * @retval     The state of the group as a GroupState enum.
     *******************************************************************************/
    const SviGroupEventListener::GroupState getState(){return state;}

    /**
     ********************************************************************************
     * @brief      Destroys the AbstractSviGroup
     *
     *******************************************************************************/
    virtual ~AbstractSviGroup(){};

    /**
     ********************************************************************************
     * @brief      Overload of the == operator. If modulename and varname is the same,
     *             operator will return true.
     *
     *******************************************************************************/
    bool operator==(AbstractSviGroup &other)
    {
        if (this->getName() == other.getName())
        {
            return true;
        }
        return false;
    }

    /**
     ********************************************************************************
     * @brief      Overload of the == operator. Uses the equals operator of the template
     *             type
     *
     *******************************************************************************/
    bool operator==(std::string &other)
    {
        return this->getName() == other;
    }

protected:

    void notifyAboutState(SviGroupEventListener::GroupState newState);

    void notifyAboutGroupRefresh();

    void notifyAboutItemFailed(SINT32 reason, AbstractSviItem *pItem);

    void notifyFailList(TFailList list);

    void setState(const SviGroupEventListener::GroupState newState);

private:

    std::vector<SviGroupEventListener*> listeners;

    SviGroupEventListener::GroupState state;

};

#endif /* BEFC_SVI_VALUE_ABSTRACTSVIGROUP_HPP_ */
