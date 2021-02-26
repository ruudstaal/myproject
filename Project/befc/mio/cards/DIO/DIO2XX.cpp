/**
 ********************************************************************************
 * @file     DIO2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DIO2XX.hpp"
#include <string.h>

const UINT32 DIO2XX::MODE_INPUT = MIO_M_IN;
const UINT32 DIO2XX::MODE_OUTPUT = MIO_M_OUT;
const UINT32 DIO2XX::MODE_POSEDGE = MIO_M_POSEDGE;
const UINT32 DIO2XX::MODE_NEGEDGE = MIO_M_NEGEDGE;
const UINT32 DIO2XX::MODE_BOTHEDGES = MIO_M_BOTHEDGES;
const UINT32 DIO2XX::MODE_INC = MIO_M_INC;
const UINT32 DIO2XX::MODE_GATE_TIME = MIO_M_GATETIME;
const UINT32 DIO2XX::MODE_PERIOD = MIO_M_PERIOD;
const UINT32 DIO2XX::MODE_SINGLE = MIO_M_SINGLE;
const UINT32 DIO2XX::MODE_DOUBLE = MIO_M_DOUBLE;
const UINT32 DIO2XX::MODE_QUAD = MIO_M_QUAD;

/**-----------------------------------------------------------------*/
DIO2XX::DIO2XX() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO2XX::DIO2XX(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO2XX::~DIO2XX()
{
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::setPwmConfig(UINT8 ui8Channel, sPWM_CONFIG_t* pConfig)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPWMCFG, l_ui32Channel, (SINT32) pConfig);
}

/**-----------------------------------------------------------------*/
DIO2XX::sPWM_CONFIG_t* DIO2XX::getPwmConfig(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPWMCFG, l_ui32Channel, (SINT32) &m_PwmCfg);
    return &m_PwmCfg;
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::setFilter(UINT8 ui8Channel, UINT32 ui32Time)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) ui32Time);
}

/**-----------------------------------------------------------------*/
UINT32 DIO2XX::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Time = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER, l_ui32Channel, (SINT32) &l_ui32Time);
    return l_ui32Time;
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::setGateTime(UINT8 ui8Channel, UINT32 ui32Time)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETGATETIME, l_ui32Channel, (SINT32) ui32Time);
}

/**-----------------------------------------------------------------*/
UINT32 DIO2XX::getGateTime(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Time = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETGATETIME, l_ui32Channel, (SINT32) &l_ui32Time);
    return l_ui32Time;
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::setResetValue(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETRESETVALUE, l_ui32Channel, (SINT32) ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 DIO2XX::getResetValue(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRESETVALUE, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::getPinLevel(UINT8 ui8Channel, UINT16* pui16Channels)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Buffer[16];

    l_ui32Channel = (UINT32) ui8Channel;

    if (NULL == pui16Channels)
    {
        throw MIOexception("DIO2XX::getPinLevel: invalid parameter ", ui8Channel, MIO_ER_BADPARM);
    }

    memset(&l_ui32Buffer[0], 0, sizeof(l_ui32Buffer));

    BasicIoModule::doCommmand(MIO_CMD_GETPINLEVELS, l_ui32Channel, (SINT32) &l_ui32Buffer[0]);
    *pui16Channels = 0;
    /**
     * l_ui32Buffer[i] is 0 or 1
     * Every Channel is pushed to the Bitvalue
     *
     */
    for (int i = 0; i < 15; i++)
    {
        *pui16Channels |= ((l_ui32Buffer[i] << i) & 0xFFFF);
    }
}

/**-----------------------------------------------------------------*/
UINT32 DIO2XX::getStrobeRegister(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32StrobeRegister;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRB, l_ui32Channel, (SINT32) &l_ui32StrobeRegister);
    return l_ui32StrobeRegister;
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::enableReset(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_ENABLERST, l_ui32Channel);
}

/**-----------------------------------------------------------------*/
BOOL8 DIO2XX::resetActive(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Buffer = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRST, l_ui32Channel, (SINT32) &l_ui32Buffer);
    if (1 == l_ui32Buffer)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
VOID DIO2XX::setNullSwitchMode(UINT8 ui8Channel, DIO2XX::eEDGE_t Mode)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Mode = MIO_M_NEGEDGE;

    l_ui32Channel = (UINT32) ui8Channel;

    if (eRISING_EDGE == Mode)
    {
        l_ui32Mode = MIO_M_POSEDGE;
    }

    BasicIoModule::doCommmand(MIO_CMD_CONFIGNULLEDGE, l_ui32Channel, (SINT32) l_ui32Mode);
}

/**-----------------------------------------------------------------*/
DIO2XX::eEDGE_t DIO2XX::getNullSwitchMode(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Mode = 0;
    DIO2XX::eEDGE_t l_eEdge;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETNULLEDGE, l_ui32Channel, (SINT32) &l_ui32Mode);
    l_eEdge = eFALLING_EDGE;
    if (MIO_M_POSEDGE == l_ui32Mode)
    {
        l_eEdge = eRISING_EDGE;
    }

    return l_eEdge;
}
