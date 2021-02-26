/**
 ********************************************************************************
 * @file     AIX212.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AIC212
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AIC212.hpp"
#include <string.h>

const UINT32 AIC212::MAXFILTER = 46875;
const UINT32 AIC212::MINFILTER = 183;
const UINT32 AIC212::MODE_50KHZ = MIO_M_50KHZ;
const UINT32 AIC212::MODE_25KHZ = MIO_M_25KHZ;
const UINT32 AIC212::MODE_12KHZ = MIO_M_12KHZ;
const UINT32 AIC212::MODE_6KHZ = MIO_M_6KHZ;
const UINT32 AIC212::MODE_INC = MIO_M_INC;
const UINT32 AIC212::MODE_CONTINUOUS = MIO_M_CONTINUOUS;
const UINT32 AIC212::MODE_NO_ZERO = MIO_M_NOZERO;
const UINT32 AIC212::MODE_NO_HOME = MIO_M_NOHOME;
const UINT32 AIC212::MODE_PULSE_DIR = MIO_M_PULSEDIR;
const UINT32 AIC212::MODE_SINGLE = MIO_M_SINGLE;
const UINT32 AIC212::MODE_DOUBLE = MIO_M_DOUBLE;
const UINT32 AIC212::MODE_QUAD = MIO_M_QUAD;
const UINT32 AIC212::MODE_COUNT_TIME = MIO_M_CNTTIME;
const UINT32 AIC212::MODE_DIFF_TIME = MIO_M_DIFFTIME;
const UINT32 AIC212::MODE_SYNC = MIO_M_SYNC;
const UINT32 AIC212::MODE_TRIGG = MIO_M_TRIGG;
const UINT32 AIC212::MODE_RESET = MIO_M_RESET;

/**----------------------------------------------------------------- */
AIC212::AIC212() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIC212::AIC212(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AIC212::~AIC212()
{

}

/**----------------------------------------------------------------- */
VOID AIC212::attachReference(EventSession* pSession, UINT8 ui8Channel,
        BasicEventListener* pListener)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, l_ui32Channel,
    MIO_EV_REFERENCE, pListener);
}

/**----------------------------------------------------------------- */
VOID AIC212::attachStrobe(EventSession* pSession, BasicEventListener* pListener)
{
    BasicIoModule::attachEvent(pSession, 14,
    MIO_EV_LATCHSTRB, pListener);
}

/**----------------------------------------------------------------- */
VOID AIC212::setTemporaryDir(CHAR8* pch8Directory)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_SETTEMPDIR, l_ui32Channel, (SINT32) pch8Directory);
}

/**----------------------------------------------------------------- */
VOID AIC212::getTemporaryDir(CHAR8* pch8Directory)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETTEMPDIR, l_ui32Channel, (SINT32) pch8Directory);
}

/**----------------------------------------------------------------- */
VOID AIC212::setCompressionRate(ECompression_t Compression)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Value = (SINT32) Compression;

    BasicIoModule::doCommmand(MIO_CMD_SETCOMPRESSION, l_ui32Channel, (SINT32) l_ui32Value);
}

/**----------------------------------------------------------------- */
AIC212::ECompression_t AIC212::getCompressionRate(VOID)
{
    UINT32 l_ui32Channel = 0;
    ECompression_t l_Compression;

    BasicIoModule::doCommmand(MIO_CMD_GETCOMPRESSION, l_ui32Channel, (SINT32) &l_Compression);
    return l_Compression;
}

/**----------------------------------------------------------------- */
VOID AIC212::setRecordLen(UINT16 ui16Len)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Value = (SINT32) ui16Len;

    BasicIoModule::doCommmand(MIO_CMD_SETRECORDLEN, l_ui32Channel, (SINT32) l_ui32Value);
}

/**----------------------------------------------------------------- */
UINT16 AIC212::getRecordLen(VOID)
{
    UINT32 l_ui32Channel = 0;
    UINT16 l_ui16RecordingLength = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETRECORDLEN, l_ui32Channel, (SINT32) &l_ui16RecordingLength);
    return l_ui16RecordingLength;
}

/**----------------------------------------------------------------- */
AIC212::EStatus_t AIC212::getStatus(VOID)
{
    UINT32 l_ui32Channel = 0;
    EStatus_t l_ui32Status;

    BasicIoModule::doCommmand(MIO_CMD_GETSTATUS, l_ui32Channel, (SINT32) &l_ui32Status);
    return l_ui32Status;
}

/**----------------------------------------------------------------- */
VOID AIC212::startRecording(AIC212::EStart_t Mode)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_START, l_ui32Channel, (SINT32) Mode);
}

/**----------------------------------------------------------------- */
VOID AIC212::stopRecording(VOID)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_STOP, l_ui32Channel);
}

/**----------------------------------------------------------------- */
UINT32 AIC212::getFrequency(VOID)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Frequency = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETFREQUENCY, l_ui32Channel, (SINT32) &l_ui32Frequency);
    return l_ui32Frequency;
}

/**----------------------------------------------------------------- */
UINT32 AIC212::getMemSize(VOID)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32MemorySize = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETMEMSIZE, l_ui32Channel, (SINT32) &l_ui32MemorySize);
    return l_ui32MemorySize;
}

/**----------------------------------------------------------------- */
VOID AIC212::getRecordedValues(UINT32 ui32FirstIndex, UINT32* pui32Count, SINT32* psi32Values)
{
    UINT32 l_ui32Channel = 0;
    PARAMETERLIST l_Parameter;

    memset(&l_Parameter[0], 0, sizeof(l_Parameter));

    l_Parameter[0] = (SINT32) ui32FirstIndex;
    l_Parameter[1] = (SINT32) pui32Count;
    l_Parameter[2] = (SINT32) psi32Values;

    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, l_ui32Channel, &l_Parameter, 3);
}

