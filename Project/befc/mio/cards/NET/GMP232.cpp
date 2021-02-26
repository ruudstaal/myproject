/**
 ********************************************************************************
 * @file     GMP232.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid measurement and protection module GMP232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "GMP232.hpp"
#include <string.h>
#include <math.h>
#include <limits.h>

UINT64 GMP232::csa_Selection[] =
{
GMP_VAL_U_L1N_RMS,              /** 0 */
        GMP_VAL_U_L2N_RMS,
        GMP_VAL_U_L3N_RMS,
        GMP_VAL_U_L1L2_RMS,
        GMP_VAL_U_L2L3_RMS,
        GMP_VAL_U_L3L1_RMS,
        GMP_VAL_I_L1_RMS,
        GMP_VAL_I_L2_RMS,
        GMP_VAL_I_L3_RMS,
        GMP_VAL_I_N_RMS,
        GMP_VAL_P_SUM,          /** 10 */
        GMP_VAL_P_L1,
        GMP_VAL_P_L2,
        GMP_VAL_P_L3,
        GMP_VAL_S_SUM,
        GMP_VAL_S_L1,
        GMP_VAL_S_L2,
        GMP_VAL_S_L3,
        GMP_VAL_Q_SUM,
        GMP_VAL_Q_L1,
        GMP_VAL_Q_L2,           /** 20 */
        GMP_VAL_Q_L3,
        GMP_VAL_FREQUENCY,
        GMP_VAL_ROCOF,
        GMP_VAL_ASYM_U,
        GMP_VAL_ASYM_I,
        GMP_VAL_PHI_U1I1,
        GMP_VAL_PHI_U2I2,
        GMP_VAL_PHI_U3I3,
        GMP_VAL_PF_SUM,
        GMP_VAL_PF_L1,          /** 30 */
        GMP_VAL_PF_L2,
        GMP_VAL_PF_L3,
        GMP_VAL_ROTDIR_U,
        GMP_VAL_ROTDIR_I,
        GMP_VAL_OVERLOADU,
        GMP_VAL_OVERLOADI,
        GMP_VAL_VECTORJMP,
        GMP_VAL_ALL, 0, 0,               /** 40 */
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /** 50 */
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    /** 60 */
        0, 0, 0                          /** 63 */
        };

/**-----------------------------------------------------------------*/
GMP232::GMP232() :
        BasicMixedModule()
{
    /** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GMP232::GMP232(UINT32 ui32CardNumber) :
        BasicMixedModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GMP232::~GMP232()
{

}

VOID GMP232::init(VOID)
{
    m_Output[0].setParentModule(this);
    m_Output[1].setParentModule(this);
    m_Output[0].setChannelNumber(10);
    m_Output[1].setChannelNumber(11);

    memset(&m_Event, 0, sizeof(m_Event));
    memset(&m_Values, 0, sizeof(m_Values));
    memset(&m_Energy, 0, sizeof(m_Energy));
    memset(&m_QuLimit, 0, sizeof(m_QuLimit));
    memset(&m_Progress, 0, sizeof(m_Progress));
    memset(&m_ScopeData, 0, sizeof(m_ScopeData));
    memset(&m_Statistic, 0, sizeof(m_Statistic));
    memset(&m_IecValues, 0, sizeof(m_IecValues));
    memset(&m_Harmonics, 0, sizeof(m_Harmonics));
    memset(&m_ScopeState, 0, sizeof(m_ScopeState));
    memset(&m_ScopeLimit, 0, sizeof(m_ScopeLimit));
    memset(&m_BaseConfig, 0, sizeof(m_BaseConfig));
    memset(&m_EnergyReal, 0, sizeof(m_EnergyReal));
    memset(&m_ScopeConfig, 0, sizeof(m_ScopeConfig));
    memset(&m_PhaseAngles, 0, sizeof(m_PhaseAngles));
    memset(&m_AlarmHistory, 0, sizeof(m_AlarmHistory));
    memset(&m_SampleConfig, 0, sizeof(m_SampleConfig));
    memset(&m_VectorDiagram, 0, sizeof(m_VectorDiagram));
    memset(&m_SelectedValues, 0, sizeof(m_SelectedValues));
    memset(&m_RawSampleDatas, 0, sizeof(m_RawSampleDatas));
    memset(&m_FrequencyLimit, 0, sizeof(m_FrequencyLimit));
    memset(&m_SimulationData, 0, sizeof(m_SimulationData));
    memset(&m_ScopeLockHandle, 0, sizeof(m_ScopeLockHandle));
    memset(&m_FaultRideThrough, 0, sizeof(m_FaultRideThrough));
    memset(&m_RelaySwitchCount, 0, sizeof(m_RelaySwitchCount));
    memset(&m_HistoryLockHandle, 0, sizeof(m_HistoryLockHandle));
}

/**-----------------------------------------------------------------*/
DigitalChannel* GMP232::getDigitalChannel(UINT32 ui32Channel)
{
    /**
     * only allowed for channel 10 and 11
     */
    if (10 != ui32Channel && 11 != ui32Channel)
    {
        throw MIOexception("GMP232::getDigitalChannel: invalid parameter ", ui32Channel,
        MIO_ER_BADPARM);
    }

    return &m_Output[ui32Channel - 10];
}

/**-----------------------------------------------------------------*/
VOID GMP232::deleteHistory(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_DELETEALARMHISTORY, 0);
}

