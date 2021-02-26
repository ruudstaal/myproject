/**
 ********************************************************************************
 * @file     GIO2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of general purpose input and output module GIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "GIO2XX.hpp"

const UINT32 GIO2XX::MODE_DISABLED = MIO_M_GIODISABLED;
const UINT32 GIO2XX::MODE_DI_TYPE1 = MIO_M_GIODITYPE1;
const UINT32 GIO2XX::MODE_DI_TYPE2 = MIO_M_GIODITYPE2;
const UINT32 GIO2XX::MODE_DI_TYPE3 = MIO_M_GIODITYPE3;
const UINT32 GIO2XX::MODE_DI_SOURCE = MIO_M_GIODISOURCE;
const UINT32 GIO2XX::MODE_DI_CMP = MIO_M_GIODITYPECMP;
const UINT32 GIO2XX::MODE_DO_PUSHPULL = MIO_M_GIODOPUSHPULL;
const UINT32 GIO2XX::MODE_DO_LOWSIDE = MIO_M_GIODOLOWSIDE;
const UINT32 GIO2XX::MODE_DO_HIGHSIDE = MIO_M_GIODOHIGHSIDE;
const UINT32 GIO2XX::MODE_AI1_10V = MIO_M_GIOVI_10V;
const UINT32 GIO2XX::MODE_AI1_1V = MIO_M_GIOVI_1V;
const UINT32 GIO2XX::MODE_AI1_100mV = MIO_M_GIOVI_100mV;
const UINT32 GIO2XX::MODE_AI1_10mV = MIO_M_GIOVI_10mV;
const UINT32 GIO2XX::MODE_AI_RANGE1 = MIO_M_GIOVIRANGE1;
const UINT32 GIO2XX::MODE_AI_RANGE2 = MIO_M_GIOVIRANGE2;
const UINT32 GIO2XX::MODE_AI_20mA = MIO_M_GIOCI_20mA;
const UINT32 GIO2XX::MODE_AI_4_20mA = MIO_M_GIOCI_4_20mA;
const UINT32 GIO2XX::MODE_AO_V = MIO_M_GIOVO;
const UINT32 GIO2XX::MODE_AO_V_EXT = MIO_M_GIOVOEXT;
const UINT32 GIO2XX::MODE_AO_0_20mA = MIO_M_GIOCO_0_20mA;
const UINT32 GIO2XX::MODE_AO_4_20mA = MIO_M_GIOCO_4_20mA;
const UINT32 GIO2XX::MODE_AO_0_2mA = MIO_M_GIOCO_0_2mA;
const UINT32 GIO2XX::MODE_AO_0_200uA = MIO_M_GIOCO_0_200uA;
const UINT32 GIO2XX::MODE_CNT_EDGE = MIO_M_GIOCNTEDGE;
const UINT32 GIO2XX::MODE_CNT_PERIOD = MIO_M_GIOCNTTIMEPERIOD;
const UINT32 GIO2XX::MODE_CNT_PULSE = MIO_M_GIOCNTTIMEPULSE;
const UINT32 GIO2XX::MODE_DCNT_EDGE_TRIG = MIO_M_GIOCNTDUALEDGETRIG;
const UINT32 GIO2XX::MODE_DCNT_EDGE_RESET = MIO_M_GIOCNTDUALEDGERESET;
const UINT32 GIO2XX::MODE_DCNT_EDGE_GATE = MIO_M_GIOCNTDUALEDGEGATE;
const UINT32 GIO2XX::MODE_DCNT_EDGE_DIR = MIO_M_GIOCNTDUALEDGEDIR;
const UINT32 GIO2XX::MODE_INC_1 = MIO_M_GIOCNTINC_1;
const UINT32 GIO2XX::MODE_INC_2 = MIO_M_GIOCNTINC_2;
const UINT32 GIO2XX::MODE_INC_4 = MIO_M_GIOCNTINC_4;
const UINT32 GIO2XX::MODE_PWM_PUSHPULL = MIO_M_GIOPWMPUSHPULL;
const UINT32 GIO2XX::MODE_PWM_LOWSIDE = MIO_M_GIOPWMLOWSIDE;
const UINT32 GIO2XX::MODE_PWM_HIGHSIDE = MIO_M_GIOPWMHIGHSIDE;
const UINT32 GIO2XX::MODE_PWM_DUAL_PP = MIO_M_GIOPWMDUALPUSHPULL;
const UINT32 GIO2XX::MODE_PWM_DUAL_LS = MIO_M_GIOPWMDUALLOWSIDE;
const UINT32 GIO2XX::MODE_PWM_DUAL_HS = MIO_M_GIOPWMDUALHIGHSIDE;
const UINT32 GIO2XX::MODE_TC_J = MIO_M_GIOTEMOELEM_J;
const UINT32 GIO2XX::MODE_TC_K = MIO_M_GIOTEMOELEM_K;
const UINT32 GIO2XX::MODE_TC_T = MIO_M_GIOTEMOELEM_T;
const UINT32 GIO2XX::MODE_TC_N = MIO_M_GIOTEMOELEM_N;
const UINT32 GIO2XX::MODE_TC_E = MIO_M_GIOTEMOELEM_E;
const UINT32 GIO2XX::MODE_TC_R = MIO_M_GIOTEMOELEM_R;
const UINT32 GIO2XX::MODE_TC_S = MIO_M_GIOTEMOELEM_S;
const UINT32 GIO2XX::MODE_TC_B = MIO_M_GIOTEMOELEM_B;
const UINT32 GIO2XX::MODE_PT100_2 = MIO_M_GIOPT100_2;
const UINT32 GIO2XX::MODE_PT100_3 = MIO_M_GIOPT100_3;
const UINT32 GIO2XX::MODE_PT100_4 = MIO_M_GIOPT100_4;
const UINT32 GIO2XX::MODE_PT200_2 = MIO_M_GIOPT200_2;
const UINT32 GIO2XX::MODE_PT200_3 = MIO_M_GIOPT200_3;
const UINT32 GIO2XX::MODE_PT200_4 = MIO_M_GIOPT200_4;
const UINT32 GIO2XX::MODE_PT500_2 = MIO_M_GIOPT500_2;
const UINT32 GIO2XX::MODE_PT500_3 = MIO_M_GIOPT500_3;
const UINT32 GIO2XX::MODE_PT500_4 = MIO_M_GIOPT500_4;
const UINT32 GIO2XX::MODE_PT1000_2 = MIO_M_GIOPT1000_2;
const UINT32 GIO2XX::MODE_PT1000_3 = MIO_M_GIOPT1000_3;
const UINT32 GIO2XX::MODE_PT1000_4 = MIO_M_GIOPT1000_4;

/**----------------------------------------------------------------- */
GIO2XX::GIO2XX() :
        BasicMixedModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
