/**
 ********************************************************************************
 * @file     AIO288.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input and output module
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AIO288_HPP_
#define AIO288_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 14 Bit Analog Input Output Module AIO288
 *
 * Input 10V, 1V, 0.20 mA : 8 \n
 * PT100, PT1000          : 4 \n
 * Output +/- 10V         : 8
 */
class AIO288: public BasicAnalogModule
{

public:

    /** Channel Modes */
    static const UINT32 MODE_10V; /**< -10 - +10V */
    static const UINT32 MODE_1V; /**< -1 - +1V */
    static const UINT32 MODE_20mA; /**< 0-20mA */
    static const UINT32 MODE_PT100; /**< PT100 */
    static const UINT32 MODE_PT1000;/**< PT1000 */

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AIO288();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AIO288(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~AIO288();

    /**
     * Read Temperature from PT100/PT1000 Channel
     * Value is in 1/100 K
     *
     * @param ui8Channel - selected Channel (5-8)
     * @return Temperature in 1/100 K
     *
     */
    SINT32 readTemperature(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AIO288;
    }
};

#endif /** AIO288_HPP_ */
