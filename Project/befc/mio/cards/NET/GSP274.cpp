/**
 ********************************************************************************
 * @file     GSP274.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid synchronization and protection module GSP274
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "GSP274.hpp"
#include <string.h>

/**
 * contains all possible constants which
 * are needed to read all values
 *
 *
 */
UINT64 GSP274::csa_Selection[] =
{
GSP_VAL_U_L1N_RMS, /** 0 */
GSP_VAL_U_L2N_RMS,
GSP_VAL_U_L3N_RMS,
GSP_VAL_U_L1L2_RMS,
GSP_VAL_U_L2L3_RMS,
GSP_VAL_U_L3L1_RMS,
GSP_VAL_I_L1_RMS,
GSP_VAL_I_L2_RMS,
GSP_VAL_I_L3_RMS,
GSP_VAL_I_N_RMS,
GSP_VAL_P_SUM, /** 10 */
GSP_VAL_P_L1,
GSP_VAL_P_L2,
GSP_VAL_P_L3,
GSP_VAL_S_SUM,
GSP_VAL_S_L1,
GSP_VAL_S_L2,
GSP_VAL_S_L3,
GSP_VAL_Q_SUM,
GSP_VAL_Q_L1,
GSP_VAL_Q_L2, /** 20 */
GSP_VAL_Q_L3,
GSP_VAL_FREQUENCY,
GSP_VAL_ROCOF,
GSP_VAL_ASYM_U,
GSP_VAL_ASYM_I,
GSP_VAL_I_RMS, /** 26 */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 40 */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 50 */
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /** 60 */
0, 0, 0 /** 63 */
};

/**-----------------------------------------------------------------*/
GSP274::GSP274() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GSP274::GSP274(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();

    init();

    for (UINT32 i = 0; i < 4; ++i)
    {
        m_Output[i].setParentModule(this);
        m_Output[i].setChannelNumber(17 + i);

        m_Input[i].setParentModule(this);
        m_Input[i].setChannelNumber(21 + i);
    }

}

/**-----------------------------------------------------------------*/
GSP274::~GSP274()
{

}

/**-----------------------------------------------------------------*/
VOID GSP274::init(VOID)
{
    memset(&m_Limit, 0, sizeof(m_Limit));
    memset(&m_Energy, 0, sizeof(m_Energy));
    memset(&m_QuLimit, 0, sizeof(m_QuLimit));
    memset(&m_ScopeLock, 0, sizeof(m_ScopeLock));
    memset(&m_IECValues, 0, sizeof(m_IECValues));
    memset(&m_Statistic, 0, sizeof(m_Statistic));
    memset(&m_Harmonics, 0, sizeof(m_Harmonics));
    memset(&m_ScopeData, 0, sizeof(m_ScopeData));
    memset(&m_BaseConfig, 0, sizeof(m_BaseConfig));
    memset(&m_ScopeState, 0, sizeof(m_ScopeState));
    memset(&m_HistoryLock, 0, sizeof(m_HistoryLock));
    memset(&m_SwitchCount, 0, sizeof(m_SwitchCount));
    memset(&m_PhaseAngles, 0, sizeof(m_PhaseAngles));
    memset(&m_ScopeConfig, 0, sizeof(m_ScopeConfig));
    memset(&m_VectorDiagram, 0, sizeof(m_VectorDiagram));
    memset(&m_SimulationData, 0, sizeof(m_SimulationData));
    memset(&m_FrequencyLimit, 0, sizeof(m_FrequencyLimit));
    memset(&m_MeasuredValues, 0, sizeof(m_MeasuredValues));
    memset(&m_SelectedValues, 0, sizeof(m_SelectedValues));
    memset(&m_ExportProgress, 0, sizeof(m_ExportProgress));
    memset(&m_FaultRideThroughCfg, 0, sizeof(m_FaultRideThroughCfg));
}

/**-----------------------------------------------------------------*/
DigitalChannel* GSP274::getDigitalChannel(UINT32 ui32Channel)
{

    /**
     * only 10 and 11 possible
     */
    if (10 == ui32Channel || 11 == ui32Channel)
    {
        return &m_Output[ui32Channel - 10];
    }
    else
    {
        throw MIOexception("GSP274::getDigitalChannel: invalid parameter ", m_ui32CardNumber,
        MIO_ER_BADPARM);
    }
}

