/**
 ********************************************************************************
 * @file     GMP232x.cpp
 * @author   Søren Vejlgaard Vedstesen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Sep 17, 2015 10:38:48 $
 *
 * @brief    Implementation of grid measurement and protection module GMP232x
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#include "GMP232x.hpp"
#include <cstring>

/**-----------------------------------------------------------------*/
GMP232x::GMP232x()
    : BasicMixedModule()
{
	/** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GMP232x::GMP232x(UINT32 ui32CardNumber)
    : BasicMixedModule(ui32CardNumber, true)
{
	/** Check card type */
    checkCardType();

    init();

    m_Output[0].setParentModule(this);
    m_Output[1].setParentModule(this);
    m_Output[0].setChannelNumber(12);
    m_Output[1].setChannelNumber(13);

}

/**-----------------------------------------------------------------*/
GMP232x::GMP232x(UINT32 ui32CardNumber, MIOSystem *pMIOSystem)
    : BasicMixedModule(ui32CardNumber, pMIOSystem, true)
{
    /** Check card type */
    checkCardType();

    init();

    m_Output[0].setParentModule(this);
    m_Output[1].setParentModule(this);
    m_Output[0].setChannelNumber(12);
    m_Output[1].setChannelNumber(13);

}

/**-----------------------------------------------------------------*/
GMP232x::~GMP232x()
{
}

/**-----------------------------------------------------------------*/
VOID GMP232x::init(VOID)
{
	m_OldTimeStamp = 0;
	m_ui32StartIndex = 0;
	m_Asym = (GMP232X_ASYM){0};
	memset(&m_Asym, 0, sizeof(m_Asym));
	memset(&m_Phase, 0, sizeof(m_Phase));
	memset(&m_NegSys, 0, sizeof(m_NegSys));
	memset(&m_SimData, 0, sizeof(m_SimData));
	memset(&m_QuLimit, 0, sizeof(m_QuLimit));
	memset(&m_MeanCfg, 0, sizeof(m_MeanCfg));
	memset(&m_Frms_Fcs, 0, sizeof(m_Frms_Fcs));
	memset(&m_Trms_Hcs, 0, sizeof(m_Trms_Hcs));
	memset(&m_Frms_Fcc, 0, sizeof(m_Frms_Fcc));
	memset(&m_Trms_Hcc, 0, sizeof(m_Trms_Hcc));
	memset(&m_PhaseRef, 0, sizeof(m_PhaseRef));
	memset(&m_moduleCfg, 0, sizeof(m_moduleCfg));
	memset(&m_Hammonics, 0, sizeof(m_Hammonics));
	memset(&m_FreqLimit, 0, sizeof(m_FreqLimit));
	memset(&m_VfrtLimit, 0, sizeof(m_VfrtLimit));
	memset(&m_FfrtLimit, 0, sizeof(m_FfrtLimit));
	memset(&m_MeanValue, 0, sizeof(m_MeanValue));
	memset(&m_SampleCfg, 0, sizeof(m_SampleCfg));
	memset(&m_ModuleTime, 0, sizeof(m_ModuleTime));
	memset(&m_EnergyData, 0, sizeof(m_EnergyData));
	memset(&m_InhibitCfg, 0, sizeof(m_InhibitCfg));
	memset(&m_Phase_UI_S, 0, sizeof(m_Phase_UI_S));
	memset(&m_RocofLimit, 0, sizeof(m_RocofLimit));
	memset(&m_ScopeState, 0, sizeof(m_ScopeState));
	memset(&m_LimitStatus, 0, sizeof(m_LimitStatus));
	memset(&m_HistoryData, 0, sizeof(m_HistoryData));
	memset(&m_ModuleState, 0, sizeof(m_ModuleState));
	memset(&m_RocofRotDir, 0, sizeof(m_RocofRotDir));
	memset(&m_ScopeConfig, 0, sizeof(m_ScopeConfig));
	memset(&m_ThdTddLimit, 0, sizeof(m_ThdTddLimit));
	memset(&m_PowerFactor, 0, sizeof(m_PowerFactor));
	memset(&m_ExtendedCfg, 0, sizeof(m_ExtendedCfg));
	memset(&m_checkSumPart, 0, sizeof(m_checkSumPart));
	memset(&m_GetScopeData, 0, sizeof(m_GetScopeData));
	memset(&m_VoltageLimit, 0, sizeof(m_VoltageLimit));
	memset(&m_CurrentLimit, 0, sizeof(m_CurrentLimit));
	memset(&m_LimitRelayCfg, 0, sizeof(m_LimitRelayCfg));
	memset(&m_LimitScopeCfg, 0, sizeof(m_LimitScopeCfg));
	memset(&m_SymComponents, 0, sizeof(m_SymComponents));
	memset(&m_MaxPowerLimit, 0, sizeof(m_MaxPowerLimit));
	memset(&m_HarmonicLimit, 0, sizeof(m_HarmonicLimit));
	memset(&m_PowerFrms_Fcs, 0, sizeof(m_PowerFrms_Fcs));
	memset(&m_PowerFrms_Fcc, 0, sizeof(m_PowerFrms_Fcc));
	memset(&m_PowerTrms_Hcs, 0, sizeof(m_PowerTrms_Hcs));
	memset(&m_PowerTrms_Hcc, 0, sizeof(m_PowerTrms_Hcc));
	memset(&m_StatisticPoint, 0, sizeof(m_StatisticPoint));
	memset(&m_THD_TDD_Values, 0, sizeof(m_THD_TDD_Values));
	memset(&m_StatisticsData, 0, sizeof(m_StatisticsData));
	memset(&m_ExportProgress, 0, sizeof(m_ExportProgress));
	memset(&m_RawSampleDatas, 0, sizeof(m_RawSampleDatas));
	memset(&m_AsymmetryLimit, 0, sizeof(m_AsymmetryLimit));
	memset(&m_LastSampleData, 0, sizeof(m_LastSampleData));
	memset(&m_FRMS_FCS_Values, 0, sizeof(m_FRMS_FCS_Values));
	memset(&m_FRMS_FCC_Values, 0, sizeof(m_FRMS_FCC_Values));
	memset(&m_TRMS_HCC_Values, 0, sizeof(m_TRMS_HCC_Values));
	memset(&m_VectorJumpLimit, 0, sizeof(m_VectorJumpLimit));
	memset(&m_ScopeLockHandle, 0, sizeof(m_ScopeLockHandle));
	memset(&m_RelaySwitchCount, 0, sizeof(m_RelaySwitchCount));
	memset(&m_HistoryLockHandle, 0, sizeof(m_HistoryLockHandle));
	memset(&m_SymComponentsBulk, 0, sizeof(m_SymComponentsBulk));
	memset(&m_ReversePowerLimit, 0, sizeof(m_ReversePowerLimit));
	memset(&m_CurrentDirectionLimit, 0, sizeof(m_CurrentDirectionLimit));
}
VOID GMP232x::attachGmpEvent(EventSession *pSession,
                             BasicEventListener *pListener,
                             EGMPxEvent_t eEvent,
                             UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::attachEvent(pSession,
                               l_ui32Channel,
                               (UINT32)eEvent,
                               pListener);
}

