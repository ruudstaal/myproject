/**
 ********************************************************************************
 * @file     DO232.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital output module DO232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DO232_HPP_
#define DO232_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Output Module DO232
 *
 * Channels: 32
 */
class DO232: public BasicDigitalModule
{

public:

    /**
     * default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DO232();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DO232(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DO232();

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DO232;
    }
};

#endif /** DO232_HPP_ */