/**-----------------------------------------------------------------*/
VOID GSP274::deleteHistory(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_DELETEALARMHISTORY, 0);
}

/**-----------------------------------------------------------------*/
GSP274::SDisplayStatistics_t* GSP274::displayStatistics(UINT32 ui32Index, UINT32 ui32Count, SDisplayStatistics_t* pStat)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Index;
    l_param[1] = (SINT32) ui32Count;
    l_param[2] = (SINT32) pStat;

    BasicIoModule::doCommmand(MIO_CMD_DISPSTATISTICS, 0, &l_param, 3);

    return pStat;
}

/**-----------------------------------------------------------------*/
VOID GSP274::resetStatistics(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_RESETSTATISTICS, 0);
}

/**-----------------------------------------------------------------*/
VOID GSP274::exportScope(CHAR8* pch8Filename, UINT32 ui32Timeout, UINT32 ui8Channel)
{
    PARAMETERLIST l_param;

    takeScopeLock(ui32Timeout, ui8Channel);

    l_param[0] = (SINT32) m_ScopeLock;
    l_param[1] = (SINT32) pch8Filename;
    l_param[2] = 0; /** Flags (can be ignored) */

	BasicIoModule::doCommmand(MIO_CMD_EXPORTSCOPE, ui8Channel, &l_param, 3);
	// Scope lock released by getExportScopeProgress
	giveScopeLock(ui8Channel);
}

/**-----------------------------------------------------------------*/
VOID GSP274::exportScopeNB(CHAR8* pch8Filename, UINT32 ui32Timeout, UINT32 ui8Channel)
{
    PARAMETERLIST l_param;

    takeScopeLock(ui32Timeout, ui8Channel);

    l_param[0] = (SINT32) m_ScopeLock;
    l_param[1] = (SINT32) pch8Filename;
    l_param[2] = 0; /** Flags (can be ignored) */

	BasicIoModule::doCommmand(MIO_CMD_EXPORTSCOPEINTASK, ui8Channel, &l_param, 3);
	// Scope lock released by getExportScopeProgress
}

/**-----------------------------------------------------------------*/
VOID GSP274::processIniFile(CHAR8 pch8Filename)
{
    BasicIoModule::doCommmand(MIO_CMD_PROCESSINIFILE, 0, (SINT32) pch8Filename);
}

/**-----------------------------------------------------------------*/
VOID GSP274::forceRelay(UINT8 ui8Channel, BOOL8 b8Value)
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
VOID GSP274::resetRelay(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_RESETRELAY, l_ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID GSP274::takeHistoryLock(UINT32 ui32Timeout)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Timeout;
    l_param[1] = (SINT32) &m_HistoryLock;

    BasicIoModule::doCommmand(MIO_CMD_TAKEHISTORYLOCK, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
VOID GSP274::giveHistoryLock(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GIVEHISTORYLOCK, 0, (SINT32) m_HistoryLock);
}

/**-----------------------------------------------------------------*/
VOID GSP274::takeScopeLock(UINT32 ui32Timeout, UINT32 ui8Channel)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) ui32Timeout;
    l_param[1] = (SINT32) &m_ScopeLock;

    BasicIoModule::doCommmand(MIO_CMD_TAKESCOPELOCK, ui8Channel, &l_param, 2);
}

/**-----------------------------------------------------------------*/
VOID GSP274::giveScopeLock(UINT32 ui8Channel)
{

    BasicIoModule::doCommmand(MIO_CMD_GIVESCOPELOCK, ui8Channel, (SINT32) m_ScopeLock);
}

MIO_PROGRESS_R* GSP274::getExportScopeProgress(UINT32 ui8Channel)
{
    BasicIoModule::doCommmand(MIO_CMD_GETPROGRESS,
    						  ui8Channel,
                              (SINT32)&m_ExportProgress);
    if (m_ExportProgress.Status == PROGRESS_DONE)
    {
    	giveScopeLock(ui8Channel);
    }
    return &m_ExportProgress;
}

