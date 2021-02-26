/**
 ********************************************************************************
 * @file     AutomaticConfiguration.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of AutomaticConfiguration
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <AutomaticConfiguration.hpp>
#include <stdexcept>

AutomaticConfiguration::AutomaticConfiguration() :
        ManualConfiguration()
{
    init();
}

AutomaticConfiguration::AutomaticConfiguration(IOStrategy *pIOStrategy) :
        ManualConfiguration(pIOStrategy)
{
    init();
}

BasicChannel* AutomaticConfiguration::getChannel(std::string symbolicName)
{
    return pScan->getChannel(symbolicName);
}

AutomaticConfiguration::~AutomaticConfiguration()
{
    SAFE_DELETE(pScan);
}

void AutomaticConfiguration::init()
{
    pScan = new M1Scan();
    M1Scan::ModuleMap_t *pMap = pScan->getCardList();
    if (pMap != NULL)
    {
        M1Scan::ModuleMap_t::iterator it;
        for (it = pMap->begin(); it != pMap->end(); ++it)
        {
            try
            {
                addCard(it->second);
            }
            catch(MIOexception &ex)
            {
                log_Wrn("Could not add card %i in configuration, reason: %s",
                        it->second->getCardNumber(), ex.what());
            }
            catch(std::invalid_argument &ex)
            {
                log_Wrn("Could not add card %i in configuration, since it already exists",
                        it->second->getCardNumber());
            }
        }
    }
}

