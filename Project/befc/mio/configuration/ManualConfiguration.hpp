/**
 ********************************************************************************
 * @file     ManualConfiguration.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ManualConfiguration
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MANUALCONFIGURATION_HPP_
#define MANUALCONFIGURATION_HPP_

#include <vector>
#include "IOStrategy.hpp"
#include <configuration/MIOConfiguration.hpp>

class ManualConfiguration: public MIOConfiguration
{

public:

    ManualConfiguration(IOStrategy *pIOStrategy);

    void addCard(BasicIoModule *pCard);

    MIOConfiguration::ModuleList_t* getCards();

    BasicIoModule* getCard(UINT32 cardNbr);

    BasicChannel* getChannel(std::string symbolicName);

    void updateIn();

    void updateOut();

    ~ManualConfiguration();

protected:
    ManualConfiguration();

private:

    IOStrategy *pIOStrategy;
    MIOConfiguration::ModuleList_t *pCards;
};

#endif /* MANUALCONFIGURATION_HPP_ */
