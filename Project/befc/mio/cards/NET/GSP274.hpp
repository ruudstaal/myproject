/**
 ********************************************************************************
 * @file     GSP274.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid synchronization and protection module GSP274
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef GSP274_HPP_
#define GSP274_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <gsp274.h>

/**********************************************************************
 * project includes
 **********************************************************************
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"
#include "../../common/base/DigitalChannel.hpp"
#include "../../common/base/MIOexception.hpp"

/**
 * @brief Module for Net Measuering and Synchronization GSP274
 */
class GSP274: public BasicAnalogModule
{

private:

    /**
     * Configuration Table for Do Command
     *
     */
    static UINT64 csa_Selection[64];

public:

    /**@{ @name mapped datatypes */
    typedef UINT32 LockHandle_t;
    typedef GSP_ENERGYREAL SEnergyR_t;
    typedef GSP_SCOPECFG SScopeConfig_t;
    typedef GSP_SCOPESTATE SScopeState_t;
    typedef GSP_SCOPEDATA SScopeData_t;
    typedef GSP_SIMDATA SSimulationData_t;
    typedef GSP_DISPLAYSTATISTICS SDisplayStatistics_t;
    typedef GSP_GETSTATISTIC SStatistic_t;
    typedef GSP_ALARMHISTORY SAlarmHistory_t;
    typedef GSP_HARMONICS SHarmonics_t;
    typedef GSP_PHASEANGLES SPhaseAngels_t;
    typedef GSP_QULIMIT SQuLimit_t;
    typedef GSP_CONFIG SBaseConfig_t;
    typedef GSP_VALUES SValues_t;
    typedef GSP_LIMIT SLimit_t;
    typedef GSP_FREQUENCYLIMIT SFrequencyLimit_t;
    typedef GSP_SWITCHCOUNT SSwitchCount_t;
    typedef GSP_VECTORDIAGRAM SVectorDiagram_t;
    typedef GSP_FRT SFaultRideThrough_t;
    typedef GSP_IECVALUES SIECValues_t;
    /**
     * @brief Selection Array
     *
     * Array represents 64 BOOL8 Values which are \n
     * used to map into an UINT64 value. \n
     *
     * Use the enum values of ESelection_t to select \n
     * the specific value like this: \n
     *
     * Sample: ASelection_t[ eSlct_U_L3N_RMS ] = TRUE;
     *
     * @see getSelectedValues
     * @see ESelection_t
     *
     */
    typedef BOOL8 ASelection_t[64];
    /**@} */