/**-----------------------------------------------------------------*/
VOID GMP232x::attachGmpError(ErrorSession *pSession,
                          BasicErrorListener *pListener,
                          EGMPxError_t eError,
                          UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32)ui8Channel;

    BasicIoModule::attachError(pSession,
                               l_ui32Channel,
                               (UINT32)eError,
                               pListener);
}

timespec* GMP232x::getModuleTime(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMODULETIME,
                              0,
                              (SINT32)&m_ModuleTime);

	return &m_ModuleTime;
}

VOID GMP232x::setModuleTime(timespec *Time)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETMODULETIME,
                              0,
                              (SINT32)Time);
}

VOID GMP232x::processParameterFile(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_PROCESSPARAMFILE,0);
}

BOOL32 GMP232x::getRunThrough(VOID)
{
    BOOL32	RunThrough;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETRUNTHROUGH, 0, (SINT32)&RunThrough);

	return RunThrough;
}

VOID GMP232x::setRunThrough(BOOL32 RunThrough)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETRUNTHROUGH, 0, RunThrough);
}

UINT32 GMP232x::getEventsStatus(VOID)
{
    UINT32	EventsStatus;
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETEVENT, 0, (SINT32)&EventsStatus);

	return EventsStatus;
}

VOID GMP232x::setFrequencyLimit(GMP232X_LIMIT_FREQ *freqLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)freqLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_FREQ,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_FREQ* GMP232x::getFrequencyLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_FreqLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_FREQ,
                              0,
                              &l_param,
                              2);
    return &m_FreqLimit;
}

VOID GMP232x::setVfrtLimit(GMP232X_LIMIT_VFRT *VfrtLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)VfrtLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_VFRT,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_VFRT* GMP232x::getVfrtLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_VfrtLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_VFRT,
                              0,
                              &l_param,
                              2);
    return &m_VfrtLimit;
}

VOID GMP232x::setFfrtLimit(GMP232X_LIMIT_FFRT *FfrtLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)FfrtLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_FFRT,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_FFRT* GMP232x::getFfrtLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_FfrtLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_FFRT,
                              0,
                              &l_param,
                              2);
    return &m_FfrtLimit;
}

VOID GMP232x::setVoltageLimit(GMP232X_LIMIT_V *VoltageLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)VoltageLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_VOLTAGE,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_V* GMP232x::getVoltageLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_VoltageLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_VOLTAGE,
                              0,
                              &l_param,
                              2);
    return &m_VoltageLimit;
}

VOID GMP232x::setQULimit(GMP232X_LIMIT_QU *QULimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)QULimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_QU,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_QU* GMP232x::getQULimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_QuLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_QU,
                              0,
                              &l_param,
                              2);
    return &m_QuLimit;
}

