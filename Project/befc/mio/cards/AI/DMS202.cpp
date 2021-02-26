/**
 ********************************************************************************
 * @file     DMS202.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of strain gauge module DMS202
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DMS202.hpp"

/**----------------------------------------------------------------- */
DMS202::DMS202() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
DMS202::DMS202(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
DMS202::~DMS202()
{

}

/**----------------------------------------------------------------- */
VOID DMS202::setOffset(UINT8 ui8Channel, DMS202::EOffset_t Value, BOOL8 b8Save)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32Value = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    switch (Value)
    {
        case (OFFSET_0):
            l_si32Value = 0 * 2048;
            break;
        case (OFFSET_1):
            l_si32Value = 1 * 2048;
            break;
        case (OFFSET_2):
            l_si32Value = 2 * 2048;
            break;
        case (OFFSET_3):
            l_si32Value = 3 * 2048;
            break;
        case (OFFSET_4):
            l_si32Value = 4 * 2048;
            break;
        case (OFFSET_5):
            l_si32Value = 5 * 2048;
            break;
        case (OFFSET_6):
            l_si32Value = 6 * 2048;
            break;
        case (OFFSET_7):
            l_si32Value = 7 * 2048;
            break;
        case (OFFSET_8):
            l_si32Value = 8 * 2048;
            break;
        default:
            throw MIOexception("DMS202::setOffset: invalid parameter ", ui8Channel, MIO_ER_BADPARM);
    }

    if (TRUE == b8Save)
    {
        BasicIoModule::doCommmand(MIO_CMD_OFFSETCAL, l_ui32Channel, l_si32Value);
    }
    else
    {
        BasicIoModule::doCommmand(MIO_CMD_OFFSETCALTMP, l_ui32Channel, l_si32Value);
    }
}

/**----------------------------------------------------------------- */
SINT32 DMS202::getPeak(UINT8 ui8Channel, BOOL8 b8Reset)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32PeakValue = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (TRUE == b8Reset)
    {
        BasicIoModule::doCommmand(MIO_CMD_PEEKRW, l_ui32Channel, (SINT32) &l_si32PeakValue);
    }
    else
    {
        BasicIoModule::doCommmand(MIO_CMD_PEEKRO, l_ui32Channel, (SINT32) &l_si32PeakValue);
    }
    return l_si32PeakValue;
}

/**----------------------------------------------------------------- */
VOID DMS202::setZero(UINT8 ui8Channel, BOOL8 b8Save)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (TRUE == b8Save)
    {
        BasicIoModule::doCommmand(MIO_CMD_ZEROCALIB, l_ui32Channel, 0);
    }
    else
    {
        BasicIoModule::doCommmand(MIO_CMD_ZEROCALTMP, l_ui32Channel, 0);
    }
}