    /**
     * @brief IDs for Statistics Selection
     */
    typedef enum
    {
        eIdGEN_U_L1N_SAMPLES = GSP_STATISTICS_GEN_U_L1N_SAMPLES, /**< Voltage phase 1 (samples) */
        eIdGEN_U_L2N_SAMPLES = GSP_STATISTICS_GEN_U_L2N_SAMPLES, /**< Voltage phase 2 (samples) */
        eIdGEN_U_L3N_SAMPLES = GSP_STATISTICS_GEN_U_L3N_SAMPLES, /**< Voltage phase 3 (samples) */
        eIdGEN_U_L12_SAMPLES = GSP_STATISTICS_GEN_U_L12_SAMPLES, /**< Voltage phase 1 and phase 2 (samples) */
        eIdGEN_U_L23_SAMPLES = GSP_STATISTICS_GEN_U_L23_SAMPLES, /**< Voltage phase 2 and phase 3 (samples) */
        eIdGEN_U_L31_SAMPLES = GSP_STATISTICS_GEN_U_L31_SAMPLES, /**< Voltage phase 3 and phase 1 (samples) */
        eIdGEN_I_L1_SAMPLES = GSP_STATISTICS_GEN_I_L1_SAMPLES, /**< Current phase 1 (samples) */
        eIdGEN_I_L2_SAMPLES = GSP_STATISTICS_GEN_I_L2_SAMPLES, /**< Current phase 2 (samples) */
        eIdGEN_I_L3_SAMPLES = GSP_STATISTICS_GEN_I_L3_SAMPLES, /**< Current phase 3 (samples) */
        eIdGEN_I_N_SAMPLES = GSP_STATISTICS_GEN_I_N_SAMPLES, /**< Current neutral (samples) */
        eIdGEN_U_L1N = GSP_STATISTICS_GEN_U_L1N, /**< Voltage phase 1 (RMS) */
        eIdGEN_U_L2N = GSP_STATISTICS_GEN_U_L2N, /**< Voltage phase 2 (RMS) */
        eIdGEN_U_L3N = GSP_STATISTICS_GEN_U_L3N, /**< Voltage phase 3 (RMS) */
        eIdGEN_U_L12 = GSP_STATISTICS_GEN_U_L12, /**< Voltage phase 1 and phase 2 (RMS) */
        eIdGEN_U_L23 = GSP_STATISTICS_GEN_U_L23, /**< Voltage phase 2 and phase 3 (RMS) */
        eIdGEN_U_L31 = GSP_STATISTICS_GEN_U_L31, /**< Voltage phase 3 and phase 1 (RMS) */
        eIdGEN_I_L1 = GSP_STATISTICS_GEN_I_L1, /**< Current phase 1 (RMS) */
        eIdGEN_I_L2 = GSP_STATISTICS_GEN_I_L2, /**< Current phase 2 (RMS) */
        eIdGEN_I_L3 = GSP_STATISTICS_GEN_I_L3, /**< Current phase 3 (RMS) */
        eIdGEN_I_N = GSP_STATISTICS_GEN_I_N, /**< Current neutral (RMS) */
        eIdGEN_P_SUM = GSP_STATISTICS_GEN_P_SUM, /**< Total real power */
        eIdGEN_P_L1 = GSP_STATISTICS_GEN_P_L1, /**< Real power phase 1 */
        eIdGEN_P_L2 = GSP_STATISTICS_GEN_P_L2, /**< Real power phase 2 */
        eIdGEN_P_L3 = GSP_STATISTICS_GEN_P_L3, /**< Real power phase 3 */
        eIdGEN_S_SUM = GSP_STATISTICS_GEN_S_SUM, /**< Total complex power */
        eIdGEN_S_L1 = GSP_STATISTICS_GEN_S_L1, /**< Real complex phase 1 */
        eIdGEN_S_L2 = GSP_STATISTICS_GEN_S_L2, /**< Real complex phase 2 */
        eIdGEN_S_L3 = GSP_STATISTICS_GEN_S_L3, /**< Real complex phase 3 */
        eIdGEN_Q_SUM = GSP_STATISTICS_GEN_Q_SUM, /**< Total reactive power */
        eIdGEN_Q_L1 = GSP_STATISTICS_GEN_Q_L1, /**< Real reactive phase 1 */
        eIdGEN_Q_L2 = GSP_STATISTICS_GEN_Q_L2, /**< Real reactive phase 2 */
        eIdGEN_Q_L3 = GSP_STATISTICS_GEN_Q_L3, /**< Real reactive phase 3 */
        eIdGEN_U_L1_IEC = GSP_STATISTICS_GEN_U_L1_IEC, /**< U1 IEC */
        eIdGEN_U_L2_IEC = GSP_STATISTICS_GEN_U_L2_IEC, /**< U2 IEC */
        eIdGEN_U_L3_IEC = GSP_STATISTICS_GEN_U_L3_IEC, /**< U3 IEC */
        eIdGEN_I_L1_IEC = GSP_STATISTICS_GEN_I_L1_IEC, /**< I1 IEC */
        eIdGEN_I_L2_IEC = GSP_STATISTICS_GEN_I_L2_IEC, /**< I2 IEC */
        eIdGEN_I_L3_IEC = GSP_STATISTICS_GEN_I_L3_IEC, /**< I3 IEC */
        eIdGEN_P_IEC = GSP_STATISTICS_GEN_P_IEC, /**< P IEC */
        eIdGEN_S_IEC = GSP_STATISTICS_GEN_S_IEC, /**< S IEC */
        eIdGEN_Q_IEC = GSP_STATISTICS_GEN_Q_IEC, /**< Q IEC */
        eIdGEN_F = GSP_STATISTICS_GEN_F, /**< Frequency */
        eIdGEN_ROCOF = GSP_STATISTICS_GEN_ROCOF, /**< Rate Of Change Of Frequency */
        eIdGEN_THD_U1U12 = GSP_STATISTICS_GEN_THD_U1U12, /**< THD U1/U12 */
        eIdGEN_THD_U2U23 = GSP_STATISTICS_GEN_THD_U2U23, /**< THD U2/U23 */
        eIdGEN_THD_U3U31 = GSP_STATISTICS_GEN_THD_U3U31, /**< THD U3/U31 */
        eIdGEN_TDD_I1 = GSP_STATISTICS_GEN_TDD_I1, /**< THD I1 */
        eIdGEN_TDD_I2 = GSP_STATISTICS_GEN_TDD_I2, /**< THD I2 */
        eIdGEN_TDD_I = GSP_STATISTICS_GEN_TDD_I3, /**< THD I3 */
        eIdGEN_ASYM_U = GSP_STATISTICS_GEN_ASYM_U, /**< Voltage asymmetric */
        eIdGEN_ASYM_I = GSP_STATISTICS_GEN_ASYM_I, /**< Current asymmetric */
        eIdGEN_PHI_U1I1 = GSP_STATISTICS_GEN_PHI_U1I1, /**< Phase angle from U1 and I1 */
        eIdGEN_PHI_U2I2 = GSP_STATISTICS_GEN_PHI_U2I2, /**< Phase angle from U2 and I2 */
        eIdGEN_PHI_U3I3 = GSP_STATISTICS_GEN_PHI_U3I3, /**< Phase angle from U3 and I3 */
        eIdGEN_VECTORJMP = GSP_STATISTICS_GEN_VECTORJMP, /**< Vector jump */
        eIdBUS_U_L1N_SAMPLES = GSP_STATISTICS_BUS_U_L1N_SAMPLES, /**< Voltage phase 1 (samples) */
        eIdBUS_U_L1N = GSP_STATISTICS_BUS_U_L1N, /**< Voltage phase 1 (RMS) */
        eIdBUS_F = GSP_STATISTICS_BUS_F, /**< Frequency */
        eIdBUS_ROCOF = GSP_STATISTICS_BUS_ROCOF, /**< Rate Of Change Of Frequency */
        eIdMAINS_U_L1N_SAMPLES = GSP_STATISTICS_MAINS_U_L1N_SAMPLES, /**< Voltage phase 1 (samples) */
        eIdMAINS_U_L2N_SAMPLES = GSP_STATISTICS_MAINS_U_L2N_SAMPLES, /**< Voltage phase 2 (samples) */
        eIdMAINS_U_L3N_SAMPLES = GSP_STATISTICS_MAINS_U_L3N_SAMPLES, /**< Voltage phase 3 (samples) */
        eIdMAINS_U_L12_SAMPLES = GSP_STATISTICS_MAINS_U_L12_SAMPLES, /**< Voltage phase 1 and phase 2 (samples) */
        eIdMAINS_U_L23_SAMPLES = GSP_STATISTICS_MAINS_U_L23_SAMPLES, /**< Voltage phase 2 and phase 3 (samples) */
        eIdMAINS_U_L31_SAMPLES = GSP_STATISTICS_MAINS_U_L31_SAMPLES, /**< Voltage phase 3 and phase 1 (samples) */
        eIdMAINS_U_L1N = GSP_STATISTICS_MAINS_U_L1N, /**< Voltage phase 1 (RMS) */
        eIdMAINS_U_L2N = GSP_STATISTICS_MAINS_U_L2N, /**< Voltage phase 1 (RMS) */
        eIdMAINS_U_L3N = GSP_STATISTICS_MAINS_U_L3N, /**< Voltage phase 1 (RMS) */
        eIdMAINS_U_L12 = GSP_STATISTICS_MAINS_U_L12, /**< Voltage phase 1 and phase 2 (RMS) */
        eIdMAINS_U_L23 = GSP_STATISTICS_MAINS_U_L23, /**< Voltage phase 2 and phase 3 (RMS) */
        eIdMAINS_U_L31 = GSP_STATISTICS_MAINS_U_L31, /**< Voltage phase 3 and phase 1 (RMS) */
        eIdMAINS_F = GSP_STATISTICS_MAINS_F, /**< Frequency */
        eIdMAINS_ROCOF = GSP_STATISTICS_MAINS_ROCOF, /**< Rate Of Change Of Frequency */
        eIdMAINS_ASYM_U = GSP_STATISTICS_MAINS_ASYM_U, /**< Voltage asymmetric */
        eIdNP_ASYM_I = GSP_STATISTICS_NP_ASYM_I, /**< Current asymmetric */
        eIdNP_I_L1 = GSP_STATISTICS_NP_I_L1 /**< Current phase 1 */
    } EStatisticId_t;