/**-----------------------------------------------------------------*/
VOID GSP274::triggerScope(UINT32 ui8Channel)
{
    BasicIoModule::doCommmand(MIO_CMD_TRIGGERSCOPE, ui8Channel);
}

/**-----------------------------------------------------------------*/
VOID GSP274::getAlarmHistory(UINT32 ui32Index, UINT32 ui32Count, UINT32 ui32Timeout,
        SAlarmHistory_t* pValue)
{
    PARAMETERLIST l_param;

    takeHistoryLock(ui32Timeout);

    l_param[0] = (SINT32) m_HistoryLock;
    l_param[1] = (SINT32) ui32Index;
    l_param[2] = (SINT32) ui32Count;
    l_param[3] = (SINT32) pValue;

    BasicIoModule::doCommmand(MIO_CMD_GETALARMHISTORY, 0, &l_param, 4);
    giveHistoryLock();
}

/**-----------------------------------------------------------------*/
VOID GSP274::setEnergy(SEnergyR_t* pValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETENERGYREAL, 0, (SINT32) pValue);
}

/**-----------------------------------------------------------------*/
GSP274::SEnergyR_t* GSP274::getEnergy(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETENERGYREAL, 0, (SINT32) &m_Energy);
    return &m_Energy;
}

/**-----------------------------------------------------------------*/
GSP274::EEvent_t GSP274::getEvent(UINT8 ui8Channel)
{
    EEvent_t l_eEvent;
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETEVENT, l_ui32Channel, (SINT32) &l_eEvent);
    return l_eEvent;
}

/**-----------------------------------------------------------------*/
GSP274::SHarmonics_t* GSP274::getHarmonics(EHarmonicsId_t id)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) id;
    l_param[1] = (SINT32) &m_Harmonics;

    BasicIoModule::doCommmand(MIO_CMD_GETHARMONICS, 0, &l_param, 2);
    return &m_Harmonics;
}

/**-----------------------------------------------------------------*/
UINT32 GSP274::getStatisticsCounter(VOID)
{
    UINT32 l_ui32StatisticsCounter;

    BasicIoModule::doCommmand(MIO_CMD_GETNBSTATISTICS, 0, (SINT32) &l_ui32StatisticsCounter);
    return l_ui32StatisticsCounter;
}

/**-----------------------------------------------------------------*/
GSP274::SPhaseAngels_t* GSP274::getPhaseAngles(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETPHASEANGLES, 0, (SINT32) &m_PhaseAngles);
    return &m_PhaseAngles;
}

/**-----------------------------------------------------------------*/
UINT32 GSP274::getPreInitErrors(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32PreInitErrors = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPREINITERROR, l_ui32Channel,
            (SINT32) &l_ui32PreInitErrors);

    return l_ui32PreInitErrors;
}

/**-----------------------------------------------------------------*/
UINT32 GSP274::getPreInitEvents(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32PreInitEvents = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETPREINITEVENT, l_ui32Channel,
            (SINT32) &l_ui32PreInitEvents);

    return l_ui32PreInitEvents;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setQULimit(SQuLimit_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_GETQULIMIT, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GSP274::SQuLimit_t* GSP274::getQULimit(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_SETQULIMIT, 0, (SINT32) &m_QuLimit);

    return &m_QuLimit;
}

/**-----------------------------------------------------------------*/
GSP274::SBaseConfig_t* GSP274::getBaseConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETCONFIG, 0, (SINT32) &m_BaseConfig);
    return &m_BaseConfig;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setRelayConfig(ERelayConfig_t eValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETRELAYCFG, 0, (SINT32) eValue);
}

/**-----------------------------------------------------------------*/
GSP274::ERelayConfig_t GSP274::getRelayConfig(VOID)
{
    ERelayConfig_t eRelayConfig;

    BasicIoModule::doCommmand(MIO_CMD_GETRELAYCFG, 0, (SINT32) &eRelayConfig);
    return eRelayConfig;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setScopeConfig(SScopeConfig_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSCOPECFG, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GSP274::SScopeConfig_t* GSP274::getScopeConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSCOPECFG, 0, (SINT32) &m_ScopeConfig);
    return &m_ScopeConfig;
}

