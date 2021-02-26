/**
 ********************************************************************************
 * @file     GMP232.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid measurement and protection module GMP232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef GMP232_HPP_
#define GMP232_HPP_

#define GMP_OVERHEAD	         5		/**< Number of extra bytes in each request */
#define GMP_RUNBEFOREVALIDDATA   100	/**< Number of data before data is valid */
#define GMP_MAX_NO_SAMPLES       33		/**< Max buffer size of raw data buffer */
#define GMP_SCOPELOCKTIMEOUT	 10		/**< Time before scope lock expires [s] */


/**********************************************************************
 * system includes
 **********************************************************************/
#include <gmp232.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicMixedModule.hpp"
#include "../../common/base/DigitalChannel.hpp"

/**
 * @brief Module for Net Measuering and Analysis GMP232
 *
 */
class GMP232: public BasicMixedModule
{

private:

    /**
     * Selection Table for Do Command
     * getSelectedValues
     */
    static UINT64 csa_Selection[64];

public:

    /**
     * Datatype Definitions/Mappings
     */
    typedef UINT32 LockHandle_t;
    typedef GMP_ENERGY SEnergy_t;
    typedef GMP_ENERGYREAL SEnergyR_t;
    typedef GMP_SCOPECFG SScopeConfig_t;
    typedef GMP_SCOPESTATE SScopeState_t;
    typedef GMP_SCOPEDATA SScopeData_t;
    typedef GMP_SIMDATA SSimulationData_t;
    typedef GMP_DISPLAYSTATISTICS SDisplayStatistics_t;
    typedef GMP_GETSTATISTIC SStatistic_t;
    typedef GMP_ALARMHISTORY SAlarmHistory_t;
    typedef GMP_HARMONICS SHarmonics_t;
    typedef GMP_PHASEANGLES SPhaseAngels_t;
    typedef MIO_PROGRESS_R SProgress_t;
    typedef GMP_QULIMIT SQuLimit_t;
    typedef GMP_CONFIG SBaseConfig_t;
    typedef GMP_VALUES SValues_t;
    typedef GMP_LIMIT SLimit_t;
    typedef GMP_FREQUENCYLIMIT SFrequencyLimit_t;
    typedef GMP_SWITCHCOUNT SSwitchCount_t;
    typedef GMP_VECTORDIAGRAM SVectorDiagram_t;
    typedef GMP_FRT SFaultRideThrough_t;
    typedef GMP_SAMPLEVAL SSampleValue_t;
    typedef GMP_IECVALUES SIECValues_t;

    /**
     * Possible values of SampleRate
     */
    typedef enum
    {
        eRate_10_Khz = 0, eRate_5_Khz = 1, eRate_2500_Hz = 2, eRate_1250_Hz = 3, eRate_625_Hz = 4
    } ESampleRate_t;

    /**
     * Possible types of Value to Sample
     */
    typedef enum
    {
        eSampleValue_P = GMP_SAMPLE_MEAN_P
    } ESampleValue_t;

    /**
     * Configuration of Sample Value
     *
     * eSampleRate   : Samplefrequency
     * ui32Len       : Count of values for averaging (1..205)
     * eValue        : definition of Valuetype
     */
    typedef struct SSampleConfig_t
    {
        ESampleRate_t eSampleRate;
        UINT32 ui32Len;
        ESampleValue_t eValue;

        SSampleConfig_t()
        {
            eSampleRate = eRate_10_Khz;
            ui32Len = 1;
            eValue = eSampleValue_P;
        }
    } SSampleConfig_t;

    /**
     * Configuration of Raw Data buffer
     *
     * sSampleData : Raw Data buffer
     */
    typedef SSampleValue_t SRawDataBuffer_t[GMP_MAX_NO_SAMPLES];

