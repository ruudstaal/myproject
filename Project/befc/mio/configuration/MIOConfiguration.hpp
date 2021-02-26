/**
 ********************************************************************************
 * @file     MIOConfiguration.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of MIOConfiguration
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MIOCONFIGURATION_HPP_
#define MIOCONFIGURATION_HPP_

#include <list>
#include <vector>
#include "mcpp.hpp"
#include "../common/base/BasicIoModule.hpp"

class BasicIoModule;

class MIOConfiguration
{

public:

    /**
     * List of Modules
     */
    typedef std::list<BasicIoModule*> ModuleList_t;

    /**
     ********************************************************************************
     * @brief      add a card to the configuration. WARNING: Cards are NOT deleted
     * when MIOConfiguration instance is deleted.
     *
     *
     * @param[in]  pModule          Pointer to BasicIoModule (representing physical card)
     * @throws     invalid_argument If a card with same module number already exists.
     *******************************************************************************/
    virtual void addCard(BasicIoModule *pModule) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the list of configured modules (physical cards)
     *
     * @retval     The configured cards as std::list
     *******************************************************************************/
    virtual ModuleList_t* getCards() = 0;

    /**
     ********************************************************************************
     * @brief      Gets the list of configured modules (physical cards)
     *
     * @retval     The configured cards as std::list
     *******************************************************************************/
    virtual BasicIoModule* getCard(UINT32 cardNbr) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the channel related to the symbolic name
     *
     * @retval     The BasicChannel if the symbolic exists, else NULL is returned
     *******************************************************************************/
    virtual BasicChannel* getChannel(std::string symbolicName) = 0;

    /**
     ********************************************************************************
     * @brief      This function updates all the cards which has been added.
     *******************************************************************************/
    virtual void updateIn() = 0;

    /**
     ********************************************************************************
     * @brief      This function writes values from the configured cards to the actual
     * 			   HW module
     *******************************************************************************/
    virtual void updateOut() = 0;

    virtual ~MIOConfiguration()
    {
    }
    ;

protected:

    MIOConfiguration()
    {
    }
    ;

};

#endif /** MIOCONFIGURATION_HPP_ */