VOID GMP232x::setVectorJumpLimit(GMP232X_LIMIT_VECTORJUMP *VectorJumpLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)VectorJumpLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_VECTORJUMP,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_VECTORJUMP* GMP232x::getVectorJumpLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_VectorJumpLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_VECTORJUMP,
                              0,
                              &l_param,
                              2);
    return &m_VectorJumpLimit;
}

VOID GMP232x::setHarmonicLimit(GMP232X_LIMIT_HARMONICS *HarmonicLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)HarmonicLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_HARMONICS,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_HARMONICS* GMP232x::getHarmonicLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_HarmonicLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_HARMONICS,
                              0,
                              &l_param,
                              2);
    return &m_HarmonicLimit;
}

VOID GMP232x::setCurrentLimit(GMP232X_LIMIT_I *CurrentLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)CurrentLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_I,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_I* GMP232x::getCurrentLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_CurrentLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_I,
                              0,
                              &l_param,
                              2);
    return &m_CurrentLimit;
}

VOID GMP232x::setThdTddLimit(GMP232X_LIMIT_THDTDD *ThdTddLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)ThdTddLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_THDTDD,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_THDTDD* GMP232x::getThdTddLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_ThdTddLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_THDTDD,
                              0,
                              &l_param,
                              2);
    return &m_ThdTddLimit;
}

VOID GMP232x::setAsymmetryLimit(GMP232X_LIMIT_ASYM *AsymmetryLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)AsymmetryLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_ASYM,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_ASYM* GMP232x::getAsymmetryLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_AsymmetryLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_ASYM,
                              0,
                              &l_param,
                              2);
    return &m_AsymmetryLimit;
}

VOID GMP232x::setRocofLimit(GMP232X_LIMIT_ROCOF *RocofLimit)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)RocofLimit;
    l_param[1] = MIO_CMD_GMP232X_SETLIMIT_ROCOF;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_ROCOF,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_ROCOF* GMP232x::getRocofLimit(VOID)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_RocofLimit;
    l_param[1] = MIO_CMD_GMP232X_SETLIMIT_ROCOF;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_ROCOF,
                              0,
                              &l_param,
                              2);
    return &m_RocofLimit;
}

VOID GMP232x::setMaxPowerLimit(GMP232X_LIMIT_MAX_POWER *MaxPowerLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)MaxPowerLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_MAX_POWER,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_MAX_POWER* GMP232x::getMaxPowerLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_MaxPowerLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_MAX_POWER,
                              0,
                              &l_param,
                              2);
    return &m_MaxPowerLimit;
}

VOID GMP232x::setReversePowerLimit(GMP232X_LIMIT_REVERSE_POWER *ReversePowerLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)ReversePowerLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_REVERSE_POWER,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_REVERSE_POWER* GMP232x::getReversePowerLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_ReversePowerLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_REVERSE_POWER,
                              0,
                              &l_param,
                              2);
    return &m_ReversePowerLimit;
}

VOID GMP232x::setCurrentDirectionLimit(GMP232X_LIMIT_DIR_CURRENT *CurrentDirectionLimit, UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)CurrentDirectionLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_DIR_CURRENT,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_DIR_CURRENT* GMP232x::getCurrentDirectionLimit(UINT32 limitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&m_CurrentDirectionLimit;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_DIR_CURRENT,
                              0,
                              &l_param,
                              2);
    return &m_CurrentDirectionLimit;
}


UINT32 GMP232x::getLimitStatus(UINT32 limitId)
{
	UINT32 LimitStatus;
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)&LimitStatus;
    l_param[1] = limitId;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_STATUS,
                              0,
                              &l_param,
                              2);
    return LimitStatus;
}

GMP232X_FRMS_FCS_VALUES* GMP232x::getFrms_Fcs(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GET_FRMS_FCS,
                              0,
                              (SINT32)&m_Frms_Fcs);
    return &m_Frms_Fcs;
}

GMP232X_TRMS_HCS_VALUES* GMP232x::getTrms_Hcs(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GET_TRMS_HCS,
                              0,
                              (SINT32)&m_Trms_Hcs);
    return &m_Trms_Hcs;
}

GMP232X_FRMS_FCC_VALUES* GMP232x::getFrms_Fcc(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GET_FRMS_FCC,
                              0,
                              (SINT32)&m_Frms_Fcc);
    return &m_Frms_Fcc;
}

GMP232X_TRMS_HCC_VALUES* GMP232x::getTrms_Hcc(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GET_TRMS_HCC,
                              0,
                              (SINT32)&m_Trms_Hcc);
    return &m_Trms_Hcc;
}

GMP232X_POWERS_FRMS_FCS* GMP232x::getPowerFrms_Fcs(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPOWERS_FRMS_FCS,
                              0,
                              (SINT32)&m_PowerFrms_Fcs);
    return &m_PowerFrms_Fcs;
}

GMP232X_POWERS_FRMS_FCC* GMP232x::getPowerFrms_Fcc(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPOWERS_FRMS_FCC,
                              0,
                              (SINT32)&m_PowerFrms_Fcc);
    return &m_PowerFrms_Fcc;
}

