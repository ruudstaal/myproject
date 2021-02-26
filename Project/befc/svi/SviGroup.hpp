/**
 ********************************************************************************
 * @file     SviGroup.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviGroup
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIGROUP_HPP_
#define SVIGROUP_HPP_

#include <SviGroupItemStrategy.hpp>
#include <map>
#include <vector>
#include <string>
#include <sstream>

#include "BEFCTypes.hpp"
#include "AbstractSviItem.hpp"
#include "SviItemModuleWrapper.hpp"
#include "AbstractSviGroup.hpp"

/**
 * @addtogroup SVI
 * @{
 */

typedef std::map<std::string, SviItemModuleWrapper*> TStrWrapMap;
typedef std::pair<std::string, SviItemModuleWrapper*> TStrWrapPair;

class BETask;
class SviSystem;

class SviGroup: public AbstractSviGroup
{
public:

    friend class ListReadStrategyImpl;
    friend class SingleItemStrategyImpl;

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviGroup
     *
     * @param[in]  name     The name of the group.
     * @param[in]  pTask    The pointer to the task in which it is created
     *******************************************************************************/
    SviGroup(std::string name, BETask* pTask);

    /**
     ********************************************************************************
     * @brief      Destructs the SviGroup
     *******************************************************************************/
    ~SviGroup();

    /**
     ********************************************************************************
     * @brief      Gets the name of the group
     *
     * @retval     The name of the group
     *******************************************************************************/
    std::string getName();

    /**
     ********************************************************************************
     * @brief      Returns if the group is active or not. If the group is active, it
     *             will update (read/write) the items in the group
     *
     * @retval     Whether the group is active or not
     *******************************************************************************/
    bool isActive();

    /**
     ********************************************************************************
     * @brief      Adds a SviItem to group
     *
     * @param[in]  pSviItem     The pointer to the SviItem to add
     * @retval     bool         False if group is active when adding, true if not.
     *******************************************************************************/
    bool addItem(AbstractSviItem* pSviItem);

    /**
     ********************************************************************************
     * @brief      Removes the item from group
     *
     * @param[in]  pSviItem     The pointer to the SviItem to remove
     * @retval     bool         True if items exists in group and has been removed. Otherwise false.
     *******************************************************************************/
    bool removeItem(AbstractSviItem* pSviItem);

    /**
     ********************************************************************************
     * @brief      Returns if the group is active or not. If the group is active, it
     *             will update (read/write) the items in the group
     *
     * @param[in]  active       The new active state for the group
     *******************************************************************************/
    void setActive(bool active);

    /**
     ********************************************************************************
     * @brief      Trigger a refresh of the group. All items added to the group will
     *             get updated values from SVI
     *******************************************************************************/
    void refresh(void);

    /**
     ********************************************************************************
     * @brief      Trigger a write of the group. All the items current state will be
     *             written to the SVI layer
     *******************************************************************************/
    void updateOut();

    /**
     ********************************************************************************
     * @brief      Returns the AbstractSviItems in the group.
     *
     * @retval     std::vector  A vector containing AbstractSviItems in the group
     *******************************************************************************/
    std::vector<AbstractSviItem*> getItems();

    /**
     ********************************************************************************
     * @brief      Sets the SVI system used by this group
     *
     * @param[in]  pSystem     The pointer to the SviSystem for the group to use
     *******************************************************************************/
    void setSviSystem(SviSystem *pSystem);

    /**
     ********************************************************************************
     * @brief      Resets the group. This means that the items added to the group
     *             will be initialized again.
     *******************************************************************************/
    void reset();

private:

    std::string name;

    bool initialized;

    bool active;

    BETask *pTask;

    TStrWrapMap *pMap;

    SviGroupItemStrategy *itemStrategy;

    SviSystem *pSviSystem;

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviGroup
     *
     *******************************************************************************/
    SviGroup();

    /**
     ********************************************************************************
     * @brief      Initializes the SviGroup
     *
     * @throws     SviException     If SviGroup cannot be initialized due to illegal module state.
     *******************************************************************************/
    VOID init(void);

    /**
     ********************************************************************************
     * @brief      Helper function for initializing an SviItem
     *
     * @param[in]  pItem            The pointer to the SviItem
     * @param[in]  pLib             The pointer to the library
     * @throws     SviException     If initilization fails.
     *******************************************************************************/
    VOID initializeItem(AbstractSviItem *pItem, pLib);

    /**
     ********************************************************************************
     * @brief      Helper function for getting the lib address. (Handled by the module)
     *
     * @param[in]  moduleName     The name of the module.
     * @retval     pLib           The pointer for the module.
     *******************************************************************************/
    pLib getLibAddress(std::string moduleName);

    /**
     ********************************************************************************
     * @brief      Since addresses for software modules are cached, references can be
     *             invalid if a software module is re-deployed. This function will renew
     *             the references
     *
     * @param[in]  moduleName     The name of the module.
     * @retval     pLib           The pointer for the module.
     *******************************************************************************/
    pLib renewLibAddress(std::string moduleName);

    /**
     ********************************************************************************
     * @brief      Helper function to log a stringstream
     *
     * @param[in]  pStream     The pointer to the stringstream
     *******************************************************************************/
    VOID log(std::stringstream *pStream);
    /**
     ********************************************************************************
     * @brief      Helper function to log exception
     *
     * @param[in]  e     Reference to the exception
     *******************************************************************************/
    VOID logException(std::exception const& e);

    SviGroup(const SviGroup& that); /** no copy */

    SviGroup& operator=(SviGroup const&); /** no assign */

    bool isInitialized();

    bool hasValidItems();
};
/** @} */

#endif  /*SVIGROUP_HPP_*/
