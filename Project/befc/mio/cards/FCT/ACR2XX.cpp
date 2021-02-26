/**
 ********************************************************************************
 * @file     ACR2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of axis control module ACR2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "ACR2XX.hpp"
#include <string.h>

const UINT32 ACR2XX::MODE_LINEAR = MIO_M_PROF_LIN;
const UINT32 ACR2XX::MODE_SINUS = MIO_M_PROF_SIN;
const UINT32 ACR2XX::MODE_PARABOLIC = MIO_M_PROF_PARAB;
const UINT32 ACR2XX::MODE_FREQUENCY = MIO_M_PROF_FREQ;

/**-----------------------------------------------------------------*/
ACR2XX::ACR2XX() :
        BasicAnalogModule()
{
    init();

    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
ACR2XX::ACR2XX(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    init();

    /** Check card type */
    checkCardType();
}

VOID ACR2XX::init()
{
    memset(&m_Homing, 0, sizeof(m_Homing));
    memset(&m_Profile, 0, sizeof(m_Profile));
    memset(&m_Setting, 0, sizeof(m_Setting));
    memset(&m_DriveData, 0, sizeof(m_DriveData));
    memset(&m_Resoultion, 0, sizeof(m_Resoultion));
    memset(&m_StatusWord, 0, sizeof(m_StatusWord));
    memset(&m_SwitchState, 0, sizeof(m_SwitchState));
    memset(&m_StateHistory, 0, sizeof(m_StateHistory));
}

/**-----------------------------------------------------------------*/
ACR2XX::~ACR2XX()
{

}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setProfile(UINT8 ui8Channel, SProfile_t* psProfile)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETPROF, l_ui32Channel, (SINT32) psProfile);
}

/**-----------------------------------------------------------------*/
ACR2XX::SProfile_t* ACR2XX::getProfile(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPROF, l_ui32Channel, (SINT32) &m_Profile);
    return &m_Profile;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setHome(UINT8 ui8Channel, SHome_t* psHome)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETHOME, l_ui32Channel, (SINT32) psHome);
}

/**-----------------------------------------------------------------*/
ACR2XX::SHome_t* ACR2XX::getHoming(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETHOME, l_ui32Channel, (SINT32) &m_Homing);
    return &m_Homing;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setDriveData(UINT8 ui8Channel, SDriveData_t* psData)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETDRIVEDATA, l_ui32Channel, (SINT32) psData);
}

/**-----------------------------------------------------------------*/
ACR2XX::SDriveData_t* ACR2XX::getDriveData(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETDRIVEDATA, l_ui32Channel, (SINT32) &m_DriveData);
    return &m_DriveData;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setResoultion(UINT8 ui8Channel, SResolution_t* psResolution)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETRESOLUTION, l_ui32Channel, (SINT32) psResolution);
}

/**-----------------------------------------------------------------*/
ACR2XX::SResolution_t* ACR2XX::getResoultion(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETRESOLUTION, l_ui32Channel, (SINT32) &m_Resoultion);
    return &m_Resoultion;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setSettings(UINT8 ui8Channel, SSettings_t* psSettings)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Setting = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (psSettings->b8Boost)
    {
        l_ui32Setting |= 0x1;
    }

    if (psSettings->b8Standby)
    {
        l_ui32Setting |= 0x2;
    }

    if (psSettings->b8Step)
    {
        l_ui32Setting |= 0x4;
    }

    if (psSettings->b8Index)
    {
        l_ui32Setting |= 0x8;
    }

    switch (psSettings->eMode)
    {
        case eQuad:
            l_ui32Setting |= 0x00;
            break;
        case eDouble:
            l_ui32Setting |= 0x10;
            break;
        case eSingle:
            l_ui32Setting |= 0x20;
            break;
        case eNegative:
            l_ui32Setting |= 0x30;
            break;
    }

    BasicIoModule::doCommmand(MIO_CMD_SETCOMMONSETTINGS, l_ui32Channel, (SINT32) l_ui32Setting);
}

