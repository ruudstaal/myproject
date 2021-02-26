/**
 ********************************************************************************
 * @file     TI214.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog temperature module TI214
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "TI214.hpp"

const UINT32 TI214::MODE_TC_J = MIO_M_THERMO_J;
const UINT32 TI214::MODE_TC_K = MIO_M_THERMO_K;
const UINT32 TI214::MODE_TC_N = MIO_M_THERMO_N;
const UINT32 TI214::MODE_TC_S = MIO_M_THERMO_S;
const UINT32 TI214::MODE_PT100 = MIO_M_PT100;
const UINT32 TI214::MODE_PT100_2 = MIO_M_PT100_2;
const UINT32 TI214::MODE_PT100_3 = MIO_M_PT100_3;
const UINT32 TI214::MODE_PT1000_2 = MIO_M_PT1000_2;
const UINT32 TI214::MODE_PT1000_3 = MIO_M_PT1000_3;

/**----------------------------------------------------------------- */
TI214::TI214() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
TI214::TI214(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
TI214::~TI214()
{
}

/**----------------------------------------------------------------- */
VOID TI214::setAverageFilter(UINT8 ui8Channel, TI214::EFilter_t Filter)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Counter = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (TI214::eFilter_16 == Filter)
    {
        l_ui32Counter = 16;
    }

    if (TI214::eFilter_64 == Filter)
    {
        l_ui32Counter = 64;
    }

    BasicIoModule::doCommmand(MIO_CMD_SETAVERAGING, l_ui32Channel, (SINT32) l_ui32Counter);

}

/**----------------------------------------------------------------- */
TI214::EFilter_t TI214::getAverageFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETAVERAGING, l_ui32Channel, (SINT32) &l_ui32Value);
    if (16 == l_ui32Value)
    {
        return TI214::eFilter_16;
    }
    else if (64 == l_ui32Value)
    {
        return TI214::eFilter_64;
    }
    else
    {
        throw MIOexception("TI214::getAverageFilter: invalid value received ", ui8Channel,
                MIO_ER_BADREAD);
    }
}
