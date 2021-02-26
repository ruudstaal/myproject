/**
 ********************************************************************************
 * @file     CNT204.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of counter module CNT204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "CNT204.hpp"

const UINT32 CNT204::MODE_INC = MIO_M_INC;
const UINT32 CNT204::MODE_COUNT = MIO_M_COUNT;
const UINT32 CNT204::MODE_INC_TIME = MIO_M_INCTIME;
const UINT32 CNT204::MODE_COUNT_TIME = MIO_M_CNTTIME;
const UINT32 CNT204::MODE_DIFF_TIME = MIO_M_DIFFTIME;
const UINT32 CNT204::MODE_TRIGG = MIO_M_TRIGG;
const UINT32 CNT204::MODE_SINGLE = MIO_M_SINGLE;
const UINT32 CNT204::MODE_DOUBLE = MIO_M_DOUBLE;
const UINT32 CNT204::MODE_QUAD = MIO_M_QUAD;
const UINT32 CNT204::MODE_CONTINUOUS = MIO_M_CONTINUOUS;
const UINT32 CNT204::MODE_NO_ZERO = MIO_M_NOZERO;
const UINT32 CNT204::MODE_NO_HOME = MIO_M_NOHOME;
const UINT32 CNT204::MODE_PULSE_DIR = MIO_M_PULSEDIR;
const UINT32 CNT204::MODE_SYNC = MIO_M_SYNC;
const UINT32 CNT204::MODE_RESET = MIO_M_RESET;
const UINT32 CNT204::MAXFILTER = 46875;
const UINT32 CNT204::MINFILTER = 183;

/**-----------------------------------------------------------------*/
CNT204::CNT204() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
CNT204::CNT204(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
CNT204::~CNT204()
{

}

/**-----------------------------------------------------------------*/
UINT32 CNT204::getValueAndFlags(UINT8 ui8Channel, SFlags_t* psFlags)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;
    /**
     * Special Call
     * GETVAL does not only return an Errorcode
     * it also deliver the Flags
     */
    (VOID) BasicIoModule::doCommmand(MIO_CMD_GETVAL, l_ui32Channel, (SINT32) &l_ui32Value);

    if (m_si32Error >= 0)
    {
        if (NULL != psFlags)
        {
            psFlags->b8NewValue = BitCheck(m_si32Error, 0x1);
            psFlags->b8ValueLost = BitCheck(m_si32Error, 0x2);
        }
    }

    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
UINT32 CNT204::getCounter(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETACT, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
BOOL8 CNT204::getInput(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETINPSTAT, l_ui32Channel, (SINT32) &l_ui32Temp);

    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
VOID CNT204::setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETREF, l_ui32Channel, si32Value);
}

/**-----------------------------------------------------------------*/
SINT32 CNT204::getReferenceRegister(UINT8 ui8Channel)
{
    SINT32 l_si32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETREF, l_ui32Channel, (SINT32) &l_si32Value);
    return l_si32Value;
}

/**-----------------------------------------------------------------*/
BOOL8 CNT204::getReferenceState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRST, l_ui32Channel, (SINT32) &l_ui32Temp);
    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
SINT32 CNT204::getStrobeRegister(UINT8 ui8Channel)
{
    SINT32 l_si32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRB, l_ui32Channel, (SINT32) &l_si32Value);
    return l_si32Value;
}

/**-----------------------------------------------------------------*/
VOID CNT204::resetStrobeState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_RESETSTRBSTAT, l_ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID CNT204::enableReset(UINT8 ui8Channel, BOOL8 b8Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (TRUE == b8Value)
    {
        BasicIoModule::doCommmand(MIO_CMD_ENABLERST, l_ui32Channel);
    }
    else
    {
        BasicIoModule::doCommmand(MIO_CMD_DISABLERST, l_ui32Channel);

    }
}

/**-----------------------------------------------------------------*/
BOOL8 CNT204::getStrobeState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRBSTAT, l_ui32Channel, (SINT32) &l_ui32Temp);
    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
BOOL8 CNT204::getZeroState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZEROSTAT, l_ui32Channel, (SINT32) &l_ui32Temp);
    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
BOOL8 CNT204::getRefSwitchState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZINIT, l_ui32Channel, (SINT32) &l_ui32Temp);
    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**-----------------------------------------------------------------*/
VOID CNT204::setFilter(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 CNT204::getFrequency(VOID)
{
    UINT32 l_ui32Value = 0;
    BasicIoModule::doCommmand(MIO_CMD_GETFREQUENCY, 0, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/

CNT204::SFlags_t* CNT204::getFlags(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_NEWTIMEVAL, l_ui32Channel, (SINT32) &l_ui32Value);
    if (1 == l_ui32Value)
    {
        m_Flags.b8NewValue = TRUE;
    }

    BasicIoModule::doCommmand(MIO_CMD_LOSTTIMEVAL, l_ui32Channel, (SINT32) &l_ui32Value);
    if (1 == l_ui32Value)
    {
        m_Flags.b8ValueLost = TRUE;
    }

    return &m_Flags;
}

/**-----------------------------------------------------------------*/
VOID CNT204::attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession, 0,
    MIO_E_POWER, pListener);
}

/**-----------------------------------------------------------------*/
VOID CNT204::attachExternalVoltage(ErrorSession *pSession, UINT8 ui8Channel,
        BasicErrorListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachError(pSession, ui32Channel,
    MIO_E_EXTERNAL, pListener);
}

/**-----------------------------------------------------------------*/
VOID CNT204::attachDecoderError(ErrorSession *pSession, UINT8 ui8Channel,
        BasicErrorListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachError(pSession, ui32Channel,
    MIO_E_DECODER, pListener);
}

/**-----------------------------------------------------------------*/
VOID CNT204::attachReferenceCompare(EventSession *pSession, UINT8 ui8Channel,
        BasicEventListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, ui32Channel,
    MIO_EV_REFERENCE, pListener);
}

/**-----------------------------------------------------------------*/
VOID CNT204::attachReset(EventSession *pSession, UINT8 ui8Channel, BasicEventListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, ui32Channel,
    MIO_EV_RESET, pListener);
}
