/**
 ********************************************************************************
 * @file     ManualPIConfigurationFactoryImpl.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ManualPIConfigurationFactoryImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <ManualPIConfigurationFactoryImpl.hpp>
#include "BEModule.hpp"
#include "ProcessImageIOStrategy.hpp"

ManualPIConfigurationFactoryImpl::ManualPIConfigurationFactoryImpl()
{
}

ManualPIConfigurationFactoryImpl::~ManualPIConfigurationFactoryImpl()
{
}

MIOConfiguration* ManualPIConfigurationFactoryImpl::createConfiguration(IOStrategy *pIOStrategy)
{
    return new ManualConfiguration(pIOStrategy);
}

IOStrategy* ManualPIConfigurationFactoryImpl::createIOStrategy(BETask *pTask)
{
    return new ProcessImageIOStrategy(pTask->getModule()->getAppName());
}
