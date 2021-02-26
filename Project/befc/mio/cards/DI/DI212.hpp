/**
 ********************************************************************************
 * @file     DI212.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input module DI212
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DI212_HPP_
#define DI212_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input Module DI212
 */
class DI212: public BasicDigitalModule
{
public:

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DI212();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DI212(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DI212();

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DI212;
    }
};

#endif /** DI212_HPP_ */
