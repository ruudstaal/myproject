/**
 ********************************************************************************
 * @file     PWM202.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of pulse width modulation module PWM202
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "PWM202.hpp"
#include <string.h>



const UINT32 PWM202::MODE_OPERATE        = MIO_M_OPERATE;
const UINT32 PWM202::MODE_PWM            = MIO_M_PWM;
const UINT32 PWM202::MODE_CONTROL        = MIO_M_CONTROL;
const UINT32 PWM202::MODE_SMA            = MIO_M_SMA;
const UINT32 PWM202::MODE_LAP            = MIO_M_LAP;
const UINT32 PWM202::MODE_BRAKE          = MIO_M_BRAKE;
const UINT32 PWM202::MODE_BRAKE_UPPER    = MIO_M_UPPER;
const UINT32 PWM202::MODE_BRAKE_LOWER    = MIO_M_LOWER;
const UINT32 PWM202::MODE_BRAKE_OPEN     = MIO_M_OPEN;
const UINT32 PWM202::MODE_ALIGN_EDGE     = MIO_M_EDGE;
const UINT32 PWM202::MODE_ALIGN_CENTER   = MIO_M_CENTER;
const UINT32 PWM202::MODE_PRESCALE       = MIO_M_PRESCAL;
const REAL32 PWM202:: MAXSAMPLE = 32767;
const REAL32 PWM202:: MINSAMPLE = 1;
const REAL32 PWM202:: MAXPROPORTIONAL = 32767;
const REAL32 PWM202:: MINPROPORTIONAL = 1;
const REAL32 PWM202:: MAXINTEGRAL = 1000;
const REAL32 PWM202:: MININTEGRAL = 1;


/**-----------------------------------------------------------------*/
PWM202::PWM202()
    : BasicAnalogModule()
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
PWM202::PWM202(UINT32 ui32CardNumber)
    : BasicAnalogModule(ui32CardNumber)
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
PWM202::~PWM202()
{

}

/**-----------------------------------------------------------------*/
VOID PWM202::setPeriod(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPP,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 PWM202::getPeriod(UINT8 ui8Channel)
{
	UINT32 l_ui32Periode = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPP,
                              l_ui32Channel,
                              (SINT32)&l_ui32Periode);
    return l_ui32Periode;
}

/**-----------------------------------------------------------------*/
VOID PWM202::operate(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETOP,
                              l_ui32Channel,
                              1);
}

/**-----------------------------------------------------------------*/
VOID PWM202::brake(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETOP,
                              l_ui32Channel,
                              0);
}

/**-----------------------------------------------------------------*/
BOOL8 PWM202::getOpState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value  = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETOP,
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
VOID PWM202::setSampleTime(UINT8 ui8Channel, REAL32 r32Value)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value   = 0;

    memcpy(&l_ui32Value, &r32Value, sizeof(l_ui32Value));

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPAR_TS,
                              l_ui32Channel,
                              (SINT32)l_ui32Value);
}

/**-----------------------------------------------------------------*/
VOID PWM202::setProportionalTerm(UINT8 ui8Channel, REAL32 r32Value)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value   = 0;

    memcpy(&l_ui32Value, &r32Value, sizeof(l_ui32Value));

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPAR_PR,
                              l_ui32Channel,
                              (SINT32)l_ui32Value);
}

/**-----------------------------------------------------------------*/
VOID PWM202::setIntegralTerm(UINT8 ui8Channel, REAL32 r32Value)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value   = 0;

    memcpy(&l_ui32Value, &r32Value, sizeof(l_ui32Value));

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPAR_TI,
                              l_ui32Channel,
                              (SINT32)l_ui32Value);
}

/**-----------------------------------------------------------------*/
REAL32 PWM202::getSampleTime(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
	REAL32 l_r32SampleTime = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPAR_TS,
                              l_ui32Channel,
                              (SINT32)&l_r32SampleTime);
    return l_r32SampleTime;
}

/**-----------------------------------------------------------------*/
REAL32 PWM202::getProportionalTerm(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
	REAL32 l_r32ProportionalTerm = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPAR_PR,
                              l_ui32Channel,
                              (SINT32)&l_r32ProportionalTerm);
    return l_r32ProportionalTerm;
}

/**-----------------------------------------------------------------*/
REAL32 PWM202::getIntegralTerm(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    REAL32 l_r32IntegralTerm = 1.0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPAR_TI,
                              l_ui32Channel,
                              (SINT32)&l_r32IntegralTerm);
    return l_r32IntegralTerm;
}

/**-----------------------------------------------------------------*/
VOID PWM202::setLoadType(UINT8 ui8Channel, PWM202::ELoadType_t eValue)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value   = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    if (eValue == eInductive)
    {
        l_ui32Value = 1;
    }

    BasicIoModule::doCommmand(MIO_CMD_LOADTYPE,
                              l_ui32Channel,
                              (SINT32)l_ui32Value);

}

/**-----------------------------------------------------------------*/
VOID PWM202::setMaxCurrent(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_MAXCURRENT,
                              l_ui32Channel,
                              (SINT32)ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 PWM202::getMaxCurrent(UINT8 ui8Channel)
{
	UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETMAXCURRENT,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID PWM202::setResolution(UINT8 ui8Channel, EResolution_t eValue)
{
    UINT32 l_ui32Value = MIO_M_RESLO;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    if (eHigh == eValue)
    {
        l_ui32Value = MIO_M_RESHI;
    }

    BasicIoModule::doCommmand(MIO_CMD_CURRENTRES,
                              l_ui32Channel,
                              (SINT32)l_ui32Value);
}

/**-----------------------------------------------------------------*/
PWM202::EResolution_t PWM202::getResolution(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value   = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETCURRENTRES,
                              l_ui32Channel,
                              (SINT32)&l_ui32Value);

	if (MIO_M_RESHI == l_ui32Value)
	{
		return eHigh;
	}
	else
	{
		return eLow;
	}
}

/**-----------------------------------------------------------------*/
VOID PWM202::attachPowerFail(ErrorSession *pSession,
                               BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession,
                               0,
                               MIO_E_POWER,
                               pListener);
}

