/**
 ********************************************************************************
 * @file     SviItemModulewrapper.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviItemModulewrapper
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIITEMMODULEWRAPPER_HPP_
#define SVIITEMMODULEWRAPPER_HPP_

#include <vector>
#include "SviItem.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SviItemModuleWrapper
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of SviItemModuleWrapper
     *******************************************************************************/
    SviItemModuleWrapper();

    /**
     ********************************************************************************
     * @brief      Destructs the SviItemModuleWrapper
     *******************************************************************************/
    ~SviItemModuleWrapper();

    /**
     ********************************************************************************
     * @brief      Gets the library pointer
     *
     * @retval     The Library pointer
     *******************************************************************************/
    pLib getLib(VOID)
    {
        return lib;
    }

    /**
     ********************************************************************************
     * @brief      Gets the AbstractSviItems in the wrapper
     *
     * @retval     The AbstractSviItems in a std::vector
     *******************************************************************************/
    std::vector<AbstractSviItem*>* getItems(VOID)
    {
        return pItems;
    }

    /**
     ********************************************************************************
     * @brief      Sets the items which are related to the module.
     *
     * @param[in]  pItems                   The pointer to the items
     * @throws     std::invalid_argument    If the argument is NULL
     *******************************************************************************/
    VOID setItems(std::vector<AbstractSviItem*> *pItems);

    /**
     ********************************************************************************
     * @brief      Sets the pointer to the module
     *
     * @param[in]  lib                      The pointer to the module
     * @throws     std::invalid_argument    If the argument is NULL
     *******************************************************************************/
    VOID setLib(pLib lib);

private:

    std::vector<AbstractSviItem*> *pItems;

    pLib lib;
};
/** @} */

#endif  /*SVIITEMMODULEWRAPPER_HPP_*/
