/**
 ********************************************************************************
 * @file     PIConfigurationFactoryImpl
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of PIConfigurationFactoryImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <configuration/DetectPIConfigurationFactoryImpl.hpp>
#include "BEModule.hpp"
#include "ProcessImageIOStrategy.hpp"
#include "mio/configuration/StdIOStrategy.hpp"

DetectPIConfigurationFactoryImpl::DetectPIConfigurationFactoryImpl()
{
}

DetectPIConfigurationFactoryImpl::~DetectPIConfigurationFactoryImpl()
{
}

MIOConfiguration* DetectPIConfigurationFactoryImpl::createConfiguration(IOStrategy *pIOStrategy)
{
    return new ManualConfiguration(pIOStrategy);
}

IOStrategy* DetectPIConfigurationFactoryImpl::createIOStrategy(BETask *pTask)
{

    //TODO Should be externalized
    if (mio_PiUseProcImg)
    {

        return new ProcessImageIOStrategy(pTask->getModule()->getAppName());
    }
    else
    {
        return new StdIOStrategy(); /** PI not possible */
    }
}