    /**
     * @brief Selection Values
     *
     * Constants for Selection Array \n
     * Sample: ASelection_t[ eSlct_U_L3N_RMS ] = TRUE;
     *
     * @see ASelection_t
     */
    /** !!! do not change the order !!! */
    typedef enum
    {
        eSlct_U_L1N_RMS = 0, /**< Voltage U1 */
        eSlct_U_L2N_RMS = 1, /**< Voltage U2 */
        eSlct_U_L3N_RMS = 2, /**< Voltage U3 */
        eSlct_U_L1L2_RMS = 3, /**< Voltage U12 */
        eSlct_U_L2L3_RMS = 4, /**< Voltage U23 */
        eSlct_U_L3L1_RMS = 5, /**< Voltage U31 */
        eSlct_I_L1_RMS = 6, /**< Current I1 */
        eSlct_I_L2_RMS = 7, /**< Current I2 */
        eSlct_I_L3_RMS = 8, /**< Current I3 */
        eSlct_I_N_RMS = 9, /**< Current IN */
        eSlct_P_SUM = 10, /**< summary real power */
        eSlct_P_L1 = 11, /**< real power*/
        eSlct_P_L2 = 12, /**< real power*/
        eSlct_P_L3 = 13, /**< real power */
        eSlct_S_SUM = 14, /**< summary apparent power*/
        eSlct_S_L1 = 15, /**< apparent power*/
        eSlct_S_L2 = 16, /**< apparent power*/
        eSlct_S_L3 = 17, /**< apparent power*/
        eSlct_Q_SUM = 18, /**< summary reactive power */
        eSlct_Q_L1 = 19, /**< reactive power*/
        eSlct_Q_L2 = 20, /**< reactive power*/
        eSlct_Q_L3 = 21, /**< reactive power*/
        eSlct_FREQUENCY = 22, /**< Frequency */
        eSlct_ROCOF = 23, /**< rate of change frequency */
        eSlct_ASYM_U = 24, /**< asymmetric voltage */
        eSlct_ASYM_I = 25, /**< asymmetric current */
        eSlct_I_RMS = 26, /**< */
        eSlct_ALARMS = 27, /**< */
        eSlct_DIS = 28, /**< */
        eSlctALL = 29 /**< */
    } ESelection_t;

