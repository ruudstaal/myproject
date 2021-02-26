/**
 ********************************************************************************
 * @file     IOConfigurationFactory
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of IOConfigurationFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef IOCONFIGURATIONFACTORY_HPP_
#define IOCONFIGURATIONFACTORY_HPP_

#include "MIOConfiguration.hpp"
#include "BETask.hpp"

class IOConfigurationFactory
{

public:
    /**
     ********************************************************************************
     * @brief      				This functions creates the MIOConfiguration. This is a
     * 							pure virtual function, and is meant to be overridden in
     * 							whatever factory is needed.
     * @param[in]  pIOStrategy  A pointer to an IOStrategy if needed.
     * @retval     				A pointer to the MIOConfiguration, which the client has
     * 							the responsibility to delete.
     *******************************************************************************/
    virtual MIOConfiguration* createConfiguration(IOStrategy *pIOStrategy) = 0;

    /**
     ********************************************************************************
     * @brief      This functions creates the IOStrategy. This is a pure virtual
     * 			   function, and is meant to be overridden in whatever factory is needed.
     * @retval     A pointer to the IOStrategy. Deleting instances is the responsibility
     *             of the client to delete.
     *
     *******************************************************************************/
    virtual IOStrategy* createIOStrategy(BETask *pTask) = 0;

    IOConfigurationFactory()
    {
        ;
    }

    virtual ~IOConfigurationFactory()
    {
        ;
    }

protected:

};

#endif /* IOCONFIGURATIONFACTORY_HPP_ */