GMP232X_POWERS_TRMS_HCS* GMP232x::getPowerTrms_Hcs(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPOWERS_TRMS_HCS,
                              0,
                              (SINT32)&m_PowerTrms_Hcs);
    return &m_PowerTrms_Hcs;
}

GMP232X_POWERS_TRMS_HCC* GMP232x::getPowerTrms_Hcc(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPOWERS_TRMS_HCC,
                              0,
                              (SINT32)&m_PowerTrms_Hcc);
    return &m_PowerTrms_Hcc;
}

GMP232X_PHASEREF* GMP232x::getPhaseReferance(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPHASE_REF,
                              0,
                              (SINT32)&m_PhaseRef);
    return &m_PhaseRef;
}

GMP232X_PHASE* GMP232x::getPhase(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPHASE,
                              0,
                              (SINT32)&m_Phase);
    return &m_Phase;
}

GMP232X_ROCOF_ROTDIR* GMP232x::getRocofRotDir(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETROCOF_ROTDIR,
                              0,
                              (SINT32)&m_RocofRotDir);
    return &m_RocofRotDir;
}

GMP232X_POWERFACTOR* GMP232x::getPowerFactor(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPOWERFACTOR,
                              0,
                              (SINT32)&m_PowerFactor);
    return &m_PowerFactor;
}

GMP232X_ASYM* GMP232x::getAsym(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETASYM,
                              0,
                              (SINT32)&m_Asym);
    return &m_Asym;
}

GMP232X_SYMCOMPONENTS* GMP232x::getSymComponents(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSYM_COMPONENTS,
                              0,
                              (SINT32)&m_SymComponents);
    return &m_SymComponents;
}

VOID GMP232x::setEnergy(GMP232X_ENERGY* energyData, UINT32 SourceSelect)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)energyData;
    l_param[1] = SourceSelect;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETENERGY,
                              0,
                              &l_param,
                              2);
}

GMP232X_ENERGY* GMP232x::getEnergy(UINT32 SourceSelect)
{
    PARAMETERLIST l_param;

    l_param[0] = SourceSelect;
    l_param[1] = (SINT32)&m_EnergyData;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETENERGY,
                              0,
                              &l_param,
                              2);
    return &m_EnergyData;
}

VOID GMP232x::setScopeConfig(GMP232X_SCOPE_CONFIG* ScopeCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETSCOPECFG,
                              0,
                              (SINT32)ScopeCfg);
}

GMP232X_SCOPE_CONFIG* GMP232x::getScopeConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSCOPECFG,
                              0,
                              (SINT32)&m_ScopeConfig);
    return &m_ScopeConfig;
}


BOOL8 GMP232x::TakeScopeLock(UINT32 LockTimeout)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)LockTimeout;
    l_param[1] = (SINT32)&m_ScopeLockHandle;

	try
	{
		BasicIoModule::doCommmand(MIO_CMD_GMP232X_TAKESCOPELOCK,
								  0,
								  &l_param,
								  2);
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

VOID GMP232x::GiveScopeLock(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GIVESCOPELOCK,
                              0,
                              (SINT32)m_ScopeLockHandle);
}

VOID GMP232x::TriggerScope(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_TRIGGERSCOPE, 0);
}

VOID GMP232x::exportScopeNB(CHAR8* pch8Filename)
{
    PARAMETERLIST l_param;

    if (TakeScopeLock(GMP_SCOPELOCKTIMEOUT))
    {
		l_param[0] = (SINT32)m_ScopeLockHandle;
		l_param[1] = (SINT32)pch8Filename;
		l_param[2] = 0;     /** Flags (can be ignored) */
		/** Export in Backgroundtask */
		BasicIoModule::doCommmand(MIO_CMD_GMP232X_EXPORTSCOPEINTASK,
								  0,
								  &l_param,
								  3);
    }
}

VOID GMP232x::exportScope(CHAR8* pch8Filename)
{
    PARAMETERLIST l_param;

    if (TakeScopeLock(GMP_SCOPELOCKTIMEOUT))
    {
		l_param[0] = (SINT32)m_ScopeLockHandle;
		l_param[1] = (SINT32)pch8Filename;
		l_param[2] = 0;     /** Flags (can be ignored) */
		BasicIoModule::doCommmand(MIO_CMD_GMP232X_EXPORTSCOPE,
								  0,
								  &l_param,
								  3);
		GiveScopeLock();
    }
}

MIO_PROGRESS_R* GMP232x::getExportScopeProgress(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETPROGRESS,
                              0,
                              (SINT32)&m_ExportProgress);
    if (m_ExportProgress.Status == PROGRESS_DONE)
    {
    	GiveScopeLock();
    }
    return &m_ExportProgress;
}

