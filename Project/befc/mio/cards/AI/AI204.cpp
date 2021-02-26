/**
 ********************************************************************************
 * @file     AI204.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AI204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AI204.hpp"

const UINT32 AI204::MODE_FILTER_333HZ = MIO_M_FILT333HZ;
const UINT32 AI204::MODE_FILTER_4kHZ = MIO_M_FILT4KHZ;
const UINT32 AI204::MODE_SAMPLE1 = MIO_M_SAMPLE1;
const UINT32 AI204::MODE_SAMPLE8 = MIO_M_SAMPLE8;
const UINT32 AI204::MODE_SAMPLE16 = MIO_M_SAMPLE16;
const UINT32 AI204::MODE_SAMPLE32 = MIO_M_SAMPLE32;
const UINT32 AI204::MODE_NO_TEMPCOMP = MIO_M_NOTMPCOMP;
const UINT32 AI204::MODE_SYNC = MIO_M_SYNC;

/**----------------------------------------------------------------- */
AI204::AI204() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AI204::AI204(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AI204::~AI204()
{
}

/**----------------------------------------------------------------- */
SINT32 AI204::readTemperature(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32Temperature;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETTEMP, l_ui32Channel, (SINT32) &l_si32Temperature);
    return l_si32Temperature;
}

/**----------------------------------------------------------------- */
VOID AI204::startCompensation(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_TEMPCOMP, l_ui32Channel);

}