    /**
     * Configuration of Raw Data Sample
     *
     * eSampleData        : Pointer to raw data samples
     * ui32Len            : Number of data that is read
     * b8DataIsContinious : Indicate that data is continuous sampled
     */
    typedef struct SRawDataSamples_t
    {
        SRawDataBuffer_t sSampleData;
        UINT32 ui32Len;
        BOOL8 b8DataIsContinuous;

        SRawDataSamples_t()
        {
            ui32Len = 0;
            b8DataIsContinuous = FALSE;
        }
    } SRawDataSamples_t;

    /**
     * IDs for Statistics Selection
     */
    typedef enum
    {
        eStatU_L1N_Peak = GMP_STATISTICS_U_L1N_PEAK,
        eStatU_L2N_Peak = GMP_STATISTICS_U_L2N_PEAK,
        eStatU_L3N_Peak = GMP_STATISTICS_U_L3N_PEAK,
        eStatU_L1L2_Peak = GMP_STATISTICS_U_L12_PEAK,
        eStatU_L2L3_Peak = GMP_STATISTICS_U_L23_PEAK,
        eStatU_L1L3_Peak = GMP_STATISTICS_U_L31_PEAK,
        eStatI_L1_Peak = GMP_STATISTICS_I_L1_PEAK,
        eStatI_L2_Peak = GMP_STATISTICS_I_L2_PEAK,
        eStatI_L3_Peak = GMP_STATISTICS_I_L3_PEAK,
        eStatI_N_Peak = GMP_STATISTICS_I_N_PEAK,
        eStatU_L1N = GMP_STATISTICS_U_L1N,
        eStatU_L2N = GMP_STATISTICS_U_L2N,
        eStatU_L3N = GMP_STATISTICS_U_L3N,
        eStatU_L1L2 = GMP_STATISTICS_U_L12,
        eStatU_L2L3 = GMP_STATISTICS_U_L23,
        eStatU_L1L3 = GMP_STATISTICS_U_L31,
        eStatI_L1 = GMP_STATISTICS_I_L1,
        eStatI_L2 = GMP_STATISTICS_I_L2,
        eStatI_L3 = GMP_STATISTICS_I_L3,
        eStatI_N = GMP_STATISTICS_I_N,
        eStatP_L1 = GMP_STATISTICS_P_L1,
        eStatP_L2 = GMP_STATISTICS_P_L2,
        eStatP_L3 = GMP_STATISTICS_P_L3,
        eStatP_SUM = GMP_STATISTICS_P_SUM,
        eStatS_L1 = GMP_STATISTICS_S_L1,
        eStatS_L2 = GMP_STATISTICS_S_L2,
        eStatS_L3 = GMP_STATISTICS_S_L3,
        eStatS_SUM = GMP_STATISTICS_S_SUM,
        eStatQ_L1 = GMP_STATISTICS_Q_L1,
        eStatQ_L2 = GMP_STATISTICS_Q_L2,
        eStatQ_L3 = GMP_STATISTICS_Q_L3,
        eStatQ_SUM = GMP_STATISTICS_Q_SUM,
        eStatF = GMP_STATISTICS_F,
        eStatROCOF = GMP_STATISTICS_ROCOF,
        eStatTHD_U1 = GMP_STATISTICS_THD_U1U12,
        eStatTHD_U2 = GMP_STATISTICS_THD_U2U23,
        eStatTHD_U3 = GMP_STATISTICS_THD_U3U31,
        eStatTDD_I1 = GMP_STATISTICS_TDD_I1,
        eStatTDD_I2 = GMP_STATISTICS_TDD_I2,
        eStatTDD_I3 = GMP_STATISTICS_TDD_I3,
        eStatPHI_U1 = GMP_STATISTICS_PHI_U1I1,
        eStatPHI_U2 = GMP_STATISTICS_PHI_U2I2,
        eStatPHI_U3 = GMP_STATISTICS_PHI_U3I3,
        eStatVector = GMP_STATISTICS_VECTORJMP,
        eStatAsym_U = GMP_STATISTICS_ASYM_U,
        eStatAsym_I = GMP_STATISTICS_ASYM_I

    } EStatisticId_t;