/**-----------------------------------------------------------------*/
GMP232::SDisplayStatistics_t* GMP232::displayStatistics(UINT32 ui32Index, UINT32 ui32Count, GMP232::SDisplayStatistics_t* pStat)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Index;
    l_param[1] = (SINT32) ui32Count;
    l_param[2] = (SINT32) pStat;
    BasicIoModule::doCommmand(MIO_CMD_DISPSTATISTICS, 0, &l_param, 3);
    return pStat;
}

/**-----------------------------------------------------------------*/
VOID GMP232::resetStatistics(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_RESETSTATISTICS, 0);
}

/**-----------------------------------------------------------------*/
GMP232::SProgress_t* GMP232::getExportProgress(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETPROGRESS, 0, (SINT32) &m_Progress);

    if (m_Progress.Status == PROGRESS_DONE)
    {
        giveScopeLock();
    }

    return &m_Progress;
}

/**-----------------------------------------------------------------*/
VOID GMP232::exportScope(CHAR8* pch8Filename)
{
    PARAMETERLIST l_param;

    if (takeScopeLock(GMP_SCOPELOCKTIMEOUT))
    {
        l_param[0] = (SINT32) &m_ScopeLockHandle;
        l_param[1] = (SINT32) pch8Filename;
        l_param[2] = 0; /** Flags (can be ignored) */

        BasicIoModule::doCommmand(MIO_CMD_EXPORTSCOPE, 0, &l_param, 3);
        giveScopeLock();
    }
}

/**-----------------------------------------------------------------*/
VOID GMP232::exportScopeNB(CHAR8* pch8Filename)
{
    PARAMETERLIST l_param;

    if (takeScopeLock(GMP_SCOPELOCKTIMEOUT))
    {
        l_param[0] = (SINT32) &m_ScopeLockHandle;
        l_param[1] = (SINT32) pch8Filename;
        l_param[2] = 0;     // Flags (can be ignored)

        /** Export in Backgroundtask */
        BasicIoModule::doCommmand(MIO_CMD_EXPORTSCOPEINTASK, 0, &l_param, 3);
    }
}

/**-----------------------------------------------------------------*/
VOID GMP232::processIniFile(CHAR8 pch8Filename)
{
    BasicIoModule::doCommmand(MIO_CMD_PROCESSINIFILE, 0, (SINT32) pch8Filename);
}