/**----------------------------------------------------------------- */
VOID AIC212::startExport(CHAR8* pch8Filename)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_EXPORTVALUES, l_ui32Channel, (SINT32) pch8Filename);
}

/**----------------------------------------------------------------- */
VOID AIC212::openRecord(AIC212::FILEHANDLE* pHandle, CHAR* pch8Filename)
{
    UINT32 l_ui32Channel = 0;
    PARAMETERLIST l_Parameter;

    memset(&l_Parameter[0], 0, sizeof(l_Parameter));

    l_Parameter[0] = (SINT32) pHandle;
    l_Parameter[1] = (SINT32) pch8Filename;

    BasicIoModule::doCommmand(MIO_CMD_OPEN, l_ui32Channel, &l_Parameter, 2);
}

/**----------------------------------------------------------------- */
VOID AIC212::closeRecord(AIC212::FILEHANDLE handle)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_CLOSE, l_ui32Channel, (SINT32) handle);
}

/**----------------------------------------------------------------- */
AIC212::WAVEFILE* AIC212::readHeader(UINT8 ui8Channel, AIC212::FILEHANDLE handle)
{
    UINT32 l_ui32Channel = 0;
    PARAMETERLIST l_Parameter;

    memset(&l_Parameter[0], 0, sizeof(l_Parameter));

    l_Parameter[0] = (SINT32) handle;
    l_Parameter[1] = (SINT32) &m_WaveHeader;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_READHEADER, l_ui32Channel, &l_Parameter, 2);
    return &m_WaveHeader;
}

/**----------------------------------------------------------------- */
VOID AIC212::readSamples(UINT8 ui8Channel, AIC212::FILEHANDLE handle, UINT32 ui32FirstIndex,
        UINT32* pui32Count, SINT32* psi32Values)
{
    UINT32 l_ui32Channel = 0;
    PARAMETERLIST l_Parameter;

    memset(&l_Parameter[0], 0, sizeof(l_Parameter));

    l_Parameter[0] = (SINT32) handle;
    l_Parameter[1] = (SINT32) ui32FirstIndex;
    l_Parameter[2] = (SINT32) pui32Count;
    l_Parameter[3] = (SINT32) psi32Values;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_READSAMPLES, l_ui32Channel, &l_Parameter, 4);
}

/**----------------------------------------------------------------- */
VOID AIC212::setSimulationValues(CHAR8 pch8Filename)
{
    UINT32 l_ui32Channel = 0;

    BasicIoModule::doCommmand(MIO_CMD_SIMULATEVALUES, l_ui32Channel, (SINT32) pch8Filename);
}

/**----------------------------------------------------------------- */
SINT32 AIC212::getCounter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32Counter;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETACT, l_ui32Channel, (SINT32) &l_si32Counter);
    return l_si32Counter;
}

/**----------------------------------------------------------------- */
VOID AIC212::disableReference(VOID)
{
    UINT32 l_ui32Channel = 13;

    BasicIoModule::doCommmand(MIO_CMD_DISABLERST, l_ui32Channel);
}

/**----------------------------------------------------------------- */
VOID AIC212::enableReference(VOID)
{
    UINT32 l_ui32Channel = 13;

    BasicIoModule::doCommmand(MIO_CMD_ENABLERST, l_ui32Channel);
}

/**----------------------------------------------------------------- */
BOOL8 AIC212::isReferenceDone(VOID)
{
    UINT32 l_ui32Channel = 13;
    UINT32 l_ui32Value = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETRST, l_ui32Channel, (SINT32) &l_ui32Value);
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
VOID AIC212::setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETREF, l_ui32Channel, (SINT32) si32Value);
}

/**----------------------------------------------------------------- */
SINT32 AIC212::getReferenceRegister(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    SINT32 l_si32ReferanceRegister = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETREF, l_ui32Channel, (SINT32) &l_si32ReferanceRegister);
    return l_si32ReferanceRegister;
}

/**----------------------------------------------------------------- */
SINT32 AIC212::getStrobeRegister(VOID)
{
    UINT32 l_ui32Channel = 13;
    UINT32 l_ui32StrobeRegister = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRB, l_ui32Channel, (SINT32) &l_ui32StrobeRegister);
    return l_ui32StrobeRegister;
}

/**----------------------------------------------------------------- */
BOOL8 AIC212::isStrobeTriggerd(VOID)
{
    UINT32 l_ui32Channel = 13;
    UINT32 l_ui32Value = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETSTRBSTAT, l_ui32Channel, (SINT32) &l_ui32Value);
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
VOID AIC212::resetStrobeRegister(VOID)
{
    UINT32 l_ui32Channel = 13;

    BasicIoModule::doCommmand(MIO_CMD_RESETSTRBSTAT, l_ui32Channel);
}

/**----------------------------------------------------------------- */
BOOL8 AIC212::isZeroInputActive(VOID)
{
    UINT32 l_ui32Channel = 13;
    UINT32 l_ui32Value = 0;

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

/**----------------------------------------------------------------- */
VOID AIC212::setFilter(UINT8 ui8Channel, UINT32 ui32Filter)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) ui32Filter);
}

/**----------------------------------------------------------------- */
UINT32 AIC212::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Filter = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER, l_ui32Channel, (SINT32) &l_ui32Filter);
    return l_ui32Filter;
}

/**----------------------------------------------------------------- */
BOOL8 AIC212::getInputState(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (SINT32) ui8Channel;

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
BOOL8 AIC212::getReferenceSwitch(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Value = 0;

    l_ui32Channel = (SINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_ZINIT, l_ui32Channel, (SINT32) &l_ui32Value);
    if (1 == l_ui32Value)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

