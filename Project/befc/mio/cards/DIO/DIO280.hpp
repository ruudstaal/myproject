/**
 ********************************************************************************
 * @file     DIO280.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO280
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DIO280_HPP_
#define DIO280_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input/Output Module DIO280
 */
class DIO280: public BasicDigitalModule
{
public:

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DIO280();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DIO280(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DIO280();

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DIO280;
    }

};

#endif /** DIO280_HPP_ */