/**-----------------------------------------------------------------*/
ACR2XX::SSettings_t* ACR2XX::getSettings(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Setting = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETCOMMONSETTINGS, l_ui32Channel, (SINT32) &l_ui32Setting);
    if ((l_ui32Setting & 0x1) > 0)
    {
        m_Setting.b8Boost = TRUE;
    }

    if ((l_ui32Setting & 0x2) > 0)
    {
        m_Setting.b8Standby = TRUE;
    }

    if ((l_ui32Setting & 0x4) > 0)
    {
        m_Setting.b8Step = TRUE;
    }

    if ((l_ui32Setting & 0x8) > 0)
    {
        m_Setting.b8Index = TRUE;
    }

    /** 0 -> QUAD */
    m_Setting.eMode = eQuad;

    if ((l_ui32Setting & 0x30) == 0x10)
    {
        m_Setting.eMode = eDouble;
    }

    if ((l_ui32Setting & 0x30) == 0x20)
    {
        m_Setting.eMode = eSingle;
    }

    if ((l_ui32Setting & 0x30) == 0x30)
    {
        m_Setting.eMode = eNegative;
    }

    return &m_Setting;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setQuickDecel(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETQUICKDECEL, l_ui32Channel, (SINT32) ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ACR2XX::getQuickDecel(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETQUICKDECEL, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setErrorWindow(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETERRORWINDOW, l_ui32Channel, (SINT32) ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ACR2XX::getErrorWindow(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETERRORWINDOW, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setMaxFrequency(UINT8 ui8Channel, UINT32 ui32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETMAXFREQ, l_ui32Channel, (SINT32) ui32Value);
}

/**-----------------------------------------------------------------*/
UINT32 ACR2XX::getMaxFrequency(UINT8 ui8Channel)
{
    UINT32 l_ui32Value;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETMAXFREQ, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
ACR2XX::SStateHistory_t* ACR2XX::getStateHistory(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32History = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSTATEHIST, l_ui32Channel, (SINT32) &l_ui32History);

    for (UINT8 i = 0; i < 6; ++i)
    {
        /**
         * History is copied into one 32-Bit Variable
         * There are 6 entries (e) and a 16 Bit Counter (c)
         * each entry contains 4 Status Bits
         *
         * 32                                       0
         *   cccc cccc eeee eeee eeee eeee eeee eeee
         */
        buildState(&m_StateHistory.sState[i], l_ui32History, i);

    }

    buildCounter(&m_StateHistory.u8Counter, l_ui32History);

    return &m_StateHistory;
}

/**-----------------------------------------------------------------*/
UINT32 ACR2XX::getErrorCode(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32ErrorCode = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETERRORCODE, l_ui32Channel, (SINT32) &l_ui32ErrorCode);
    return l_ui32ErrorCode;
}

/**-----------------------------------------------------------------*/
BOOL8 ACR2XX::getReferenceSwitchState(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZINIT, l_ui32Channel, (SINT32) &l_ui32Value);

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
ACR2XX::SDigitalInput_t* ACR2XX::getSwitchState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSWITCHSTATE, l_ui32Channel, (SINT32) &l_ui32Value);

    memset((char*) &m_SwitchState, 0, sizeof(SDigitalInput_t));
    m_SwitchState.b8PosLimit = BitCheck(l_ui32Value, 0x01);
    m_SwitchState.b8NegLimit = BitCheck(l_ui32Value, 0x02);
    m_SwitchState.b8EmyStop = BitCheck(l_ui32Value, 0x04);
    m_SwitchState.b8Reference = BitCheck(l_ui32Value, 0x08);
    m_SwitchState.b8ZeroPulse = BitCheck(l_ui32Value, 0x10);

    return &m_SwitchState;
}

/**-----------------------------------------------------------------*/
BOOL8 ACR2XX::getZeroState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETZEROSTAT, l_ui32Channel, (SINT32) &l_ui32Value);
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
void ACR2XX::buildState(SState_t* psState, UINT32 ui32Value, UINT8 ui8Index)
{

    UINT32 l_ui32Value = ui32Value >> ui8Index;

    if (NULL == psState)
    {
        return;
    }

    psState->b8Stop = (l_ui32Value & 0x1) > 0 ? TRUE : FALSE;
    psState->b8Run = (l_ui32Value & 0x2) > 0 ? TRUE : FALSE;
    psState->b8TargetReached = (l_ui32Value & 0x4) > 0 ? TRUE : FALSE;
    psState->b8Follow = (l_ui32Value & 0x8) > 0 ? TRUE : FALSE;
}

/**-----------------------------------------------------------------*/
void ACR2XX::buildCounter(UINT8* pui8Counter, UINT32 ui32Value)
{
    UINT32 l_ui32Value = ui32Value >> 24;

    *pui8Counter = (UINT8) (l_ui32Value & 0xFF);
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession, 0,
    MIO_E_POWER, pListener);
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::attachReset(EventSession *pSession, UINT8 ui8Channel, BasicEventListener *pListener)
{
    UINT32 ui32Channel = 0;

    ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, ui32Channel,
    MIO_EV_RESET, pListener);
}

