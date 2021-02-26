/**
 ********************************************************************************
 * @file     AO20XSI.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog output module AO20XSI
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AO20XSI_HPP_
#define AO20XSI_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 16 Bit Anaolog Output Module AO202/SI, AO204/SI
 *
 * Output   : 0-20mA
 *
 */
class AO20XSI: public BasicAnalogModule
{
public:

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AO20XSI();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AO20XSI(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~AO20XSI();

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AO20XSI;
    }
};

#endif /** AO20XSI_HPP_ */