    /**
     * @brief Possible Values for Relay Configuration
     */
    typedef enum
    {
        eOpen = 0, eClosed = 1
    } ERelayConfig_t;

    /**
     * @brief Ids for Harmonics Selection
     */
    typedef enum
    {
        eHidVoltageL1 = GSP_HARMONICS_U_L1,
        eHidVoltageL2 = GSP_HARMONICS_U_L2,
        eHidVoltageL3 = GSP_HARMONICS_U_L3,
        eHidCurrentL1 = GSP_HARMONICS_I_L1,
        eHidCurrentL2 = GSP_HARMONICS_I_L2,
        eHidCurrentL3 = GSP_HARMONICS_I_L3
    } EHarmonicsId_t;

    /**
     * @brief Possible Values Eventinterrupts
     *
     * see attachEvent
     */
    typedef enum
    {
        eEventScopeReady = MIO_EV_SCOPEREADY,
        eEventHarmonicsLimit = MIO_EV_HARMONICS,
        eEventVoltageMin = MIO_EV_U_MIN,
        eEventVoltageMax = MIO_EV_U_MAX,
        eEventCurrentMax = MIO_EV_I_MAX,

        eEventFeedback = MIO_EV_FEEDBACK,
        eEventSyncScope = MIO_EV_SYNCSCOPEREADY
    } EEvent_t;