    /**
     * Selection Array for getSelectedValues CALL
     * see eSelctXXX - Constants
     */
    typedef BOOL8 ASelection_t[64];

    /**
     * This enum is used for Indexing through
     * csa_Selection[]
     * do not change the order
     */
    typedef enum
    {
        eSlctU_L1L2_rms = 0, /** 0 */
        eSlctU_L2L3_rms = 1,
        eSlctU_L1L3_rms = 2,
        eSlctU_L1N_rms = 3,
        eSlctU_L2N_rms = 4,
        eSlctU_L3N_rms = 5,
        eSlctI_L1_rms = 6,
        eSlctI_L2_rms = 7,
        eSlctI_L3_rms = 8,
        eSlctI_N_rms = 9,
        eSlctP_SUM = 10,
        eSlctP_L1 = 11,
        eSlctP_L2 = 12,
        eSlctP_L3 = 13,
        eSlctQ_SUM = 14,
        eSlctQ_L1 = 15,
        eSlctQ_L2 = 16,
        eSlctQ_L3 = 17,
        eSlctS_SUM = 18,
        eSlctS_L1 = 19,
        eSlctS_L2 = 20,
        eSlctS_L3 = 21,
        eSlctFrequency = 22,
        eSlctROCOF = 23,
        eSlctASYM_U = 24,
        eSlctASYM_I = 25,
        eSlctPHI_U1I1 = 26,
        eSlctPHI_U2I2 = 27,
        eSlctPHI_U3I3 = 28,
        eSlctPF_SUM = 29,
        eSlctPF_L1 = 30,
        eSlctPF_L2 = 31,
        eSlctPF_L3 = 32,
        eSlctROTDIR_U = 33,
        eSlctROTDIR_I = 34,
        eSlctOVERLOAD_U = 35,
        eSlctOVERLOAD_I = 36,
        eSlctVECTORJUMP = 37,
        eSlctALL = 38 /** ALL should be last ID */

    } ESelection_t;

    /**
     * Possible Values for Relay Configuration
     */
    typedef enum
    {
        eOpen = 0, eClosed = 1
    } ERelayConfig_t;

    /**
     * Ids for Harmonics Selection
     */
    typedef enum
    {
        eHidVoltageL1 = GMP_HARMONICS_U_L1,
        eHidVoltageL2 = GMP_HARMONICS_U_L2,
        eHidVoltageL3 = GMP_HARMONICS_U_L3,
        eHidCurrentL1 = GMP_HARMONICS_I_L1,
        eHidCurrentL2 = GMP_HARMONICS_I_L2,
        eHidCurrentL3 = GMP_HARMONICS_I_L3
    } EHarmonicsId_t;

    /**
     * Possible Values for getEvent(...) and
     * attachEvent
     */
    typedef enum
    {
        eEventScopeReady = MIO_EV_SCOPEREADY,
        eEventHarmonicsLimit = MIO_EV_HARMONICS,
        eEventVoltageMin = MIO_EV_U_MIN,
        eEventVoltageMax = MIO_EV_U_MAX,
        eEventCurrentMax = MIO_EV_I_MAX
    } EGmpEvent_t;

    /**
     * Possible Values for attachError
     */
    typedef enum
    {
        /** Module */
        eErrorVectorJump = MIO_E_VECTORJMP,
        eErrorQuPCC = MIO_E_QUPCC,
        eErrorQuGEN = MIO_E_QUGEN,
        eErrorROCOFMax = MIO_E_ROCOF_MAX,
        eErrorAsymUMax = MIO_E_ASYM_U_MAX,

        /** Channel 1-3 */
        eErrorUMin = MIO_E_U_MIN,
        eErrorUMax = MIO_E_U_MAX,
        eErrorTHD_UMAX = MIO_E_THD_U_MAX,
        eErrorFRT = MIO_E_FRT,

        /** Channel 4-6 */
        eErrorIMax = MIO_E_I_MAX,
        eErrorTDD_IMAX = MIO_E_TDD_I_MAX,

        /** Channel 7 */
        eErrorFreqInMin = MIO_E_F_IN_MIN,
        eErrorFreqInMax = MIO_E_F_IN_MAX,
        eErrorFreqMidMin = MIO_E_F_MID_MIN,
        eErrorFreqMidMax = MIO_E_F_MID_MAX,
        eErrorFreqOutMin = MIO_E_F_OUT_MIN,
        eErrorFreqOutMax = MIO_E_F_OUT_MAX
    } EGmpError_t;