/**-----------------------------------------------------------------*/
UINT32 GSP274::getRunThroughConfig(VOID)
{
    UINT32 l_ui32RunThroughConfig;

    BasicIoModule::doCommmand(MIO_CMD_GETRUNTHROUGH, 0, (SINT32) &l_ui32RunThroughConfig);
    return l_ui32RunThroughConfig;
}

/**-----------------------------------------------------------------*/
GSP274::SScopeData_t* GSP274::getScopeValues(UINT32 ui32Index, UINT32 ui32Timeout, UINT32 ui8Channel)
{
    PARAMETERLIST l_param;
    if(ui32Index == 0)
    {
		takeScopeLock(ui32Timeout, ui8Channel);
    }

    l_param[0] = (SINT32) m_ScopeLock;
    l_param[1] = (SINT32) &m_ScopeData;
    l_param[2] = (SINT32) ui32Index;

    BasicIoModule::doCommmand(MIO_CMD_GETSCOPE, ui8Channel, &l_param, 3);
    if(ui32Index == GSP_SCOPE_MAXVALIDX)
    {
    	giveScopeLock(ui8Channel);
    }

    return &m_ScopeData;
}

/**-----------------------------------------------------------------*/
GSP274::SScopeState_t* GSP274::getScopeState(UINT32 ui8Channel)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSCOPESTATE, ui8Channel, (SINT32) &m_ScopeState);
    return &m_ScopeState;
}

/**-----------------------------------------------------------------*/
GSP274::SValues_t* GSP274::getSelectedValues(ASelection_t *paSelection)
{
    PARAMETERLIST l_param;
    UINT64 l_ui64Selection = 0LL;

    l_param[0] = (SINT32) &m_SelectedValues;
    l_param[1] = (SINT32) &l_ui64Selection;

    /** loop through Bitmask an map */
    for (int iLoop = 0; iLoop < (int) eSlctALL; ++iLoop)
    {
        if (TRUE == (*paSelection)[iLoop])
        {
            l_ui64Selection = l_ui64Selection | GSP274::csa_Selection[iLoop];
        }
    }

    BasicIoModule::doCommmand(MIO_CMD_GETSELECTEDVALUES, 0, &l_param, 2);
    return &m_SelectedValues;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setState(EState_t eState)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSTATE, 0, (SINT32) eState);
}

/**-----------------------------------------------------------------*/
GSP274::EState_t GSP274::getState(VOID)
{
    EState_t eState;
    BasicIoModule::doCommmand(MIO_CMD_GETSTATE, 0, (SINT32) &eState);
    return eState;
}

/**-----------------------------------------------------------------*/
GSP274::SStatistic_t* GSP274::getStatistics(EStatisticId_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) eId;
    l_param[1] = (SINT32) &m_Statistic;

    BasicIoModule::doCommmand(MIO_CMD_GETSTATISTICS, 0, &l_param, 2);
    return &m_Statistic;
}

/**-----------------------------------------------------------------*/
GSP274::SSwitchCount_t* GSP274::getSwitchCount(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSWITCHCOUNT, 0, (SINT32) &m_SwitchCount);
    return &m_SwitchCount;
}

/**-----------------------------------------------------------------*/
GSP274::SValues_t* GSP274::getMeasuredValues(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, 0, (SINT32) &m_MeasuredValues);
    return &m_MeasuredValues;
}