GIO2XX::GIO2XX(UINT32 ui32CardNumber) :
        BasicMixedModule(ui32CardNumber, true)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
GIO2XX::~GIO2XX()
{
}

/**----------------------------------------------------------------- */
UINT32 GIO2XX::getEventState(VOID)
{
    UINT32 l_ui32EventState;
    BasicIoModule::doCommmand(MIO_CMD_GETEVENT, 0, (SINT32) &l_ui32EventState);
    return l_ui32EventState;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setAnalogFilter(UINT8 ui8Channel, GIO2XX::EAnalogFilter_t eValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETAIFILTER, l_ui32Channel, (SINT32) eValue);
}

/**----------------------------------------------------------------- */
GIO2XX::EAnalogFilter_t GIO2XX::getAnalogFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    GIO2XX::EAnalogFilter_t l_eValue;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETAIFILTER, l_ui32Channel, (SINT32) &l_eValue);
    return l_eValue;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setLimits(UINT8 ui8Channel, GIO2XX::SMinMax_t* psValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETLIMITS, l_ui32Channel, (SINT32) psValue);
}

/**----------------------------------------------------------------- */
GIO2XX::SMinMax_t* GIO2XX::getLimits(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETLIMITS, l_ui32Channel, (SINT32) &m_MinMaxLimits);
    return &m_MinMaxLimits;
}