    /**
     * State of Module
     */
    typedef enum
    {
        eStateRun = GMP_STATE_RUN,
        eStateForceRelay = GMP_STATE_FORCERELAY,
        eStateSimulation = GMP_STATE_SIMULATION,
        eStateConfig = GMP_STATE_CONFIG,
        eStateMeasuring = GMP_STATE_MEASURING
    } EState_t;

    /**
     * Possible Values for Limits
     */
    typedef enum
    {
        eTypeUI, eTypeAsymetric, eTypeHarmonics, eTypeROCOF, eTypeVectorJump
    } ELimitType_t;

    /**
     * possible Values for Limit Identifier
     */
    typedef enum
    {
        eIdUndefined = -1,
        /** LimitCfg */
        eIdErrUMin = GMP_ERR_U_MIN,
        eIdErrUMax = GMP_ERR_U_MAX,
        eIdEvtUMin = GMP_EVT_U_MIN,
        eIdEvtUMax = GMP_EVT_U_MAX,
        eIdErrIMax = GMP_ERR_I_MAX,
        eIdEvtIMax = GMP_EVT_I_MAX,
        eIdErrTHD = GMP_ERR_THD_MAX,
        eIdErrTDD = GMP_ERR_TDD_MAX,
        /** Asym */
        eIdErrAsymUMax = GMP_ERR_ASYM_U_MAX,
        eIdErrAsymIMax = GMP_ERR_ASYM_I_MAX,
        /** Harmonics */
        eIdHarmonics_U = GMP_HARMONICS_U,
        eIdHarmonics_I = GMP_HARMONICS_I
    } ELimitId_t;

    /**
     * Ids for Frequency Window
     */
    typedef enum
    {
        eFreqIN = GMP_F_IN, eFreqMID = GMP_F_MID, eFreqOUT = GMP_F_OUT
    } EFrequencLimit_t;

    /**
     * Modes of Module
     * Can only be set during Bootup!
     */
    typedef enum
    {
        eModeSinglePhase = GMP_M_SINGLEPHASE,
        eMode2PhaseAsym = GMP_M_2PHASEASYM,
        eMode3WireBalanced = GMP_M_3WIRE3PHASEBALANCED,
        eMode3WireAsymetric = GMP_M_3WIRE3PHASEASYM,
        eMode3WireAron = GMP_M_3WIRE3PHASEARON,
        eMode4WireBalanced = GMP_M_4WIRE3PHASEBALANCED,
        eMode4WireAsymetric = GMP_M_4WIRE3PHASEASYM
    } EMode_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    GMP232();

    /**
     * Constructor
     *
     * @param ui32CardNumber - Cardnumber of Module
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GMP232(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~GMP232();

    /**
     * Initialize all values at construction.
     */
    VOID init(VOID);

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/

    /**
     * Attach to Event Interrupt
     *
     * @param pSession - Event Session from System
     * @param pListener - Object which contains callback method
     * @param eEvent - see eEventXXXX for possible Values
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when attach event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachGmpEvent(EventSession *pSession, BasicEventListener *pListener, EGmpEvent_t eEvent,
            UINT8 ui8Channel = 0);

    /**
     * Attach to Error Interrupt
     *
     * @param pSession - Error Session from System
     * @param pListener - Object which contains callback method
     * @param eError - see eErrorXXXX for possible Values
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when attach error to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachGmpError(ErrorSession *pSession, BasicErrorListener *pListener, EGmpError_t eError,
            UINT8 ui8Channel = 0);
    /**
     * DoCommands
     */

