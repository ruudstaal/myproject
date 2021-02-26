/**
 ********************************************************************************
 * @file     ISI2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of position module ISI2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "ISI2XX.hpp"


const UINT32 ISI2XX::MODE_INC = MIO_M_INC;
const UINT32 ISI2XX::MODE_SINGLE = MIO_M_SINGLE;
const UINT32 ISI2XX::MODE_DOUBLE = MIO_M_DOUBLE;
const UINT32 ISI2XX::MODE_QUAD = MIO_M_QUAD;
const UINT32 ISI2XX::MODE_NO_ZERO = MIO_M_NOZERO;
const UINT32 ISI2XX::MODE_NO_HOME = MIO_M_NOHOME;
const UINT32 ISI2XX::MODE_AUTOLD = MIO_M_AUTOLD;
const UINT32 ISI2XX::MODE_LATCH_REF = MIO_M_LATHOME_R;
const UINT32 ISI2XX::MODE_LATCH_STROBE = MIO_M_LATHOME_S;
const UINT32 ISI2XX::MODE_LATCH_STROBE_TRIG = MIO_M_LATTRIG_S;
const UINT32 ISI2XX::MODE_SYNC = MIO_M_SYNC;
const UINT32 ISI2XX::MODE_PULSEDIR = MIO_M_PULSEDIR;
const UINT32 ISI2XX::MODE_RESET = MIO_M_RESET;
const UINT32 ISI2XX::MODE_SSI = MIO_M_SSI;
const UINT32 ISI2XX::MODE_VROUT = MIO_M_VR;
const UINT32 ISI2XX::MODE_SETOUT = MIO_M_SET;
const UINT32 ISI2XX::MODE_NOPARITY = MIO_M_NOPRTY;
const UINT32 ISI2XX::MODE_PAR_EVEN = MIO_M_EVEN;
const UINT32 ISI2XX::MODE_PAR_ODD = MIO_M_ODD;
const UINT32 ISI2XX::MODE_BINARY = MIO_M_BIN;
const UINT32 ISI2XX::MODE_GRAY= MIO_M_GRAY;
const UINT32 ISI2XX::MAX_SSI_FREQUENCY = 2000;
const UINT32 ISI2XX::MIN_SSI_FREQUENCY = 100;
const UINT32 ISI2XX::MAXFILTER = 8000;
const UINT32 ISI2XX::MINFILTER = 8;

/**-----------------------------------------------------------------*/
ISI2XX::ISI2XX()
    : BasicAnalogModule()
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
ISI2XX::ISI2XX(UINT32 ui32CardNumber)
    : BasicAnalogModule(ui32CardNumber)
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
ISI2XX::~ISI2XX()
{

}

/**-----------------------------------------------------------------*/
VOID ISI2XX::enableReset(UINT8 ui8Channel, BOOL8 b8Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    if (TRUE == b8Value)
    {
        BasicIoModule::doCommmand(MIO_CMD_ENABLERST,
                                  l_ui32Channel);
    }

    BasicIoModule::doCommmand(MIO_CMD_DISABLERST,
                              l_ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETREF,
                              l_ui32Channel,
                              (SINT32)si32Value);
}

/**-----------------------------------------------------------------*/
SINT32 ISI2XX::getReferenceRegister(UINT8 ui8Channel)
{
	SINT32 l_si32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETREF,
                                      l_ui32Channel,
                                      (SINT32)&l_si32Value);
    return l_si32Value;
}

/**-----------------------------------------------------------------*/
BOOL8 ISI2XX::getReferenceState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRST,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
	if (1 == l_ui32Value)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**-----------------------------------------------------------------*/
SINT32 ISI2XX::getStrobeRegister(UINT8 ui8Channel)
{
    SINT32 l_si32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRB,
                              l_ui32Channel,
                              (SINT32)&l_si32Value);
    return l_si32Value;
}

/**-----------------------------------------------------------------*/
BOOL8 ISI2XX::getStrobeState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRBSTAT,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
	if (1 == l_ui32Value)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**-----------------------------------------------------------------*/
BOOL8 ISI2XX::getZeroState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value    = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZEROSTAT,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
	if (1 == l_ui32Value)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**-----------------------------------------------------------------*/
