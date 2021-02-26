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

#ifndef PICONFIGURATIONFACTORYIMPL_H_
#define PICONFIGURATIONFACTORYIMPL_H_

#include <configuration/IOConfigurationFactory.hpp>

/**
 ********************************************************************************
 * @brief     This is a variant of the IOConfigurationFactory, which detects
 *            whether it is possible to use the PI. If it is not possible, then
 *            the normal MIO handling will be used.
 *
 *            The cards will not be autodetected - You will need to add them
 *            manually.
 *
 *******************************************************************************/
class DetectPIConfigurationFactoryImpl: public IOConfigurationFactory
{
public:
    DetectPIConfigurationFactoryImpl();

    MIOConfiguration* createConfiguration(IOStrategy *pIOStrategy);

    IOStrategy* createIOStrategy(BETask *pTask);

    virtual ~DetectPIConfigurationFactoryImpl();
};

#endif /* PICONFIGURATIONFACTORYIMPL_H_ */
