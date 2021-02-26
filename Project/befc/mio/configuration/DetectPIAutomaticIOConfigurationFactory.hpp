/**
 ********************************************************************************
 * @file     DetectPIAutomaticIOConfigurationFactory.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DetectPIAutomaticIOConfigurationFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef BEFC_MIO_CONFIGURATION_DETECTPIAUTOMATICIOCONFIGURATIONFACTORY_HPP_
#define BEFC_MIO_CONFIGURATION_DETECTPIAUTOMATICIOCONFIGURATIONFACTORY_HPP_

#include <DetectPIConfigurationFactoryImpl.hpp>

/**
 ********************************************************************************
 * @brief     This is a variant of the IOConfigurationFactory, which detects
 *            whether it is possible to use the PI. If it is not possible, then
 *            the normal MIO handling will be used.
 *
 *            All cards will be autodetected. You should not add any cards to the
 *            configuration
 *
 *******************************************************************************/
class DetectPIAutomaticIOConfigurationFactory: public DetectPIConfigurationFactoryImpl
{
public:
    DetectPIAutomaticIOConfigurationFactory();

    MIOConfiguration* createConfiguration(IOStrategy *pIOStrategy);

    virtual ~DetectPIAutomaticIOConfigurationFactory();
};

#endif /* BEFC_MIO_CONFIGURATION_DETECTPIAUTOMATICIOCONFIGURATIONFACTORY_HPP_ */