BOOL8 ISI2XX::getRefSwitchState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZINIT,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
	if (1 == l_ui32Value)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setSSIFrequency(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFREQ,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getSSIFrequency(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFREQ,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setSSIDataLen(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETDLEN,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getSSIDataLen(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETDLEN,
                                      l_ui32Channel,
                                      (SINT32)&l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setSSIDelay(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETINTERVAL,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getSSIDelay(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETINTERVAL,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setFilter(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setInputMode(UINT8 ui8Channel, ISI2XX::EInputLevel_t eValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETACTIVELEVEL,
                              l_ui32Channel,
                              (SINT32)eValue);
}

/**-----------------------------------------------------------------*/
ISI2XX::EInputLevel_t ISI2XX::getInputMode(UINT8 ui8Channel)
{
    UINT32 l_ui32Temp = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETACTIVELEVEL,
                              l_ui32Channel,
                              (SINT32)&l_ui32Temp);

	if (MIO_HIGHACTIVE == l_ui32Temp)
	{
		return ISI2XX::eHighActive;
	}
	else
	{
		return ISI2XX::eLowActive;
	}
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getCounter(UINT8 ui8Channel)
{
	UINT32 l_ui32Counter = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETVAL,
                              l_ui32Channel,
                              (SINT32)&l_ui32Counter);
    return l_ui32Counter;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setEncoderCheck(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETENCRES,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getEncoderCheck(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
	UINT32 l_ui32EncoderCheck = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETENCRES,
                              l_ui32Channel,
                              (SINT32)&l_ui32EncoderCheck);
    return l_ui32EncoderCheck;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setResetRegister(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETRESETVALUE,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getResetRegister(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32ResetRegister = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRESETVALUE,
                              l_ui32Channel,
                              (SINT32)&l_ui32ResetRegister);
    return l_ui32ResetRegister;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setGateTime(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETGATETIME,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getGateTime(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32GateTime = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETGATETIME,
                              l_ui32Channel,
                              (SINT32)&l_ui32GateTime);
    return l_ui32GateTime;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setReferenceOffset(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETDISTANCEREF,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ISI2XX::getReferenceOffset(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32ReferanceOffset = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETDISTANCEREF,
                              l_ui32Channel,
                              (SINT32)&l_ui32ReferanceOffset);
    return l_ui32ReferanceOffset;
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setNullEdge(UINT8 ui8Channel, ISI2XX::EEdge_t eValue)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_CONFIGNULLEDGE,
                              l_ui32Channel,
                              (SINT32)eValue);
}

/**-----------------------------------------------------------------*/
ISI2XX::EEdge_t ISI2XX::getNullEdge(UINT8 ui8Channel)
{
    UINT32 l_ui32Temp = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETNULLEDGE,
                              l_ui32Channel,
                              (SINT32)&l_ui32Temp);

    if (MIO_M_NEGEDGE == l_ui32Temp)
	{
		return ISI2XX::eNegative;
	}
	else
	{
		return ISI2XX::ePositive;
	}
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::setBrokenWireDetection(UINT8 ui8Channel, BOOL8 b8Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    if (TRUE == b8Value)
    {

        BasicIoModule::doCommmand(MIO_CMD_ENABLENULL,
                                  l_ui32Channel,
                                  1);
    }

    BasicIoModule::doCommmand(MIO_CMD_ENABLENULL,
                              l_ui32Channel,
                              0);
}

/**-----------------------------------------------------------------*/
BOOL8 ISI2XX::getBrokenWireDetection(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_ISNULLENABLED,
                                      l_ui32Channel,
                                      (SINT32)&l_ui32Value);

	if (1 == l_ui32Value)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::attachPowerFail(ErrorSession *pSession,
                               BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession,
                               0,
                               MIO_E_POWER,
                               pListener);
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::attachReferenceCompare(EventSession *pSession,
                                      UINT8 ui8Channel,
                                      BasicEventListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::attachEvent(pSession,
                               ui32Channel,
                               MIO_EV_REFERENCE,
                               pListener);
}

/**-----------------------------------------------------------------*/
VOID ISI2XX::attachReset(EventSession *pSession,
                           UINT8 ui8Channel,
                           BasicEventListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::attachEvent(pSession,
                               ui32Channel,
                               MIO_EV_RESET,
                               pListener);
}
