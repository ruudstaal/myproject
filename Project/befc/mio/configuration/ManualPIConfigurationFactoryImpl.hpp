/**
 ********************************************************************************
 * @file     ManualPIConfigurationFactoryImpl.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ManualPIConfigurationFactoryImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MANUALPICONFIGURATIONFACTORYIMPL_H_
#define MANUALPICONFIGURATIONFACTORYIMPL_H_

#include <IOConfigurationFactory.hpp>

/**
 ********************************************************************************
 * @brief     This is a variant of the IOConfigurationFactory, which makes use
 *            of the Process image. If this is not possible, an MIOException
 *            will be thrown.
 *            The cards will not be autodetected - You will need to add them
 *            manually.
 *
 *******************************************************************************/
class ManualPIConfigurationFactoryImpl: public IOConfigurationFactory
{
public:
    ManualPIConfigurationFactoryImpl();

    MIOConfiguration* createConfiguration(IOStrategy *pIOStrategy);

    IOStrategy* createIOStrategy(BETask *pTask);

    virtual ~ManualPIConfigurationFactoryImpl();
};

#endif /* MANUALPICONFIGURATIONFACTORYIMPL_H_ */
