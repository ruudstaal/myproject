/**
 ********************************************************************************
 * @file     DetectPIAutomaticIOConfigurationFactory.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DetectPIAutomaticIOConfigurationFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <DetectPIAutomaticIOConfigurationFactory.hpp>
#include "AutomaticConfiguration.hpp"

DetectPIAutomaticIOConfigurationFactory::DetectPIAutomaticIOConfigurationFactory()
{
}

DetectPIAutomaticIOConfigurationFactory::~DetectPIAutomaticIOConfigurationFactory()
{
}

MIOConfiguration* DetectPIAutomaticIOConfigurationFactory::createConfiguration(
        IOStrategy *pIOStrategy)
{
    return new AutomaticConfiguration(pIOStrategy);
}
