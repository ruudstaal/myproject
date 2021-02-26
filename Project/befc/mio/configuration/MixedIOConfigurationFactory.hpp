/**
 ********************************************************************************
 * @file     MixedIOConfigurationFactory.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Dec 10, 2015 12:50:00 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#ifndef BEFC_MIO_CONFIGURATION_MIXEDIOCONFIGURATIONFACTORY_HPP_
#define BEFC_MIO_CONFIGURATION_MIXEDIOCONFIGURATIONFACTORY_HPP_

#include <IOConfigurationFactory.hpp>

/**
 ********************************************************************************
 * @brief     This is a variant of the IOConfigurationFactory, which makes it
 *            possible to make use of both the Process Image and normal MIO
 *            handling. Card is added to the PI if possible, and if that fails,
 *            the normal approach is used.
 *            It furthermore autodetects all cards configured on the M1 system,
 *            so there is no need to add the cards.
 *******************************************************************************/
class MixedIOConfigurationFactory: public IOConfigurationFactory
{
public:
    MixedIOConfigurationFactory();

    MIOConfiguration* createConfiguration(IOStrategy *pIOStrategy);

    IOStrategy* createIOStrategy(BETask *pTask);

    virtual ~MixedIOConfigurationFactory();
};

#endif /* BEFC_MIO_CONFIGURATION_MIXEDIOCONFIGURATIONFACTORY_HPP_ */
