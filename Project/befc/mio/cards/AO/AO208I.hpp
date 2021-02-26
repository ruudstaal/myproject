/**
 ********************************************************************************
 * @file     AO208I.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog output module AO208I
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AO208I_HPP_
#define AO208I_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/


/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 13 Bit Anaolog Output Module AO208/I
 *
 * Output   : 0(4)-20mA
 *
 */
class AO208I: public BasicAnalogModule
{
public:

    /** Mode for Output */
    static const UINT32 MODE_AO_20mA;
    static const UINT32 MODE_AO_4_20mA;


    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AO208I();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AO208I(UINT32 ui32CardNumber);

     /**
     * Destructor
     */
    virtual ~AO208I();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AO208;
    }

};

#endif /** AO208I_HPP_ */