    /**
     * Delete Alarmhistory
     * possible in state eStateConfig
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID deleteHistory(VOID);

    /**
     * Read Statistic values
     *
     * @param ui32Index - first Value to read
     * @param ui32Count - number of values to read
     * @param pStat - pointer to Variables
     *
     * @returns the pStat pointer with data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232::SDisplayStatistics_t* displayStatistics(UINT32 ui32Index, UINT32 ui32Count, GMP232::SDisplayStatistics_t* pStat);

    /**
     * Reset Statistic of Module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetStatistics(VOID);

    /**
     * Export Scope in Comtrade-Format
     * This function is non blocking
     * N.B. Use getExportScopeProgress to get status until status = PROGRESS_DONE (this will automatically release lock handle)
     *
     * @param pch8Filename - File for export
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScopeNB(CHAR8* pch8Filename);

    /**
     * Export Scope in Comtrade-Format
     * This function is a blocking function and returns when the files has been written.
     *
     * @param pch8Filename - File for export
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScope(CHAR8* pch8Filename);

    /**
     * Read INI File to configure Module
     *
     * @param pch8Filename - Filename of INI-File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID processIniFile(CHAR8 pch8Filename);

    /**
     * Force Relay
     * Only Possible in eStateForceRelay
     *
     * @param ui8Channel - selected Channel (10 or 11)
     * @param b8Value - FALSE = OFF, TRUE = ON
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID forceRelay(UINT8 ui8Channel, BOOL8 b8Value);

    /**
     * Reset Relay Output
     *
     * @param ui8Channel - selected Channel (10 or 11)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetRelay(UINT8 ui8Channel);

    /**
     * Start Scope
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID triggerScope(VOID);

    /**
     * Get Selected Count of Alarms
     *
     * @param handle - value from takeHistoryLock
     * @param ui32Index - Start Index
     * @param ui32Count - number of entries
     * @param pValue - pointer to variable
     *
     * @returns a pointer to the Alarm history data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SAlarmHistory_t* getAlarmHistory(LockHandle_t handle, UINT32 ui32Index, UINT32 ui32Count);

    /**
     * Set EnergyCounter
     * Values are from Type UINT64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(SEnergy_t *pValue);

    /**
     * Set EnergyCounter
     * Values are from Type REAL64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(SEnergyR_t *pValue);

    /**
     * Read EnergyCounter
     * Values are from Type UINT64
     *
     * @param pValue - pointer to variable
     * @returns a pointer to the energy data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SEnergy_t* getEnergy(VOID);

    /**
     * Read EnergyCounter
     * Values are from Type REAL64
     *
     * @param pValue - pointer to variable
     * @returns a pointer to the energy data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SEnergyR_t* getEnergyReal(VOID);

    /**
     * Read Eventstate of Module
     *
     * @param ui8Channel - selected Channel (0-6) 0=Module
     * @param pValue - pointer to Variable
     * @returns a pointer to the event data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    EGmpEvent_t* getEvent(UINT8 ui8Channel);

    /**
     * Read Harmonics
     *
     * @param eId - see eHidXXXX
     * @param pValues - pointer to Variable
     * @returns a pointer to the harmonics data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SHarmonics_t* getHarmonics(EHarmonicsId_t eId);

    /**
     * Read available Statistics
     *
     * @param pui32Value - pointer to variable
     *
     * @returns the number of available statistics values.
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getStatisticsCounter(VOID);

    /**
     * Read Phaseangles
     *
     * @param pValue - pointer to Variable
     * @returns a pointer to the phase angle data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SPhaseAngels_t* getPhaseAngles(VOID);

    /**
     * Read Errors during initialization
     *
     * @param ui8Channel - selected Channel
     * The parameter contains either the channel number of
     * the queried channel or the value 0, in order to query
     * all errors that have occurred.
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPreInitErrors(UINT8 ui8Channel);

    /**
     * Read Events during initialization
     *
     * @param ui8Channel - selected Channel
     * The parameter contains either the channel number of
     * the queried channel or the value 0, in order to query
     * all errors that have occurred.
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPreInitEvents(UINT8 ui8Channel);

    /**
     * Read actual Export Progress
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the progress structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SProgress_t* getExportProgress(VOID);

    /**
     * write actual QU-Limit
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setQULimit(SQuLimit_t* psValue);

    /**
     * read actual QU-Limit
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the QU-Limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SQuLimit_t* getQULimit(VOID);

    /**
     * Read Base Config of Module
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the base config structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SBaseConfig_t* getBaseConfig(VOID);

    /**
     * Set Configuration of Relaydefault
     *
     * @param eValue - new Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRelayConfig(ERelayConfig_t eValue);

    /**
     * get Configuration of Relay Default
     *
     * @param peValue  - pointer to variable
     * @returns a pointer to the relay configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    ERelayConfig_t getRelayConfig(VOID);

    /**
     * Set configuration of Scope
     *
     * @param sValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setScopeConfig(SScopeConfig_t *sValue);

    /**
     * Get configuration of Scope
     *
     * @param sValue - pointer to variable
     * @returns a pointer to the scope configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeConfig_t* getScopeConfig(VOID);

    /**
     * Read configuration of RunThrough
     *
     * @return the RunThrough configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getRunThroughConfig(VOID);

    /**
     * Read values from Scope
     * N.B. The last value must be read in order to release the scope lock!
     *
     * @param ui32Index - first Values
     * @param ui32Timeout - timout in s for scope lock (≤ 100 s)
     * @returns a pointer to the scope values structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeData_t* getScopeValues(UINT32 ui32Index, UINT32 ui32Timeout);

    /**
     * Read actual Scope State
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the scope state structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeState_t* getScopeState(VOID);

    /**
     * Read defined values
     *
     * @param paSelection
     * @return a pointer to variable structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SValues_t* getSelectedValues(ASelection_t *paSelection);

    /**
     * Set State Module
     * see eStateXXXX
     *
     * @param eState - value for State
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setState(EState_t eState);

    /**
     * Get State Module
     * see eStateXXXX
     *
     * @param peState - pointer to variable
     * @returns a pointer to the module state structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    EState_t getState(VOID);

    /**
     * Read Statistics
     * see eStatXXX
     *
     * @param eId - identifier
     * @param psValue - pointer to variable
     * @returns a pointer to the statistics data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SStatistic_t* getStatistics(EStatisticId_t eId);

    /**
     * Read switch counter of Relays
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the switch count data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSwitchCount_t* getSwitchCount(VOID);

    /**
     * Read all measured values
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the measured values data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SValues_t* getMeasuredValues(VOID);

    /**
     * Get Vectordigram
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the vector diagram data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SVectorDiagram_t* getVectorDiagram(VOID);

    /**
     * Set ValueTable for FRT
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFaultRideThrough(SFaultRideThrough_t *psValue);

    /**
     * Get actual Valuetable for FRT
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the fault ride through data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SFaultRideThrough_t* getFaultRideThrough(VOID);

    /**
     * Set SimulationValues
     *
     * @param psData - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSimulationData(SSimulationData_t *psData);

    /**
     * get SimulationValues
     *
     * @param psData - pointer to variable
     * @returns a pointer to the simulation data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSimulationData_t* getSimulationData(VOID);

    /**
     * Set Limitconfiguration
     *
     * @param eLimit - see eTypeXXX
     * @param psValue - pointer to variable
     * @param eId - see eIdXXXX
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLimit(ELimitType_t eLimit, SLimit_t *psValue, ELimitId_t eId = eIdUndefined);

    /**
     * Read Limitconfiguration
     *
     * @param eLimit - see eTypeXXX
     * @param psValue - pointer to variable
     * @param eId - see eIdXXXX
     * @returns a pointer to the limit configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SLimit_t* getLimit(ELimitType_t eLimit, ELimitId_t eId = eIdUndefined);

    /**
     * Set Limitconfiguration of Frequencywindow
     *
     * @param psValue - pointer to variable
     * @param eId - see eFreqXXXX
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFrequencyLimit(SFrequencyLimit_t *psValue, EFrequencLimit_t eId);

    /**
     * get Limitconfiguration of Frequencywindow
     *
     * @param psValue - pointer to variable
     * @param eId - see eFreqXXXX
     * @returns a pointer to the frequency limit configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SFrequencyLimit_t* getFrequencyLimit(EFrequencLimit_t eId);

    /**
     *  Get one single Channel as Instance
     *
     * @param ui32Channel - Channelnumber (10 or 11)
     *
     * @returns a pointer to the digital channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or if the channel number is invalid.
     */
    DigitalChannel* getDigitalChannel(UINT32 ui32Channel);