/**-----------------------------------------------------------------*/
VOID ACR2XX::setControlWord(UINT8 ui8Channel, SControlword_t* psControl)
{

    UINT32 l_ui32Value = 0;
    AnalogChannel *l_pChannel = getAnalogChannel(ui8Channel + 4);

    if (NULL == l_pChannel)
    {
        throw MIOexception("ACR2XX::setControlword: invalid parameter ", ui8Channel,
        MIO_ER_BADPARM);
    }

    if (TRUE == psControl->b8DisableVoltage)
    {
        l_ui32Value |= 0x0001;
    }

    if (TRUE == psControl->b8QuickStop)
    {
        l_ui32Value |= 0x0002;
    }

    if (TRUE == psControl->b8Stop)
    {
        l_ui32Value |= 0x0004;
    }

    if (TRUE == psControl->b8Start)
    {
        l_ui32Value |= 0x0008;
    }

    if (TRUE == psControl->b8DualStart)
    {
        l_ui32Value |= 0x0010;
    }

    if (TRUE == psControl->b8MoveRelative)
    {
        l_ui32Value |= 0x0040;
    }

    if (TRUE == psControl->b8ChangeSpeed)
    {
        l_ui32Value |= 0x0080;
    }

    if (eModeReference == psControl->eMode)
    {
        l_ui32Value |= 0x0400;
    }

    if (eModeFreeRun == psControl->eMode)
    {
        l_ui32Value |= 0x0800;
    }

    if (eModeProfile == psControl->eMode)
    {
        l_ui32Value |= 0x0C00;
    }

    l_pChannel->setValue(l_ui32Value);
}

/**-----------------------------------------------------------------*/
ACR2XX::SStatusword_t* ACR2XX::getStatusWord(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    AnalogChannel *l_pChannel = getAnalogChannel(ui8Channel + 6);

    if (NULL == l_pChannel)
    {
        throw MIOexception("ACR2XX::getStatusWord: failed to get analog channel pointer",
                ui8Channel, MIO_ER_FAIL);
    }

    l_ui32Value = l_pChannel->getValue();
    m_StatusWord.b8Undefined = BitCheck(l_ui32Value, 0x0001);

    if (TRUE == m_StatusWord.b8Undefined)
    {
        return &m_StatusWord;
    }

    m_StatusWord.b8DisableVoltage = BitCheck(l_ui32Value, 0x0001);
    m_StatusWord.b8QuickStop = BitCheck(l_ui32Value, 0x0002);
    m_StatusWord.b8Stop = BitCheck(l_ui32Value, 0x0004);
    m_StatusWord.b8Start = BitCheck(l_ui32Value, 0x0008);
    m_StatusWord.b8TargetReached = BitCheck(l_ui32Value, 0x0010);
    m_StatusWord.b8FollowingError = BitCheck(l_ui32Value, 0x0020);
    m_StatusWord.b8Error = BitCheck(l_ui32Value, 0x0040);
    m_StatusWord.b8ChangeSpeed = BitCheck(l_ui32Value, 0x0080);
    m_StatusWord.b8Busy = BitCheck(l_ui32Value, 0x0400);

    /** 2 bit Mapping of Profile */
    m_StatusWord.eProfile = eProfileLinear;
    if (TRUE == BitCheck(l_ui32Value, 0x0300))
    {
        m_StatusWord.eProfile = eProfileFrequency;
    }
    else
    {
        if (TRUE == BitCheck(l_ui32Value, 0x0100))
        {
            m_StatusWord.eProfile = eProfileSinus;
        }

        if (TRUE == BitCheck(l_ui32Value, 0x0200))
        {
            m_StatusWord.eProfile = eProfileParabolic;
        }
    }

    /** 2 bit Mapping of Mode */
    m_StatusWord.eMode = eModeRamp;
    if (TRUE == BitCheck(l_ui32Value, 0x0C00))
    {
        m_StatusWord.eMode = eModeProfile;
    }
    else
    {
        if (TRUE == BitCheck(l_ui32Value, 0x0400))
        {
            m_StatusWord.eMode = eModeReference;
        }

        if (TRUE == BitCheck(l_ui32Value, 0x0800))
        {
            m_StatusWord.eMode = eModeFreeRun;
        }
    }

    return &m_StatusWord;
}