/**-----------------------------------------------------------------*/
GSP274::SVectorDiagram_t* GSP274::getVectorDiagram(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETVECTORDIAGRAM, 0, (SINT32) &m_VectorDiagram);
    return &m_VectorDiagram;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setFaultRideThrough(SFaultRideThrough_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETFRT, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GSP274::SFaultRideThrough_t* GSP274::getFaultRideThrough(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETFRT, 0, (SINT32) &m_FaultRideThroughCfg);
    return &m_FaultRideThroughCfg;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setSimulationData(SSimulationData_t* psData)
{
    BasicIoModule::doCommmand(MIO_CMD_SETSIMDATA, 0, (SINT32) psData);
}

/**-----------------------------------------------------------------*/
GSP274::SSimulationData_t* GSP274::getSimulationData(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETSIMDATA, 0, (SINT32) &m_SimulationData);
    return &m_SimulationData;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setLimit(ELimitType_t eLimit, SLimit_t* psValue, ELimitId_t eId)
{
    PARAMETERLIST l_param;
    GSP_VECTORJMPLIMIT l_vJmp;
    UINT32 l_ui32Cmd;

    if (eId == eIdUndefined && eTypeVectorJump != eLimit)
    {
        throw MIOexception("GSP274::setLimit: invalid parameter ", m_ui32CardNumber,
        MIO_ER_BADPARM);
    }

    /** prepare Data */
    l_param[0] = (SINT32) psValue;

    if (eTypeVectorJump == eLimit)
    {
        memset(&l_vJmp, 0, sizeof(GSP_VECTORJMPLIMIT));

        l_vJmp.Alarm = psValue->Alarm;
        l_vJmp.Enabled = psValue->Enabled;
        l_vJmp.Breaker = psValue->Breaker;
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
            throw MIOexception("GSP274::setLimit: invalid parameter ", m_ui32CardNumber,
            MIO_ER_BADPARM);
    }

    BasicIoModule::doCommmand(l_ui32Cmd, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
GSP274::SLimit_t* GSP274::getLimit(ELimitType_t eLimit, ELimitId_t eId)
{
    PARAMETERLIST l_param;
    GSP_VECTORJMPLIMIT l_vJmp;
    UINT32 l_ui32Cmd;

    memset(&l_vJmp, 0, sizeof(GSP_VECTORJMPLIMIT));

    if (eId == eIdUndefined && eTypeVectorJump != eLimit)
    {
        return FALSE;
    }

    /** prepare Data */
    l_param[0] = (SINT32) &m_Limit;

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
            return FALSE;
    }

    BasicIoModule::doCommmand(l_ui32Cmd, 0, &l_param, 2);

    if (eTypeVectorJump == eLimit)
    {
        m_Limit.Alarm = l_vJmp.Alarm;
        m_Limit.Enabled = l_vJmp.Enabled;
        m_Limit.Breaker = l_vJmp.Breaker;
        m_Limit.ScopeEnabled = l_vJmp.ScopeEnabled;
        m_Limit.Value = l_vJmp.Value;
        m_Limit.Delay = 0;
        m_Limit.Hysteresis = 0;
    }

    return &m_Limit;
}

/**-----------------------------------------------------------------*/
VOID GSP274::setFrequencyLimit(SFrequencyLimit_t* psValue, EFrequencLimit_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) psValue;
    l_param[1] = (SINT32) eId;

    BasicIoModule::doCommmand(MIO_CMD_SETFREQUENCYWINDOW, 0, &l_param, 2);
}

/**-----------------------------------------------------------------*/
GSP274::SFrequencyLimit_t* GSP274::getFrequencyLimit(EFrequencLimit_t eId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32) &m_FrequencyLimit;
    l_param[1] = (SINT32) eId;

    BasicIoModule::doCommmand(MIO_CMD_GETFREQUENCYWINDOW, 0, &l_param, 2);
    return &m_FrequencyLimit;
}

/**-----------------------------------------------------------------*/
GSP274::SIECValues_t* GSP274::getIecValues(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETIECVALUES, 0, (SINT32) &m_IECValues);
    return &m_IECValues;
}

/**-----------------------------------------------------------------*/
VOID GSP274::attachEvent(EventSession *pSession, BasicEventListener *pListener, EEvent_t eEvent,
        UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachEvent(pSession, l_ui32Channel, (UINT32) eEvent, pListener);
}

/**-----------------------------------------------------------------*/
VOID GSP274::attachError(ErrorSession *pSession, BasicErrorListener *pListener, EGspError_t eError,
        UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::attachError(pSession, l_ui32Channel, (UINT32) eError, pListener);
}

