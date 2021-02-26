/**
 ********************************************************************************
 * @file     ManualConfiguration.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ManualConfiguration
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <stdexcept>
#include <configuration/ManualConfiguration.hpp>

ManualConfiguration::ManualConfiguration() :
        MIOConfiguration(), pIOStrategy(NULL)
{
    pCards = new ModuleList_t();
}

ManualConfiguration::ManualConfiguration(IOStrategy *pIOStrategy) :
        MIOConfiguration(), pIOStrategy(pIOStrategy)
{
    pCards = new ModuleList_t();
}

void ManualConfiguration::addCard(BasicIoModule *pCard)
{
    ModuleList_t::iterator listIterator;
    if (getCard(pCard->getCardNumber()) == 0)
    {
        pIOStrategy->registerCard(pCard);
        pCards->push_back(pCard);
    }
    else
    {
        throw std::invalid_argument("Module/Card ID already exists");
    }
}

ManualConfiguration::ModuleList_t* ManualConfiguration::getCards()
{
    return pCards;
}

BasicIoModule* ManualConfiguration::getCard(UINT32 cardNbr)
{
    ModuleList_t::iterator listIterator;

    for (listIterator = pCards->begin(); listIterator != pCards->end(); ++listIterator)
    {
        if ((*listIterator)->getCardNumber() == cardNbr)
        {
            return (*listIterator);
        }
    }
    return NULL;
}

BasicChannel* ManualConfiguration::getChannel(std::string symbolicName)
{
    return NULL;
}

ManualConfiguration::~ManualConfiguration()
{
    /** Cards are not deleted. Should be deleted where they are created **/
    pCards->clear();

    SAFE_DELETE(pCards);
    SAFE_DELETE(pIOStrategy);
}

void ManualConfiguration::updateIn()
{
    if (pIOStrategy == NULL)
    {
        return;
    }

    pIOStrategy->readInput();
}

void ManualConfiguration::updateOut()
{
    if (pIOStrategy == NULL)
    {
        return;
    }
    pIOStrategy->writeOutput();

}