GMP232X_SCOPE_DATA* GMP232x::exportScopeData(UINT32 ui32Index, UINT32 ui32Timeout)
{
    PARAMETERLIST l_param;

    if(ui32Index == 0)
    {
		TakeScopeLock(ui32Timeout);
    }

    l_param[0] = (SINT32)&m_GetScopeData;
    l_param[1] = (SINT32)ui32Index;
    {
        BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSCOPE,
                                  0,
                                  &l_param,
                                  2);
    }

    if(ui32Index == GMP232X_SCOPE_MAXVALIDX)
    {
    	GiveScopeLock();
    }
    return &m_GetScopeData;
}

GMP232X_SCOPE_STATE* GMP232x::getScopeState(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSCOPESTATE,
                              0,
                              (SINT32)&m_ScopeState);
    return &m_ScopeState;
}

GMP232X_HARMONICS* GMP232x::getHarmonics(UINT32 harmonicsId, UINT32 indexStart, UINT32 indexEnd)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)harmonicsId;
    l_param[1] = (SINT32)indexStart;
    l_param[2] = (SINT32)indexEnd;
    l_param[3] = (SINT32)&m_Hammonics;
    {
        BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETHARMONICS,
                                  0,
                                  &l_param,
                                  4);
    }
    return m_Hammonics;
}


VOID GMP232x::setModuleState(UINT32 state)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETSTATE,
                              0,
                              (SINT32)state);
}

UINT32 GMP232x::getModuleState(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATE,
                              0,
                              (SINT32)&m_ModuleState);
    return m_ModuleState;
}

VOID GMP232x::setSampleCfg(GMP232X_SAMPLE_CONFIG *sampleCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETSAMPLECFG,
                              0,
                              (SINT32)sampleCfg);
}

GMP232X_SAMPLE_CONFIG* GMP232x::getSampleCfg(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSAMPLECFG,
                              0,
                              (SINT32)&m_SampleCfg);
    return &m_SampleCfg;
}

GMP232x::SRawDataSamples_t* GMP232x::getRawDataSamples(VOID)
{
    PARAMETERLIST	l_param;
    UINT32			l_ui32NoOfNewValues = 0;
    UINT64			l_NewTimeStamp;
    SINT64			l_TempTimeStamp = 0;

    l_param[0] = (SINT32)m_ui32StartIndex;
    l_param[1] = (SINT32)&m_RawSampleDatas.sSampleData;
    l_param[2] = (SINT32)&l_ui32NoOfNewValues;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPENDINGSAMPLES,
                              0,
                              &l_param,
                              3);

    m_RawSampleDatas.ui32Len = l_ui32NoOfNewValues;
    m_ui32StartIndex = (m_ui32StartIndex + l_ui32NoOfNewValues) % GMP_MAX_NO_SAMPLES;

    /* Calculate if data is valid/continuous */
    l_NewTimeStamp = m_RawSampleDatas.sSampleData[l_ui32NoOfNewValues - 1].Timestamp;

    l_TempTimeStamp = l_NewTimeStamp - m_OldTimeStamp;
    if (l_TempTimeStamp < 0)
    {
    	l_TempTimeStamp = __LONG_LONG_MAX__ - m_OldTimeStamp + l_NewTimeStamp;
    }
    m_OldTimeStamp = l_NewTimeStamp;

    if (l_TempTimeStamp > 3300)
    {
    	m_RawSampleDatas.b8DataIsContinuous = FALSE;
    }
    else
    {
    	m_RawSampleDatas.b8DataIsContinuous = TRUE;
    }

    return &m_RawSampleDatas;
}

GMP232X_SAMPLE_VAL* GMP232x::getLastDataSample(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLATESTSAMPLE,
                              0,
                              (SINT32)&m_LastSampleData);
    return &m_LastSampleData;
}

VOID GMP232x::setInhibitCfg(GMP232X_LIMIT_MASK *inihibitCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETINHIBITCFG,
                              0,
                              (SINT32)inihibitCfg);
}

GMP232X_LIMIT_MASK* GMP232x::getInhibitCfg(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETINHIBITCFG,
                              0,
                              (SINT32)&m_InhibitCfg);
    return &m_InhibitCfg;
}

BOOL8 GMP232x::TakeHistoryLock(UINT32 LockTimeout)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)LockTimeout;
    l_param[1] = (SINT32)&m_HistoryLockHandle;

	try
	{
		BasicIoModule::doCommmand(MIO_CMD_GMP232X_TAKEHISTORYLOCK,
								  0,
								  &l_param,
								  2);
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

VOID GMP232x::GiveHistoryLock(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GIVEHISTORYLOCK,
                              0,
                              (SINT32)&m_HistoryLockHandle);
}

GMP232X_HISTORY_ENTRY* GMP232x::getAlarmHistory(UINT32 AlarmIdx, UINT32 nbEntries)
{
    PARAMETERLIST l_param;
    TakeHistoryLock(GMP_HISTORYLOCKTIMEOUT);

    l_param[0] = (SINT32)&m_HistoryLockHandle;
    l_param[1] = (SINT32)AlarmIdx;
    l_param[2] = (SINT32)nbEntries;
    l_param[3] = (SINT32)&m_HistoryData;
    {
        BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETALARMHISTORY,
                                  0,
                                  &l_param,
                                  4);
    }

    GiveScopeLock();
    return &m_HistoryData;
}