/**----------------------------------------------------------------- */
UINT32 GIO2XX::getChipTemperature(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temperature = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETCHIPTEMP, l_ui32Channel, (SINT32) &l_ui32Temperature);
    return l_ui32Temperature;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setCompensation(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETCOLDJUNCTEMP, l_ui32Channel, (SINT32) ui32Value);
}

/**----------------------------------------------------------------- */
UINT32 GIO2XX::getCompensation(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32CompensationValue = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETCOLDJUNCTEMP, l_ui32Channel,
            (SINT32) &l_ui32CompensationValue);
    return l_ui32CompensationValue;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setHalfband(UINT8 ui8Channel, BOOL8 b8Active)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETFILTERHB, l_ui32Channel, (SINT32) b8Active);
}

/**----------------------------------------------------------------- */
BOOL8 GIO2XX::getHalfband(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

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
VOID GIO2XX::setInterpolation(UINT8 ui8Channel, BOOL8 b8Active)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETFILTERITP, l_ui32Channel, (SINT32) b8Active);
}

/**----------------------------------------------------------------- */
BOOL8 GIO2XX::getInterpolation(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

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

/**----------------------------------------------------------------- */
BOOL8 GIO2XX::getInputState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETINPSTAT, l_ui32Channel, (SINT32) &l_ui32Value);
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
VOID GIO2XX::setDigitalFilter(UINT8 ui8Channel, GIO2XX::EDigitalFilter_t eValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETSPIKEFILTER, l_ui32Channel, (SINT32) eValue);
}

/**----------------------------------------------------------------- */
GIO2XX::EDigitalFilter_t GIO2XX::getDigitalFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    GIO2XX::EDigitalFilter_t l_eValue;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETSPIKEFILTER, l_ui32Channel, (SINT32) &l_eValue);
    return l_eValue;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setPulseConfig(UINT8 ui8Channel, GIO2XX::SPulseConfig_t* psValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETDOPULSE, l_ui32Channel, (SINT32) psValue);
}

/**----------------------------------------------------------------- */
GIO2XX::SPulseConfig_t* GIO2XX::getPulseConfig(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETDOPULSE, l_ui32Channel, (SINT32) &m_PulseConfig);
    return &m_PulseConfig;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::setPwmPeriod(UINT8 ui8Channel, UINT32 ui32Time)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPP, l_ui32Channel, (SINT32) ui32Time);
}

/**----------------------------------------------------------------- */
UINT32 GIO2XX::getPwmPeriod(UINT8 ui8Channel)
{
    UINT32 l_ui32Time = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPP, l_ui32Channel, (SINT32) &l_ui32Time);
    return l_ui32Time;
}

/**----------------------------------------------------------------- */
VOID GIO2XX::startPwm(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETPWMRUNMODE, l_ui32Channel, 1);
}

/**----------------------------------------------------------------- */
VOID GIO2XX::stopPwm(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOSETPWMRUNMODE, l_ui32Channel, 0);
}

/**----------------------------------------------------------------- */
BOOL8 GIO2XX::getPwmState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GIOGETPWMRUNMODE, l_ui32Channel, (SINT32) &l_ui32Value);
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
VOID GIO2XX::setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETREF, l_ui32Channel, (SINT32) si32Value);
}

/**----------------------------------------------------------------- */
SINT32 GIO2XX::getReferenceRegister(UINT8 ui8Channel)
{
    SINT32 l_si32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETREF, l_ui32Channel, (SINT32) &l_si32Value);
    return l_si32Value;
}