/**-----------------------------------------------------------------*/
VOID GMP232::forceRelay(UINT8 ui8Channel, BOOL8 b8Value)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Temp = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    if (TRUE == b8Value)
    {
        l_ui32Temp = TRUE;
    }

    BasicIoModule::doCommmand(MIO_CMD_FORCERELAY, l_ui32Channel, (SINT32) l_ui32Temp);
}

/**-----------------------------------------------------------------*/
VOID GMP232::resetRelay(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_RESETRELAY, l_ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID GMP232::takeHistoryLock(UINT32 ui32Timeout)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Timeout;
    l_param[1] = (SINT32) &m_HistoryLockHandle;

    BasicIoModule::doCommmand(MIO_CMD_TAKEHISTORYLOCK, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
VOID GMP232::giveHistoryLock(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GIVEHISTORYLOCK, 0, (SINT32) m_HistoryLockHandle);
}

/**-----------------------------------------------------------------*/
BOOL8 GMP232::takeScopeLock(UINT32 ui32Timeout)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Timeout;
    l_param[1] = (SINT32) &m_ScopeLockHandle;

    try
    {
        BasicIoModule::doCommmand(MIO_CMD_TAKESCOPELOCK, 0, &l_param, 2);
    }
    catch(MIOexception &ex)
    {
        if (ex.ErrorCode() == MIO_ER_BUSY)
            return FALSE;
        else
            throw;
    }

    return TRUE;
}

/**-----------------------------------------------------------------*/
VOID GMP232::giveScopeLock()
{

    BasicIoModule::doCommmand(MIO_CMD_GIVESCOPELOCK, 0, (SINT32) m_ScopeLockHandle);
}

/**-----------------------------------------------------------------*/
VOID GMP232::triggerScope(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_TRIGGERSCOPE, 0);
}

/**-----------------------------------------------------------------*/
GMP232::SAlarmHistory_t* GMP232::getAlarmHistory(LockHandle_t handle, UINT32 ui32Index,
        UINT32 ui32Count)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) handle;
    l_param[1] = (SINT32) ui32Index;
    l_param[2] = (SINT32) ui32Count;
    l_param[3] = (SINT32) &m_AlarmHistory;

    BasicIoModule::doCommmand(MIO_CMD_GETALARMHISTORY, 0, &l_param, 4);
    return &m_AlarmHistory;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setEnergy(SEnergy_t* pValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETENERGY, 0, (SINT32) pValue);
}

/**-----------------------------------------------------------------*/
VOID GMP232::setEnergy(SEnergyR_t* pValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETENERGYREAL, 0, (SINT32) pValue);
}

/**-----------------------------------------------------------------*/
GMP232::SEnergy_t* GMP232::getEnergy(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETENERGY, 0, (SINT32) &m_Energy);
    return &m_Energy;
}

/**-----------------------------------------------------------------*/
GMP232::SEnergyR_t* GMP232::getEnergyReal(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETENERGYREAL, 0, (SINT32) &m_EnergyReal);
    return &m_EnergyReal;
}

/**-----------------------------------------------------------------*/
GMP232::EGmpEvent_t* GMP232::getEvent(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETEVENT, l_ui32Channel, (SINT32) &m_Event);
    return &m_Event;
}

/**-----------------------------------------------------------------*/
GMP232::SHarmonics_t* GMP232::getHarmonics(EHarmonicsId_t id)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) id;
    l_param[1] = (SINT32) &m_Harmonics;

    BasicIoModule::doCommmand(MIO_CMD_GETHARMONICS, 0, &l_param, 2);
    return &m_Harmonics;
}

/**-----------------------------------------------------------------*/
UINT32 GMP232::getStatisticsCounter(VOID)
{
    UINT32 l_ui32StatisticsCounter;
    BasicIoModule::doCommmand(MIO_CMD_GETNBSTATISTICS, 0, (SINT32) &l_ui32StatisticsCounter);

    return l_ui32StatisticsCounter;
}