    /**
     * @brief Possible Values for ErrorInterrupts
     *
     * see attachError
     */
    typedef enum
    {
        /** Module */
        eErrorVectorJump = MIO_E_VECTORJMP,
        eErrorQuPCC = MIO_E_QUPCC,
        eErrorQuGEN = MIO_E_QUGEN,
        eErrorROCOFMax = MIO_E_ROCOF_MAX,
        eErrorAsymUMax = MIO_E_ASYM_U_MAX,

        /** Channel 1-3, 10, 12-14 */
        eErrorUMin = MIO_E_U_MIN,
        eErrorUMax = MIO_E_U_MAX,
        eErrorTHD_UMAX = MIO_E_THD_U_MAX,
        eErrorFRT = MIO_E_FRT,

        /** Channel 4-6 */
        eErrorIMax = MIO_E_I_MAX,
        eErrorTDD_IMAX = MIO_E_TDD_I_MAX,
        eErrorAsymIMax = MIO_E_ASYM_I_MAX,

        /** Channel 7, 11, 15 */
        eErrorFreqInMin = MIO_E_F_IN_MIN,
        eErrorFreqInMax = MIO_E_F_IN_MAX,
        eErrorFreqMidMin = MIO_E_F_MID_MIN,
        eErrorFreqMidMax = MIO_E_F_MID_MAX,
        eErrorFreqOutMin = MIO_E_F_OUT_MIN,
        eErrorFreqOutMax = MIO_E_F_OUT_MAX,

        /** Channel 17,19 */
        eErrorSyncAlarm = MIO_E_SYNCALARM
    } EGspError_t;

    /**
     * @brief State of Module
     */
    typedef enum
    {
        eStateRun = GSP_STATE_RUN,
        eStateForceRelay = GSP_STATE_FORCERELAY,
        eStateSimulation = GSP_STATE_SIMULATION,
        eStateConfig = GSP_STATE_CONFIG,
        eStateMeasuring = GSP_STATE_MEASURING
    } EState_t;

    /**
     * @brief Possible Values for Limits
     */
    typedef enum
    {
        eTypeUI, eTypeAsymetric, eTypeHarmonics, eTypeROCOF, eTypeVectorJump
    } ELimitType_t;

    /**
     * @brief possible Values for Limit Identifier
     */
    typedef enum
    {
        eIdUndefined = -1,
        /** LimitCfg */
        eIdErrUMin = GSP_ER_U_MIN,
        eIdErrUMax = GSP_ER_U_MAX,
        eIdEvtUMin = GSP_EV_U_MIN,
        eIdEvtUMax = GSP_EV_U_MAX,
        eIdErrIMax = GSP_ER_I_MAX,
        eIdEvtIMax = GSP_EV_I_MAX,
        eIdErrTHD = GSP_ER_THD_MAX,
        eIdErrTDD = GSP_ER_TDD_MAX,
        /** Asym */
        eIdErrAsymUMax = GSP_ER_ASYM_U_MAX,
        eIdErrAsymIMax = GSP_ER_ASYM_I_MAX,
        /** Harmonics */
        eIdHarmonics_U = GSP_HARMONICS_U,
        eIdHarmonics_I = GSP_HARMONICS_I
    } ELimitId_t;

    /**
     * @brief Ids for Frequency Window
     */
    typedef enum
    {
        eFreqIN = GSP_F_IN, eFreqMID = GSP_F_MID, eFreqOUT = GSP_F_OUT
    } EFrequencLimit_t;

    /**
     * @brief Modes of Module
     *
     * Can only be set during Bootup!
     */
    typedef enum
    {
        eModeOpen = GSP_M_OPEN,
        eMode2WIRE1PHASE = GSP_M_2WIRE1PHASE,
        eMode2WIRE2PHASE = GSP_M_2WIRE2PHASE,
        eMode3WIRE2PHASE = GSP_M_3WIRE2PHASE,
        eMode3WIRE3PHASE = GSP_M_3WIRE3PHASE,
        eMode4WIRE3PHASELL = GSP_M_4WIRE3PHASELL,
        eMode4WIRE3PHASELN = GSP_M_4WIRE3PHASELN,
        eModeEQUALLYLOADED = GSP_M_EQUALLYLOADED,
        eModeARON = GSP_M_ARON,
        eModeUNBALANCEDLOADED = GSP_M_UNBALANCEDLOADED,
        eModeDISABLED = GSP_M_DISABLED,
        eModeMEASURE = GSP_M_MEASURE,
        eModeCALCULATE = GSP_M_CALCULATE,
        eModeDO_PULSE = GSP_M_DO_PULSE,
        eModeDO_CONTINUOUS = GSP_M_DO_CONTINUOUS,
        eModeDI_FEEDBACK = GSP_M_DI_FEEDBACK,
        eModeDI_MANUALSYNC = GSP_M_DI_MANUALSYNC,
        eModeDI_BREAK = GSP_M_DI_BREAK
    } EMode_t;

