/**
 ********************************************************************************
 * @file     AIO2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input and output module AIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AIO2XX.hpp"

/** Channel Disabled */
const UINT32 AIO2XX::MODE_DISABLED = MIO_M_GIODISABLED;
const UINT32 AIO2XX::MODE_AI1_10V = MIO_M_GIOVI_10V;
const UINT32 AIO2XX::MODE_AI1_1V = MIO_M_GIOVI_1V;
const UINT32 AIO2XX::MODE_AI1_100mV = MIO_M_GIOVI_100mV;
const UINT32 AIO2XX::MODE_AI1_10mV = MIO_M_GIOVI_10mV;
const UINT32 AIO2XX::MODE_AI_RANGE1 = MIO_M_GIOVIRANGE1;
const UINT32 AIO2XX::MODE_AI_RANGE2 = MIO_M_GIOVIRANGE2;
const UINT32 AIO2XX::MODE_AI_20mA = MIO_M_GIOCI_20mA;
const UINT32 AIO2XX::MODE_AI_4_20mA = MIO_M_GIOCI_4_20mA;
const UINT32 AIO2XX::MODE_AO_V = MIO_M_GIOVO;
const UINT32 AIO2XX::MODE_AO_V_EXT = MIO_M_GIOVOEXT;
const UINT32 AIO2XX::MODE_AO_0_20mA = MIO_M_GIOCO_0_20mA;
const UINT32 AIO2XX::MODE_AO_4_20mA = MIO_M_GIOCO_4_20mA;
const UINT32 AIO2XX::MODE_AO_0_2mA = MIO_M_GIOCO_0_2mA;
const UINT32 AIO2XX::MODE_AO_0_200uA = MIO_M_GIOCO_0_200uA;
const UINT32 AIO2XX::MODE_TC_J = MIO_M_GIOTEMOELEM_J;
const UINT32 AIO2XX::MODE_TC_K = MIO_M_GIOTEMOELEM_K;
const UINT32 AIO2XX::MODE_TC_T = MIO_M_GIOTEMOELEM_T;
const UINT32 AIO2XX::MODE_TC_N = MIO_M_GIOTEMOELEM_N;
const UINT32 AIO2XX::MODE_TC_E = MIO_M_GIOTEMOELEM_E;
const UINT32 AIO2XX::MODE_TC_R = MIO_M_GIOTEMOELEM_R;
const UINT32 AIO2XX::MODE_TC_S = MIO_M_GIOTEMOELEM_S;
const UINT32 AIO2XX::MODE_TC_B = MIO_M_GIOTEMOELEM_B;
const UINT32 AIO2XX::MODE_PT100_2 = MIO_M_GIOPT100_2;
const UINT32 AIO2XX::MODE_PT100_3 = MIO_M_GIOPT100_3;
const UINT32 AIO2XX::MODE_PT100_4 = MIO_M_GIOPT100_4;
const UINT32 AIO2XX::MODE_PT200_2 = MIO_M_GIOPT200_2;
const UINT32 AIO2XX::MODE_PT200_3 = MIO_M_GIOPT200_3;
const UINT32 AIO2XX::MODE_PT200_4 = MIO_M_GIOPT200_4;
const UINT32 AIO2XX::MODE_PT500_2 = MIO_M_GIOPT500_2;
const UINT32 AIO2XX::MODE_PT500_3 = MIO_M_GIOPT500_3;
const UINT32 AIO2XX::MODE_PT500_4 = MIO_M_GIOPT500_4;
const UINT32 AIO2XX::MODE_PT1000_2 = MIO_M_GIOPT1000_2;
const UINT32 AIO2XX::MODE_PT1000_3 = MIO_M_GIOPT1000_3;
const UINT32 AIO2XX::MODE_PT1000_4 = MIO_M_GIOPT1000_4;

/**----------------------------------------------------------------- */
AIO2XX::AIO2XX() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIO2XX::AIO2XX(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIO2XX::~AIO2XX()
{
}

/**----------------------------------------------------------------- */
UINT32 AIO2XX::getEventState(VOID)
{
    UINT32 l_ui32State;
    BasicIoModule::doCommmand(MIO_CMD_GETEVENT, 0, (SINT32) &l_ui32State);
    return l_ui32State;
}

/**----------------------------------------------------------------- */
VOID AIO2XX::setFilter(UINT8 ui8Channel, AIO2XX::EFilter_t eValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETAIFILTER, l_ui32Channel, (SINT32) eValue);
}

/**----------------------------------------------------------------- */
AIO2XX::EFilter_t AIO2XX::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    AIO2XX::EFilter_t l_eValue;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETAIFILTER, l_ui32Channel, (SINT32) &l_eValue);
    return l_eValue;
}

/**----------------------------------------------------------------- */
VOID AIO2XX::setLimits(UINT8 ui8Channel, AIO2XX::SMinMax_t* psValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETLIMITS, l_ui32Channel, (SINT32) psValue);
}

/**----------------------------------------------------------------- */
AIO2XX::SMinMax_t* AIO2XX::getLimits(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETLIMITS, l_ui32Channel, (SINT32) &m_MinMaxLimits);
    return &m_MinMaxLimits;
}

/**----------------------------------------------------------------- */
UINT32 AIO2XX::getChipTemperature(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temperature = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETCHIPTEMP, l_ui32Channel, (SINT32) &l_ui32Temperature);
    return l_ui32Temperature;
}

/**----------------------------------------------------------------- */
VOID AIO2XX::setCompensation(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETCOLDJUNCTEMP, l_ui32Channel, (SINT32) ui32Value);
}

/**----------------------------------------------------------------- */
UINT32 AIO2XX::getCompensation(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32CompensationValue = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETCOLDJUNCTEMP, l_ui32Channel,
            (SINT32) &l_ui32CompensationValue);
    return l_ui32CompensationValue;
}

/**----------------------------------------------------------------- */
VOID AIO2XX::setHalfband(UINT8 ui8Channel, BOOL8 b8Active)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETFILTERHB, l_ui32Channel, (SINT32) b8Active);
}

/**----------------------------------------------------------------- */
BOOL8 AIO2XX::getHalfband(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETFILTERHB, l_ui32Channel, (SINT32) &l_ui32Value);
    if (1 == l_ui32Value)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**----------------------------------------------------------------- */
VOID AIO2XX::setInterpolation(UINT8 ui8Channel, BOOL8 b8Active)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETFILTERITP, l_ui32Channel, (SINT32) b8Active);
}

/**----------------------------------------------------------------- */
BOOL8 AIO2XX::getInterpolation(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETFILTERITP, l_ui32Channel, (SINT32) &l_ui32Value);
    if (1 == l_ui32Value)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