VOID GMP232x::deleteAlarmHistory(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_DELETEALARMHISTORY, 0);
}

VOID GMP232x::setModuleCfg(GMP232X_CONFIG *moduleCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETCONFIG,
                              0,
                              (SINT32)moduleCfg);
}

GMP232X_CONFIG* GMP232x::getModuleCfg(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETCONFIG,
                              0,
                              (SINT32)&m_moduleCfg);
    return &m_moduleCfg;
}

VOID GMP232x::setSimData(GMP232X_SIMDATA *simData)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETSIMDATA,
                              0,
                              (SINT32)simData);
}

GMP232X_SIMDATA* GMP232x::getSimData(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSIMDATA,
                              0,
                              (SINT32)&m_SimData);
    return &m_SimData;
}

GMP232X_STATISTIC* GMP232x::getStatistics(UINT32 dataPointId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)dataPointId;
    l_param[1] = (SINT32)&m_StatisticsData;
    {
        BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATISTIC_INDEXED,
                                  0,
                                  &l_param,
                                  2);
    }

    return &m_StatisticsData;
}

GMP232X_STATISTIC* GMP232x::getStatisticsDisplay(UINT32 StartIdx, UINT32 nbDispStatData, GMP232X_STATISTIC* pStat)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)StartIdx;
    l_param[1] = (SINT32)nbDispStatData;
    l_param[2] = (SINT32)pStat;
    {
        BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATISTIC_RANGED,
                                  0,
                                  &l_param,
                                  3);
    }

    return pStat;
}

VOID GMP232x::ResetStatistics(VOID)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_RESETSTATISTICS, 0);
}


UINT32 GMP232x::getStatisticsNumber(VOID)
{
	UINT32 NumberOfStatistics;
    BasicIoModule::doCommmand(MIO_CMD_GETNBSTATISTICS,
                              0,
                              (SINT32)&NumberOfStatistics);
    return NumberOfStatistics;
}

VOID GMP232x::setRelayCfg(UINT32 relayCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETRELAYCFG,
                              0,
                              (SINT32)relayCfg);
}

UINT32 GMP232x::getRelayCfg(VOID)
{
	UINT32 DefaultRelayCfg;
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETRELAYCFG,
                              0,
                              (SINT32)&DefaultRelayCfg);
    return DefaultRelayCfg;
}

VOID GMP232x::forceRelay(UINT32 setState)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_FORCERELAY,
                              0,
                              (SINT32)setState);
}

VOID GMP232x::resetRelay(UINT32 Channel)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_RESETRELAY,
                              0,
                              (SINT32)Channel);
}

GMP232X_SWITCHCOUNT* GMP232x::getSwitchCountRelays(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSWITCHCOUNT,
                              0,
                              (SINT32)&m_RelaySwitchCount);
    return &m_RelaySwitchCount;
}

GMP232X_PHASE_UI_S* GMP232x::getPhase_UI_S(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETPHI_UI_S,
                              0,
                              (SINT32)&m_Phase_UI_S);
    return &m_Phase_UI_S;
}

GMP232X_BULK_SYMCOMPONENTS* GMP232x::getBulkSymComponents(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETBULK_SYMCOMPONENTS,
                              0,
                              (SINT32)&m_SymComponentsBulk);
    return &m_SymComponentsBulk;
}


GMP232X_BULK_FRMS_FCS* GMP232x::getBulkFRMS_FCS_Values(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETBULK_FRMS_FCS,
                              0,
                              (SINT32)&m_FRMS_FCS_Values);
    return &m_FRMS_FCS_Values;
}

GMP232X_BULK_FRMS_FCC* GMP232x::getBulkFRMS_FCC_Values(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETBULK_FRMS_FCC,
                              0,
                              (SINT32)&m_FRMS_FCC_Values);
    return &m_FRMS_FCC_Values;
}

GMP232X_BULK_TRMS_HCS* GMP232x::getBulkTRMS_HCS_Values(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETBULK_TRMS_HCS,
                              0,
                              (SINT32)&m_TRMS_HCC_Values);
    return &m_TRMS_HCC_Values;
}

GMP232X_BULK_THD_TDD* GMP232x::getBulkTHD_TDD_Values(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETBULK_THD_TDD,
                              0,
                              (SINT32)&m_THD_TDD_Values);
    return &m_THD_TDD_Values;
}

VOID GMP232x::vrw_setRelaySwitchCount(GMP232X_SWITCHCOUNT *switchCount)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETSWITCHCOUNT,
                              0,
                              (SINT32)switchCount);
}

VOID GMP232x::vrw_setAsym(GMP232X_ASYM *asym)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETASYM,
                              0,
                              (SINT32)asym);
}

VOID GMP232x::vrw_setFRMS_FCC(GMP232X_FRMS_FCC_VALUES *frmsFcc)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETFRMS_FCC,
                              0,
                              (SINT32)frmsFcc);
}