    /**
     * @brief Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    GSP274();

    /**
     * @brief Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GSP274(UINT32 ui32CardNumber);

    /**
     * @brief Destructor
     */
    virtual ~GSP274();

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/
    /**
     * @brief Attach to Event Interrupt
     *
     * @param pSession - Event Session from System
     * @param pListener - Object which contains callback method
     * @param eEvent - see eEventXXXX for possible Values
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachEvent(EventSession *pSession, BasicEventListener *pListener, EEvent_t eEvent,
            UINT8 ui8Channel = 0);

    /**
     * @brief Attach to Error Interrupt
     *
     * @param pSession - Error Session from System
     * @param pListener - Object which contains callback method
     * @param eError - see eErrorXXXX for possible Values
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when attaching error to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachError(ErrorSession *pSession, BasicErrorListener *pListener, EGspError_t eError,
            UINT8 ui8Channel = 0);
    /**
     * DO COMMANDS
     */

    /**
     * @brief Delete Alarmhistory
     * possible in state eStateConfig
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID deleteHistory(VOID);

    /**
     * @brief Read Statistic values
     *
     * @param ui32Index - first Value to read
     * @param ui32Count - number of values to read
     * @param pStat - pointer to Variables
     *
     * @returns the pStat pointer with data
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GSP274::SDisplayStatistics_t* displayStatistics(UINT32 ui32Index, UINT32 ui32Count, SDisplayStatistics_t* pStat);

    /**
     * @brief Reset Statistic of Module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetStatistics(VOID);

    /**
     * @brief Export Scope in Comtrade-Format
     *
     * @param pch8Filename - File for export
     * @param ui32Timeout - timout in s for scope lock (≤ 100 s)
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScope(CHAR8* pch8Filename, UINT32 ui32Timeout, UINT32 ui8Channel);

    /**
     * @brief Export Scope in Comtrade-Format
     * This function is non blocking
     * N.B. Use getExportScopeProgress to get status until status = PROGRESS_DONE (this will automatically release lock handle)
     *
     * @param pch8Filename - File for export
     * @param ui32Timeout - timout in s for scope lock (≤ 100 s)
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScopeNB(CHAR8* pch8Filename, UINT32 ui32Timeout, UINT32 ui8Channel);


    /**
     * Export the scope data progress (To be used when export is running in a background task)
     * Function releases scope lock handle when scope files is exported
     * @returns a pointer to the scope export progress structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    MIO_PROGRESS_R* getExportScopeProgress(UINT32 ui8Channel);

    /**
     * @brief Read INI File to configure Module
     *
     * @param pch8Filename - Filename of INI-File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID processIniFile(CHAR8 pch8Filename);

    /**
     * @brief Force Relay
     *
     * \note Only Possible in eStateForceRelay
     *
     * @param ui8Channel - selected Channel (10 or 11)
     * @param b8Value - FALSE = OFF, TRUE = ON
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID forceRelay(UINT8 ui8Channel, BOOL8 b8Value);

    /**
     * @brief Reset Relay Output
     *
     * @param ui8Channel - selected Channel (10 or 11)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetRelay(UINT8 ui8Channel);

    /**
     * @brief Start Scope
     *
     * @param Channel  GSP_SCOPE_MODULE is only supported
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID triggerScope(UINT32 ui8Channel);

    /**
     * @brief Get Selected Count of Alarms
     *
     * @param handle - value from takeHistoryLock
     * @param ui32Index - Start Index
     * @param ui32Count - number of entries
     * @param pValue - pointer to variable
     * @param ui32Timeout - timout in s for scope lock (≤ 100 s)
     *
     * @returns TRUE  - success
     *          FALSE - failed
     */
    VOID getAlarmHistory(UINT32 ui32Index, UINT32 ui32Count, UINT32 ui32Timeout,
            SAlarmHistory_t *pValue);