/**-----------------------------------------------------------------*/
GMP232::SPhaseAngels_t* GMP232::getPhaseAngles()
{
    BasicIoModule::doCommmand(MIO_CMD_GETPHASEANGLES, 0, (SINT32) &m_PhaseAngles);
    return &m_PhaseAngles;
}

/**-----------------------------------------------------------------*/
UINT32 GMP232::getPreInitErrors(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPREINITERROR, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
UINT32 GMP232::getPreInitEvents(UINT8 ui8Channel)
{
    UINT32 l_ui32Value = 0;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPREINITEVENT, l_ui32Channel, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setQULimit(SQuLimit_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_GETQULIMIT, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GMP232::SQuLimit_t* GMP232::getQULimit(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_SETQULIMIT, 0, (SINT32) &m_QuLimit);
    return &m_QuLimit;
}

/**-----------------------------------------------------------------*/
GMP232::SBaseConfig_t* GMP232::getBaseConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETCONFIG, 0, (SINT32) &m_BaseConfig);
    return &m_BaseConfig;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setRelayConfig(ERelayConfig_t eValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETRELAYCFG, 0, (SINT32) eValue);
}

/**-----------------------------------------------------------------*/
GMP232::ERelayConfig_t GMP232::getRelayConfig(VOID)
{
    ERelayConfig_t RelayConfig = eClosed;
    BasicIoModule::doCommmand(MIO_CMD_GETRELAYCFG, 0, (SINT32) RelayConfig);
    return RelayConfig;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setScopeConfig(SScopeConfig_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSCOPECFG, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GMP232::SScopeConfig_t* GMP232::getScopeConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSCOPECFG, 0, (SINT32) &m_ScopeConfig);
    return &m_ScopeConfig;
}

/**-----------------------------------------------------------------*/
UINT32 GMP232::getRunThroughConfig(VOID)
{
    UINT32 l_ui32Value = 0;
    BasicIoModule::doCommmand(MIO_CMD_GETRUNTHROUGH, 0, (SINT32) &l_ui32Value);
    return l_ui32Value;
}

/**-----------------------------------------------------------------*/
GMP232::SScopeData_t* GMP232::getScopeValues(UINT32 ui32Index, UINT32 ui32Timeout)
{
    PARAMETERLIST l_param;
    if(ui32Index == 0)
    {
		takeScopeLock(ui32Timeout);
    }

    l_param[0] = (SINT32) m_ScopeLockHandle;
    l_param[1] = (SINT32) &m_ScopeData;
    l_param[2] = (SINT32) ui32Index;

    BasicIoModule::doCommmand(MIO_CMD_GETSCOPE, 0, &l_param, 3);

    if(ui32Index == GMP_SCOPE_MAXVALIDX)
    {
    	giveScopeLock();
    }
    return &m_ScopeData;
}

/**-----------------------------------------------------------------*/
GMP232::SScopeState_t* GMP232::getScopeState(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSCOPESTATE, 0, (SINT32) &m_ScopeState);
    return &m_ScopeState;
}

/**-----------------------------------------------------------------*/
GMP232::SValues_t* GMP232::getSelectedValues(ASelection_t *paSelection)
{
    PARAMETERLIST l_param;
    UINT64 l_ui64Selection = 0LL;

    l_param[0] = (SINT32) &m_SelectedValues;
    l_param[1] = (SINT32) &l_ui64Selection;

    /** if "ALL" is selected there is nothing else to do */
    if (TRUE == (*paSelection)[eSlctALL])
    {
        l_ui64Selection = GMP_VAL_ALL;
    }
    else
    {
        /** if "ALL" is not selected loop through Bitmask an map */
        for (int iLoop = 0; iLoop < (int) eSlctALL; ++iLoop)
        {
            if (TRUE == (*paSelection)[iLoop])
            {
                l_ui64Selection = l_ui64Selection | GMP232::csa_Selection[iLoop];
            }
        }
    }

    BasicIoModule::doCommmand(MIO_CMD_GETSELECTEDVALUES, 0, &l_param, 2);
    return &m_SelectedValues;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setState(EState_t eState)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSTATE, 0, (SINT32) eState);
}