VOID GMP232x::vrw_setFRMS_FCS(GMP232X_FRMS_FCS_VALUES *frmsFcs)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETFRMS_FCS,
                              0,
                              (SINT32)frmsFcs);
}

VOID GMP232x::vrw_setTRMS_HCC(GMP232X_TRMS_HCC_VALUES *trmsHcc)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETTRMS_HCC,
                              0,
                              (SINT32)trmsHcc);
}

VOID GMP232x::vrw_setTRMS_HCS(GMP232X_TRMS_HCS_VALUES *trmsHcs)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETTRMS_HCS,
                              0,
                              (SINT32)trmsHcs);
}

VOID GMP232x::vrw_setPhase(GMP232X_PHASE *phase)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPHASE,
                              0,
                              (SINT32)phase);
}

VOID GMP232x::vrw_setPhaseRef(GMP232X_PHASEREF *phaseRef)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPHASE_REF,
                              0,
                              (SINT32)phaseRef);
}

VOID GMP232x::vrw_setPowerFactor(GMP232X_POWERFACTOR *powerFactor)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPOWERFACTOR,
                              0,
                              (SINT32)powerFactor);
}

VOID GMP232x::vrw_setPowersFRMS_FCC(GMP232X_POWERS_FRMS_FCC *powers)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPOWERS_FRMS_FCC,
                              0,
                              (SINT32)powers);
}

VOID GMP232x::vrw_setPowersFRMS_FCS(GMP232X_POWERS_FRMS_FCS *powers)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPOWERS_FRMS_FCS,
                              0,
                              (SINT32)powers);
}

VOID GMP232x::vrw_setPowersTRMS_HCC(GMP232X_POWERS_TRMS_HCC *powers)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPOWERS_TRMS_HCC,
                              0,
                              (SINT32)powers);
}

VOID GMP232x::vrw_setPowersTRMS_HCS(GMP232X_POWERS_TRMS_HCS *powers)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETPOWERS_TRMS_HCS,
                              0,
                              (SINT32)powers);
}

VOID GMP232x::vrw_setRocofRotDir(GMP232X_ROCOF_ROTDIR *rocofRotDir)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETROCOF_ROTDIR,
                              0,
                              (SINT32)rocofRotDir);
}

VOID GMP232x::vrw_setSymComponents(GMP232X_SYMCOMPONENTS *symComponents)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_VRW_SETSYM_COMPONENTS,
                              0,
                              (SINT32)symComponents);
}

UINT64 GMP232x::getHighResTime(VOID)
{
	UINT64  l_timestamp;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETHIRESTIME,
                              0,
                              (SINT32)&l_timestamp);

    return l_timestamp;
}

VOID GMP232x::RESETAVERAGER(UINT32 averager)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_RESETAVERAGER,
                              0,
                              averager);
}

VOID GMP232x::setMeanCfg(GMP232X_MEAN_CONFIG *MeanCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETMEANCFG,
                              0,
                              (SINT32)MeanCfg);
}

GMP232X_MEAN_CONFIG* GMP232x::getMeanCfg(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMEANCFG,
                              0,
                              (SINT32)&m_MeanCfg);
    return &m_MeanCfg;
}

VOID GMP232x::setRelayLimitCfg(GMP232X_LIMIT_RELAYCFG *LimitRelayCfg)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_RELAYCFG,
                              0,
                              (SINT32)LimitRelayCfg);
}

GMP232X_LIMIT_RELAYCFG* GMP232x::getRelayLimitCfg(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_RELAYCFG,
                              0,
                              (SINT32)&m_LimitRelayCfg);
    return &m_LimitRelayCfg;
}

VOID GMP232x::setLimitScopeCfg(GMP232X_LIMIT_MASK *LimitScopeCfg)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_SCOPECFG,
							  0,
							  (SINT32)LimitScopeCfg);
}

GMP232X_LIMIT_MASK* GMP232x::getLimitScopeCfg(VOID)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_SCOPECFG,
							  0,
							  (SINT32)&m_LimitScopeCfg);
	return &m_LimitScopeCfg;
}

VOID GMP232x::setExtendenCfg(GMP232X_CONFIG_EXT *ExtendedCfg)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETCONFIG_EXT,
							  0,
							  (SINT32)ExtendedCfg);
}

GMP232X_CONFIG_EXT* GMP232x::getExtendenCfg(VOID)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETCONFIG_EXT,
							  0,
							  (SINT32)&m_ExtendedCfg);
	return &m_ExtendedCfg;
}

VOID GMP232x::setManualRelay(GMP232X_LIMIT_MASK *LimitId, UINT32 Channel, BOOL32 enable)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)LimitId;
    l_param[1] = (SINT32)enable;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETMANUALRELAY,
                              0,
                              &l_param,
                              2);
}

BOOL32 GMP232x::getManualRelay(GMP232X_LIMIT_MASK *limitId, UINT32 Channel)
{
	BOOL32 l_enable;
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMANUALRELAY,
							  Channel,
							  (SINT32)&l_enable);
	return l_enable;
}

