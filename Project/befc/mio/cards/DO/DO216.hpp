/**
 ********************************************************************************
 * @file     DO216.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital output module DO216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DO216_HPP_
#define DO216_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Output Module DO216
 *
 * Channels: 16
 */
class DO216: public BasicDigitalModule
{

public:

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DO216();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DO216(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DO216();

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DO216;
    }
};

#endif /** DO216_HPP_ */