    /**
     * @brief Set EnergyCounter
     *
     * Values are from Type REAL64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(SEnergyR_t *pValue);

    /**
     * @brief Read EnergyCounter
     *
     * Values are from Type REAL64
     *
     * @return a pointer EnergyCounter
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SEnergyR_t* getEnergy(VOID);

    /**
     * @brief Read Eventstate of Module
     *
     * @param ui8Channel - selected Channel (0-6) 0=Module
     * @return event state
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    EEvent_t getEvent(UINT8 ui8Channel);

    /**
     * @brief Read Harmonics
     *
     * @param eId - see eHidXXXX
     * @return pointer to harmonics data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SHarmonics_t* getHarmonics(EHarmonicsId_t eId);

    /**
     * @brief Read available Statistics
     *
     * @return statistics counter
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getStatisticsCounter(VOID);

    /**
     * @brief Read Phaseangles
     *
     * @return a pointer to the phase angle data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SPhaseAngels_t* getPhaseAngles(VOID);

    /**
     * @brief Read Errors during initialization
     *
     * @param ui8Channel - selected Channel
     * @return preinit error information
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPreInitErrors(UINT8 ui8Channel);

    /**
     * @brief Read Events during initialization
     *
     * @param ui8Channel - selected Channel
     * @return preinit events information
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPreInitEvents(UINT8 ui8Channel);

    /**
     * @brief write actual QU-Limit
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setQULimit(SQuLimit_t *psValue);

    /**
     * @brief read actual QU-Limit
     *
     * @return a pointer to the actual QU-Limit
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SQuLimit_t* getQULimit(VOID);

    /**
     * @brief Read Base Config of Module
     *
     * @returns a pointer to the base configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SBaseConfig_t* getBaseConfig(VOID);

    /**
     * @brief Set Configuration of Relaydefault
     *
     * @param eValue - new Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRelayConfig(ERelayConfig_t eValue);

    /**
     * @brief get Configuration of Relay Default
     *
     * @return relay configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    ERelayConfig_t getRelayConfig(VOID);

    /**
     * @brief Set configuration of Scope
     *
     * @param sValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setScopeConfig(SScopeConfig_t *sValue);

    /**
     * @brief Get configuration of Scope
     *
     * @return a pointer to the scope configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeConfig_t* getScopeConfig(VOID);

    /**
     * @brief Read configuration of RunThrough
     *
     * @return Run through configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getRunThroughConfig(VOID);

    /**
     * @brief Read values from Scope
     * N.B. The last value must be read in order to release the scope lock!
     *
     * @param ui32Index - first Values (0 - GMP_SCOPE_MAXVALIDX)
     * @param ui32Timeout - timout in s for scope lock (≤ 100 s)
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     *
     * @returns a pointer to the scope values structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeData_t* getScopeValues(UINT32 ui32Index, UINT32 ui32Timeout, UINT32 ui8Channel);

    /**
     * @brief Read actual Scope State
     *
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     * @return a pointer to the scope state data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SScopeState_t* getScopeState(UINT32 ui8Channel);

    /**
     * @brief Read defined values
     *
     * @see ESelection_t
     *
     * @param paSelection
     * @return a pointer to the selected value data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SValues_t* getSelectedValues(ASelection_t *paSelection);

    /**
     * @brief Set State Module
     *
     * @see eState_t
     *
     * @param eState - value for State
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setState(EState_t eState);

    /**
     * @brief Get State Module
     *
     * @see eState_t
     *
     * @return the state of the module
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    EState_t getState(VOID);

    /**
     * @brief Read Statistics
     *
     * @see EStatisticId_t
     *
     * @param eId - identifier
     * @return a pointer to the statistics data
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SStatistic_t* getStatistics(EStatisticId_t eId);

    /**
     * @brief Read switch counter of Relays
     *
     * @return a pointer to the switch data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSwitchCount_t* getSwitchCount(VOID);

    /**
     * @brief Read all measured values
     *
     * @returns a pointer to the measured data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SValues_t* getMeasuredValues(VOID);

    /**
     * @brief Get Vectordigram
     *
     * @returns a pointer to the vector diagram data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SVectorDiagram_t* getVectorDiagram(VOID);

    /**
     * @brief Set ValueTable for FRT
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFaultRideThrough(SFaultRideThrough_t *psValue);

    /**
     * @brief Get actual Valuetable for FRT
     *
     * @return a pointer to the fault ride through configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SFaultRideThrough_t* getFaultRideThrough(VOID);

    /**
     * @brief Set SimulationValues
     *
     * @param psData - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSimulationData(SSimulationData_t *psData);

    /**
     * @brief get SimulationValues
     *
     * @returns a pointer to the simulations data
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSimulationData_t* getSimulationData(VOID);

    /**
     * @brief Set Limitconfiguration
     *
     * @param eLimit - see eTypeXXX
     * @param psValue - pointer to variable
     * @param eId - see eIdXXXX
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if parameter is invalid
     */
    VOID setLimit(ELimitType_t eLimit, SLimit_t *psValue, ELimitId_t eId = eIdUndefined);

