/**
 ********************************************************************************
 * @file     MixedIOConfigurationFactory.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Dec 10, 2015 12:50:00 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <MixedIOConfigurationFactory.hpp>
#include "AutomaticConfiguration.hpp"
#include "MixedIOStrategy.hpp"

MixedIOConfigurationFactory::MixedIOConfigurationFactory()
{
}

MixedIOConfigurationFactory::~MixedIOConfigurationFactory()
{
}

MIOConfiguration* MixedIOConfigurationFactory::createConfiguration(IOStrategy *pIOStrategy) {
    return new AutomaticConfiguration(pIOStrategy);
}

IOStrategy* MixedIOConfigurationFactory::createIOStrategy(BETask *pTask) {
    return new MixedIOStrategy(pTask);
}