/**-----------------------------------------------------------------*/
GMP232::EState_t GMP232::getState(VOID)
{
    EState_t eState;
    BasicIoModule::doCommmand(MIO_CMD_GETSTATE, 0, (SINT32) &eState);
    return eState;
}

/**-----------------------------------------------------------------*/
GMP232::SStatistic_t* GMP232::getStatistics(EStatisticId_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) eId;
    l_param[1] = (SINT32) &m_Statistic;

    BasicIoModule::doCommmand(MIO_CMD_GETSTATISTICS, 0, &l_param, 2);
    return &m_Statistic;
}

/**-----------------------------------------------------------------*/
GMP232::SSwitchCount_t* GMP232::getSwitchCount(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSWITCHCOUNT, 0, (SINT32) &m_RelaySwitchCount);
    return &m_RelaySwitchCount;
}

/**-----------------------------------------------------------------*/
GMP232::SValues_t* GMP232::getMeasuredValues(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, 0, (SINT32) &m_Values);
    return &m_Values;
}

/**-----------------------------------------------------------------*/
GMP232::SVectorDiagram_t* GMP232::getVectorDiagram(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETVECTORDIAGRAM, 0, (SINT32) &m_VectorDiagram);
    return &m_VectorDiagram;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setFaultRideThrough(SFaultRideThrough_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETFRT, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GMP232::SFaultRideThrough_t* GMP232::getFaultRideThrough(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETFRT, 0, (SINT32) &m_FaultRideThrough);
    return &m_FaultRideThrough;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setSimulationData(SSimulationData_t* psData)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSIMDATA, 0, (SINT32) psData);
}