    /**
     * @brief Read Limitconfiguration
     *
     * @param eLimit - see eTypeXXX
     * @param eId - see eIdXXXX
     * @return a pointer to the limit configuration structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SLimit_t* getLimit(ELimitType_t eLimit, ELimitId_t eId = eIdUndefined);

    /**
     * @brief Set Limitconfiguration of Frequencywindow
     *
     * @param psValue - pointer to variable
     * @param eId - see eFreqXXXX
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFrequencyLimit(SFrequencyLimit_t *psValue, EFrequencLimit_t eId);

    /**
     * @brief get Limitconfiguration of Frequencywindow
     *
     * @param eId - see eFreqXXXX
     * @returns a pointer to the frequencywindow limitconfiguration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SFrequencyLimit_t* getFrequencyLimit(EFrequencLimit_t eId);

    /**
     * @brief Get one single Channel as Instance
     *
     * @param ui32Channel - Channelnumber (17-24)
     * @returns a pointer to the digital channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    DigitalChannel* getDigitalChannel(UINT32 ui32Channel);

    /**
     * @brief Read IEC Values
     *
     * @returns a pointer to the IEC value data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SIECValues_t* getIecValues(VOID);

protected:

    /**
     * Module has 4 Digital Output Channels
     * and 4 Digital Input Channels
     */
    DigitalChannel m_Output[4];
    DigitalChannel m_Input[4];

    /**
     * @brief Lock Reading from other Applications
     *
     * @param ui32Timeout - timout in s (≤ 100 s)
     * @param pValue - handle Data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID takeHistoryLock(UINT32 ui32Timeout);

    /**
     * @brief Unlock Reading
     *
     * @param handle - Value from takeHistoryLock
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID giveHistoryLock(VOID);

    /**
     * @brief Lock Reading from other Applications
     *
     * @param ui32Timeout - timout in s (≤ 100 s)
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID takeScopeLock(UINT32 ui32Timeout, UINT32 ui8Channel);

    /**
     * @brief Unlock Reading
     *
     * @param Channel GSP_SCOPE_MODULE, GSP_SCOPE_SYNC1, GSP_SCOPE_SYNC2
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID giveScopeLock(UINT32 ui8Channel);

    /**
     * @brief get Type of Module
     *
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_GSP274;
    }
private:
    /**
     * Initialize all values at construction.
     */
    VOID init(VOID);

    SLimit_t m_Limit;
    SEnergyR_t m_Energy;
    SQuLimit_t m_QuLimit;
    LockHandle_t m_ScopeLock;
    SIECValues_t m_IECValues;
    SStatistic_t m_Statistic;
    SHarmonics_t m_Harmonics;
    SScopeData_t m_ScopeData;
    LockHandle_t m_HistoryLock;
    SBaseConfig_t m_BaseConfig;
    SScopeState_t m_ScopeState;
    SValues_t m_MeasuredValues;
    SValues_t m_SelectedValues;
    SSwitchCount_t m_SwitchCount;
    SPhaseAngels_t m_PhaseAngles;
    SScopeConfig_t m_ScopeConfig;
    MIO_PROGRESS_R m_ExportProgress;
    SVectorDiagram_t m_VectorDiagram;
    SSimulationData_t m_SimulationData;
    SFrequencyLimit_t m_FrequencyLimit;
    SFaultRideThrough_t m_FaultRideThroughCfg;
};

#endif /** GSP274_HPP_ */