    /**
     * Write Configuration
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSampleConfig(SSampleConfig_t *psValue);

    /**
     * Read Configuration
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the sample configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSampleConfig_t* getSampleConfig(VOID);

    /**
     * Read Samples
     * This function must be executed every 1ms, to keep data continuous.
     * @returns a pointer to the data samples structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SRawDataSamples_t* getSamples(VOID);

    /**
     * Read IEC Values
     *
     * @param psValue - pointer to variable
     * @returns a pointer to the IEC data values structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232::SIECValues_t* getIecValues(VOID);

protected:

    /**
     * Module has 2 Digital Output Channels
     */
    DigitalChannel m_Output[2];

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_GMP232;
    }

private:
    /**
     * Lock Reading from other Applications
     *
     * @param ui32Timeout - timout in ms
     * @param pValue - handle Data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 takeScopeLock(UINT32 ui32Timeout);

    /**
     * Unlock Reading
     *
     * @param handle - Value from takeHistoryLock
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID giveScopeLock();

    /**
     * Lock Reading from other Applications
     *
     * @param ui32Timeout - timout in ms
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID takeHistoryLock(UINT32 ui32Timeout);

    /**
     * Unlock Reading
     *
     * @param handle - Value from takeHistoryLock
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID giveHistoryLock(VOID);

    /**
     * Average function used by getRawDataSamples, to calculate the average of the number of data read.
     */
    UINT32 average(UINT32 newValue);

    EGmpEvent_t m_Event;
    SEnergy_t m_Energy;
    SValues_t m_Values;
    SQuLimit_t m_QuLimit;
    SProgress_t m_Progress;
    SScopeData_t m_ScopeData;
    SStatistic_t m_Statistic;
    SIECValues_t m_IecValues;
    SHarmonics_t m_Harmonics;
    SEnergyR_t m_EnergyReal;
    SScopeState_t m_ScopeState;
    SLimit_t m_ScopeLimit;
    SBaseConfig_t m_BaseConfig;
    SScopeConfig_t m_ScopeConfig;
    SPhaseAngels_t m_PhaseAngles;
    SAlarmHistory_t m_AlarmHistory;
    SSampleConfig_t m_SampleConfig;
    SVectorDiagram_t m_VectorDiagram;
    SFrequencyLimit_t m_FrequencyLimit;
    SSimulationData_t m_SimulationData;
    SRawDataSamples_t m_RawSampleDatas;
    SValues_t m_SelectedValues;
    SFaultRideThrough_t m_FaultRideThrough;
    SSwitchCount_t m_RelaySwitchCount;
    LockHandle_t m_ScopeLockHandle;
    LockHandle_t m_HistoryLockHandle;
};

#endif /** GMP232_HPP_ */