/**-----------------------------------------------------------------*/
GMP232::SSimulationData_t* GMP232::getSimulationData(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSIMDATA, 0, (SINT32) &m_SimulationData);
    return &m_SimulationData;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setLimit(ELimitType_t eLimit, SLimit_t* psValue, ELimitId_t eId)
{
    PARAMETERLIST l_param;
    GMP_VECTORJMPLIMIT l_vJmp;
    UINT32 l_ui32Cmd;

    if (eId == eIdUndefined && eTypeVectorJump != eLimit)
    {
        throw MIOexception("GMP232::setLimit: invalid parameter ", m_ui32CardNumber,
        MIO_ER_BADPARM);
    }

    /** prepare Data */
    l_param[0] = (SINT32) psValue;

    if (eTypeVectorJump == eLimit)
    {
        memset(&l_vJmp, 0, sizeof(GMP_VECTORJMPLIMIT));

        l_vJmp.Enabled = psValue->Enabled;
        l_vJmp.Relay = psValue->Relay;
        l_vJmp.ScopeEnabled = psValue->ScopeEnabled;
        l_vJmp.Value = psValue->Value;

        l_param[0] = (SINT32) &l_vJmp;
    }

    l_param[1] = (SINT32) eId;

    /** prepare command */
    l_ui32Cmd = 0;

    switch (eLimit)
    {
        case eTypeUI:
            l_ui32Cmd = MIO_CMD_SETLIMITCFG;
            break;
        case eTypeAsymetric:
            l_ui32Cmd = MIO_CMD_SETASYMLIMIT;
            break;
        case eTypeHarmonics:
            l_ui32Cmd = MIO_CMD_SETHARMONICSLIMIT;
            break;
        case eTypeROCOF:
            l_ui32Cmd = MIO_CMD_SETROCOFLIMIT;
            break;
        case eTypeVectorJump:
            l_ui32Cmd = MIO_CMD_SETVECTORJMPLIMIT;
            break;
        default:
            throw MIOexception("GMP232::setLimit: invalid parameter ", m_ui32CardNumber,
            MIO_ER_BADPARM);
    }

    BasicIoModule::doCommmand(l_ui32Cmd, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
GMP232::SLimit_t* GMP232::getLimit(ELimitType_t eLimit, ELimitId_t eId)
{

    PARAMETERLIST l_param;
    GMP_VECTORJMPLIMIT l_vJmp;
    UINT32 l_ui32Cmd;

    if (eId == eIdUndefined && eTypeVectorJump != eLimit)
    {
        throw MIOexception("GMP232::getLimit: invalid parameter ", m_ui32CardNumber,
        MIO_ER_BADPARM);
    }

    /** prepare Data */
    l_param[0] = (SINT32) &m_ScopeLimit;
    memset(&l_vJmp, 0, sizeof(GMP_VECTORJMPLIMIT));

    if (eTypeVectorJump == eLimit)
    {
        l_param[0] = (SINT32) &l_vJmp;
    }

    l_param[1] = (SINT32) eId;

    /** prepare command */
    l_ui32Cmd = 0;

    switch (eLimit)
    {
        case eTypeUI:
            l_ui32Cmd = MIO_CMD_GETLIMITCFG;
            break;
        case eTypeAsymetric:
            l_ui32Cmd = MIO_CMD_GETASYMLIMIT;
            break;
        case eTypeHarmonics:
            l_ui32Cmd = MIO_CMD_GETHARMONICSLIMIT;
            break;
        case eTypeROCOF:
            l_ui32Cmd = MIO_CMD_GETROCOFLIMIT;
            break;
        case eTypeVectorJump:
            l_ui32Cmd = MIO_CMD_GETVECTORJMPLIMIT;
            break;
        default:
            throw MIOexception("GMP232::getLimit: invalid parameter ", m_ui32CardNumber,
            MIO_ER_BADPARM);
    }

    BasicIoModule::doCommmand(l_ui32Cmd, 0, &l_param, 2);
    if (eTypeVectorJump == eLimit)
    {
        m_ScopeLimit.Enabled = l_vJmp.Enabled;
        m_ScopeLimit.Relay = l_vJmp.Relay;
        m_ScopeLimit.ScopeEnabled = l_vJmp.ScopeEnabled;
        m_ScopeLimit.Value = l_vJmp.Value;
        m_ScopeLimit.Delay = 0;
        m_ScopeLimit.Hysteresis = 0;
    }
    return &m_ScopeLimit;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setFrequencyLimit(SFrequencyLimit_t* psValue, EFrequencLimit_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) psValue;
    l_param[1] = (SINT32) eId;

    BasicIoModule::doCommmand(MIO_CMD_SETFREQUENCYWINDOW, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
GMP232::SFrequencyLimit_t* GMP232::getFrequencyLimit(EFrequencLimit_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) &m_FrequencyLimit;
    l_param[1] = (SINT32) eId;

    BasicIoModule::doCommmand(MIO_CMD_GETFREQUENCYWINDOW, 0, &l_param, 2);
    return &m_FrequencyLimit;
}

/**-----------------------------------------------------------------*/
VOID GMP232::setSampleConfig(SSampleConfig_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSAMPLECFG, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GMP232::SSampleConfig_t* GMP232::getSampleConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSAMPLECFG, 0, (SINT32) &m_SampleConfig);
    return &m_SampleConfig;
}

/**-----------------------------------------------------------------*/
GMP232::SRawDataSamples_t* GMP232::getSamples(VOID)
{
    PARAMETERLIST l_param;
    GMP_SAMPLEREQ l_Request;
    MLOCAL UINT32 l_ui32Count = 0;
    MLOCAL UINT32 l_ui32StartIndex = 0;
    MLOCAL UINT32 l_ui32AvgNoOfData = 0;
    UINT32 l_ui32NoOfNewValues = 0;
    UINT64 l_NewTimeStamp;
    MLOCAL UINT64 l_OldTimeStamp = 0;
    SINT64 l_TempTimeStamp = 0;

    l_Request.StartIdx = l_ui32StartIndex;
    if (l_ui32Count < GMP_RUNBEFOREVALIDDATA)
    {
        l_ui32Count++;
        l_Request.MaxSamples = GMP_MAX_NO_SAMPLES;
    }
    else
    {
        l_Request.MaxSamples = l_ui32AvgNoOfData + GMP_OVERHEAD; // Optimize CPU/Backplane load to minimal usage
        if (l_Request.MaxSamples > GMP_MAX_NO_SAMPLES)
        {
            l_Request.MaxSamples = 0;
        }

    }

    l_param[0] = (SINT32) &l_Request;
    l_param[1] = (SINT32) &m_RawSampleDatas.sSampleData;
    l_param[2] = (SINT32) &l_ui32NoOfNewValues;

    BasicIoModule::doCommmand(MIO_CMD_GETSAMPLES, 0, &l_param, 3);

    l_ui32StartIndex = (l_ui32StartIndex + l_ui32NoOfNewValues) % GMP_MAX_NO_SAMPLES;

    m_RawSampleDatas.ui32Len = l_ui32NoOfNewValues;

    /** Calculate if data is valid/continuous */
    l_NewTimeStamp = m_RawSampleDatas.sSampleData[l_ui32NoOfNewValues - 1].Timestamp;

    l_TempTimeStamp = l_NewTimeStamp - l_OldTimeStamp;
    if (l_TempTimeStamp < 0)
    {
        l_TempTimeStamp = __LONG_LONG_MAX__ - l_OldTimeStamp + l_NewTimeStamp;
    }

    if (l_TempTimeStamp > 3300)
        m_RawSampleDatas.b8DataIsContinuous = FALSE;
    else
        m_RawSampleDatas.b8DataIsContinuous = TRUE;

    l_OldTimeStamp = l_NewTimeStamp;
    /** Calculate average number of return values */
    l_ui32AvgNoOfData = average(l_ui32NoOfNewValues);

    return &m_RawSampleDatas;
}

/**-----------------------------------------------------------------*/
GMP232::SIECValues_t* GMP232::getIecValues(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETIECVALUES, 0, (SINT32) &m_IecValues);
    return &m_IecValues;
}

/**-----------------------------------------------------------------*/
VOID GMP232::attachGmpEvent(EventSession *pSession, BasicEventListener *pListener,
        EGmpEvent_t eEvent, UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, l_ui32Channel, (UINT32) eEvent, pListener);
}