UINT8* GMP232x::getCfgCheckSum(VOID)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETCFGCHECKSUM,
							  0,
							  (SINT32)m_checkSumPart);
	return m_checkSumPart;
}

VOID GMP232x::setLimitNegSys(GMP232X_LIMIT_MASK *LimitId, GMP232X_LIMIT_NEGSYS *NegSys)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)LimitId;
    l_param[1] = (SINT32)NegSys;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_SETLIMIT_NEGSYS,
                              0,
                              &l_param,
                              2);
}

GMP232X_LIMIT_NEGSYS* GMP232x::getLimitNegSys(GMP232X_LIMIT_MASK *LimitId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)LimitId;
    l_param[1] = (SINT32)&m_NegSys;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_NEGSYS,
                              0,
                              &l_param,
                              2);

    return &m_NegSys;
}

UINT32 GMP232x::getError(VOID)
{
	UINT32 l_Error;
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETERROR,
							  0,
							  (SINT32)&l_Error);
	return l_Error;
}

UINT32 GMP232x::getAutoStart(VOID)
{
	UINT32 l_AutoStart;
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETAUTOSTART,
							  0,
							  (SINT32)&l_AutoStart);
	return l_AutoStart;
}

GMP232X_LIMIT_STATUS GMP232x::getLimitStatus(VOID)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_STATUS,
							  0,
							  (SINT32)&m_LimitStatus);
	return m_LimitStatus;
}

GMP232X_MEAN* GMP232x::getMeanValue(UINT32 dataPointIdx, UINT32 averager)
{
	PARAMETERLIST l_param;
	GMP232X_MEAN_REQUEST l_reqDataPoint;

	l_reqDataPoint.averager = averager;
	l_reqDataPoint.dataPointIdx =  dataPointIdx;
    l_param[0] = 1;
    l_param[1] = (SINT32)&l_reqDataPoint;
    l_param[2] = (SINT32)&m_MeanValue;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMEANVALUE_INDEXED,
                              0,
                              &l_param,
                              3);
    return &m_MeanValue;
}

VOID GMP232x::getMeanValueRanged(UINT32 Idx_RangeStart, UINT32 averager, UINT32 NbrOfValues, GMP232X_MEAN *dataPoints)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)Idx_RangeStart;
    l_param[1] = (SINT32)NbrOfValues;
    l_param[2] = (SINT32)dataPoints;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMEANVALUE_RANGED,
                              0,
                              &l_param,
                              3);
}

VOID GMP232x::getMeanValueIndexed(UINT32 NbrOfValues, GMP232X_MEAN_REQUEST *reqDataPoint, GMP232X_MEAN *dataPoint)
{
	PARAMETERLIST l_param;

    l_param[0] = (SINT32)NbrOfValues;
    l_param[1] = (SINT32)reqDataPoint;
    l_param[2] = (SINT32)dataPoint;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMEANVALUE_INDEXED,
                              0,
                              &l_param,
                              3);
}

VOID GMP232x::getMeanValueConfigured(UINT32 averager, UINT32 *NbrOfValues, GMP232X_MEAN *meanValues)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)averager;
    l_param[1] = (SINT32)meanValues;
    l_param[2] = (SINT32)NbrOfValues;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETMEANVALUECONFIGURED,
                              0,
                              &l_param,
                              3);
}

GMP232X_STATISTIC* GMP232x::getStatisticValue(UINT32 StatisticId)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)StatisticId;
    l_param[1] = (SINT32)1;
    l_param[2] = (SINT32)&m_StatisticPoint;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATISTIC_RANGED,
                              0,
                              &l_param,
                              3);

    return &m_StatisticPoint;
}

VOID GMP232x::getStatisticValuesRanged(UINT32 Id_RangeStart, UINT32 NbrOfValues, GMP232X_STATISTIC *dataPoints)
{
    PARAMETERLIST l_param;

    l_param[0] = (SINT32)Id_RangeStart;
    l_param[1] = (SINT32)NbrOfValues;
    l_param[2] = (SINT32)dataPoints;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATISTIC_RANGED,
                              0,
                              &l_param,
                              3);
}

VOID GMP232x::getStatisticValueIndexed(UINT32 *dataPointIdx, UINT32 NbrOfValues, GMP232X_STATISTIC *dataPoints)
{
	PARAMETERLIST l_param;

    l_param[0] = (SINT32)dataPointIdx;
    l_param[1] = (SINT32)NbrOfValues;
    l_param[2] = (SINT32)dataPoints;

    BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETSTATISTIC_INDEXED,
                              0,
                              &l_param,
                              3);
}

VOID GMP232x::getHistoryTotal(GMP232X_HISTORY_COUNT *historyCounters)
{
	BasicIoModule::doCommmand(MIO_CMD_GMP232X_GETLIMIT_STATUS,
							  0,
							  (SINT32)historyCounters);
}

//MIO_CMD_GMP232X_GETHISTORYTOTAL
