/**
 ********************************************************************************
 * @file     AIO288.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input and output module AIO288
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AIO288.hpp"

const UINT32 AIO288::MODE_10V = MIO_M_10V;
const UINT32 AIO288::MODE_1V = MIO_M_1V;
const UINT32 AIO288::MODE_20mA = MIO_M_20MA;
const UINT32 AIO288::MODE_PT100 = MIO_M_PT100;
const UINT32 AIO288::MODE_PT1000 = MIO_M_PT1000;

/**----------------------------------------------------------------- */
AIO288::AIO288() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIO288::AIO288(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIO288::~AIO288()
{
}

/**----------------------------------------------------------------- */
SINT32 AIO288::readTemperature(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32Temperature = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETVAL, l_ui32Channel, (SINT32) &l_si32Temperature);

    return l_si32Temperature;
}