/**-----------------------------------------------------------------*/
VOID GMP232::attachGmpError(ErrorSession *pSession, BasicErrorListener *pListener,
        EGmpError_t eError, UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachError(pSession, l_ui32Channel, (UINT32) eError, pListener);
}

UINT32 GMP232::average(UINT32 newValue)
{
#define ArraySize 10
    MLOCAL BOOL8 l_BufferFull = FALSE;
    MLOCAL UINT32 l_DataArray[ArraySize];
    MLOCAL UINT32 l_DataIndex = ArraySize;
    MLOCAL UINT64 l_Average = 0; /** Total value of all buffer values */

    l_DataIndex++;
    if (l_DataIndex >= ArraySize)
        l_DataIndex = 0;

    l_Average += newValue;
    if (l_BufferFull)
    {
        l_Average -= l_DataArray[l_DataIndex]; /** Calculate total sum of all values in buffer subtract old value out of buffer. */
        l_DataArray[l_DataIndex] = newValue;
        return UINT32(round((REAL32) l_Average / ArraySize));
    }
    else
    {
        l_DataArray[l_DataIndex] = newValue;
        if (ArraySize - 1 == l_DataIndex)
            l_BufferFull = TRUE; /** Use running calculation instead */
        return UINT32(round((REAL64) l_Average / (l_DataIndex + 1)));
    }
}
