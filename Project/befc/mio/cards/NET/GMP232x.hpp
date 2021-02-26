/**
 ********************************************************************************
 * @file     GMP232x.hpp
 * @author   Søren Vejlgaard Vedstesen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Sep 17, 2015 10:38:48 AM $
 *
 * @brief    Implementation of grid measurement and protection module GMP232x
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#ifndef GMP232x_HPP_
#define GMP232x_HPP_

#define GMP_OVERHEAD	         5		/**< Number of extra bytes in each request */
#define GMP_RUNBEFOREVALIDDATA   100	/**< Number of data before data is valid */
#define GMP_MAX_NO_SAMPLES       33		/**< Max buffer size of raw data buffer */
#define GMP_SCOPELOCKTIMEOUT	 10		/**< Time before scope lock expires [s] */
#define GMP_HISTORYLOCKTIMEOUT	 10		/**< Time before scope lock expires [s] */
#define GMP232X_NB_STATISTICS	 135	/**< Maximum number of statistics values */

#define GMP232X_CHECKSUMLENGTH	 16		/**< Length of checksum */


/**********************************************************************
 * system includes
 **********************************************************************/
#include <gmp232x.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicMixedModule.hpp"
#include "../../common/base/DigitalChannel.hpp"

/**
 * @brief Module for Net Measuering and Analysis GMP232
 *
 */
class GMP232x: public BasicMixedModule
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

    /**
     * Configuration of Raw Data buffer
     *
     * sSampleData : Raw Data buffer
     */
    typedef GMP232X_SAMPLE_VAL SRawDataBuffer_t[GMP_MAX_NO_SAMPLES];
    /**
     * Configuration of Raw Data Samples
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
     * Possible Values for getEvent(...) and
     * attachEvent
     */
    typedef enum
    {
        eEventAnyZeroCrossing = MIO_EV_ANYZERO, /**< Any voltage zero crossing */
        eEventL1ZeroCrossing = MIO_EV_P1ZERO, /**< Phase 1 voltage positive zero crossing */
        eEventScopeReady = MIO_EV_SCOPE, /**< Scope event */
        eEventHarmonicsU = MIO_EV_HARM_U, /**< Voltage harmonics */
        eEventVoltageAsym1 = MIO_EV_U_ASYM1, /**< Voltage asymmetry 1 */
        eEventVoltageAsyn2 = MIO_EV_U_ASYM2, /**< Voltage asymmetry 2 */
        eEventVoltageTHD = MIO_EV_THD_U, /**< Voltage THD */
        eEventCurrentAsym1 = MIO_EV_I_ASYM1, /**< Current asymmetry 1 */
        eEventCurrentAsym2 = MIO_EV_I_ASYM2, /**< Current asymmetry 2 */
        eEventHarmonicsI = MIO_EV_HARM_I, /**< Current harmonics */
        eEventVectorJump1 = MIO_EV_VECTORJUMP1, /**< Vector jump 1 */
        eEventVectorJump2 = MIO_EV_VECTORJUMP2, /**< Vector jump 2 */
        eEventCurrentTDD = MIO_EV_TDD_I, /**< Current TDD */
        eEventOverCurrent1 = MIO_EV_DIRCURRENT1,/**< Directional overcurrent 1 */
        eEventOverCurrent2 = MIO_EV_DIRCURRENT2,/**< Directional overcurrent 2 */
        eEventRocof = MIO_EV_ROCOF, /**< ROCOF */
        eEventMaxPower1 = MIO_EV_MAX_POWER1, /**< Maximal power 1 */
        eEventMaxPower2 = MIO_EV_MAX_POWER2, /**< Maximal power 2 */
        eEventRefRelay1 = MIO_EV_MANUAL_REL1, /**< State of manual relay 1 */
        eEventRefRelay2 = MIO_EV_MANUAL_REL2, /**< State of manual relay 2 */
    } EGMPxEvent_t;

    /**
     * Possible Values for attachError
     */
    typedef enum
    {
        eErrorQuLimit1 = MIO_E_QU_GEN1, /**< QU limit 1 */
        eErrorQuLimit2 = MIO_E_QU_GEN2, /**< QU limit 2 */
        eErrorULimit1Min = MIO_E_V_LO1, /**< Voltage lower limit 1 */
        eErrorULimit1Max = MIO_E_V_HI1, /**< Voltage upper limit 1 */
        eErrorULimit2Min = MIO_E_V_LO2, /**< Voltage lower limit 2 */
        eErrorULimit2Max = MIO_E_V_HI2, /**< Voltage upper limit 2 */
        eErrorULimit3Min = MIO_E_V_LO3, /**< Voltage lower limit 3 */
        eErrorULimit3Max = MIO_E_V_HI3, /**< Voltage upper limit 3 */
        eErrorUFRT1 = MIO_E_VFRT1, /**< Voltage FRT 1 */
        eErrorUFRT2 = MIO_E_VFRT2, /**< Voltage FRT 2 */
        eErrorUFRT3 = MIO_E_VFRT3, /**< Voltage FRT 3 */
        eErrorUFRT4 = MIO_E_VFRT4, /**< Voltage FRT 4 */
        eErrorILimit1Max = MIO_E_I_HI1,
        eErrorILimit2Max = MIO_E_I_HI2,
        eErrorILimit3Max = MIO_E_I_HI3,
        eErrorFreqLimit1Min = MIO_E_F_LO1, /**< Frequency lower limit 1 */
        eErrorFreqLimit1Max = MIO_E_F_HI1, /**< Frequency upper limit 1 */
        eErrorFreqLimit2Min = MIO_E_F_LO2, /**< Frequency lower limit 2 */
        eErrorFreqLimit2Max = MIO_E_F_HI2, /**< Frequency upper limit 2 */
        eErrorFreqLimit3Min = MIO_E_F_LO3, /**< Frequency lower limit 3 */
        eErrorFreqLimit3Max = MIO_E_F_HI3, /**< Frequency upper limit 3 */
        eErrorFreqFRT1 = MIO_E_FFRT1 /**< Frequency FRT 1 */
    } EGMPxError_t;
    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    GMP232x();

    /**
     * Constructor
     *
     * @param[in] ui32CardNumber - Cardnumber of Module
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GMP232x(UINT32 ui32CardNumber);

    /**
     * Constructor
     *
     * @param[in] ui32CardNumber - Cardnumber of Module
     *
     * @param[in] pMIOSystem - Pointer to the desired IO system
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GMP232x(UINT32 ui32CardNumber, MIOSystem *pMIOSystem);


    /**
     * Destructor
     */
    virtual ~GMP232x();

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/
    /**
     * @param[in] pSession - Event Session from System
     * @param[in] pListener - Object which contains callback method
     * @param[in] eEvent - see eEventXXXX for possible Values
     * @param[in] ui8Channel - selected Channel
     *
     */
    VOID attachGmpEvent(EventSession *pSession, BasicEventListener *pListener, EGMPxEvent_t eEvent,
            UINT8 ui8Channel = 0);

    /**
     * Attach to Error Interrupt
     *
     * @param[in] pSession - Error Session from System
     * @param[in] pListener - Object which contains callback method
     * @param[in] eError - see eErrorXXXX for possible Values
     * @param[in] ui8Channel - selected Channel
     *
     * @returns TRUE - attached
     * @returns FALSE - FAILED
     */
    VOID attachGmpError(ErrorSession *pSession, BasicErrorListener *pListener, EGMPxError_t eError,
            UINT8 ui8Channel = 0);
    /**
     *
     * DO COMMANDS
     *
     */

    /**
     * Read GMP232x module time
     *
     * @returns a pointer to the module time structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    timespec* getModuleTime(VOID);

    /**
     * Write GMP232x module time
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setModuleTime(timespec *Time);

    /**
     * Process Parameter file
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID processParameterFile(VOID);

    /**
     * Read run through mode setting
     * @returns TRUE Card is in RunThrough Mode
     * @returns FALSE Card is not in RunThrough Mode
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL32 getRunThrough(VOID);

    /**
     * Write run through mode setting
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRunThrough(BOOL32);

    /**
     * Reads the events status
     * @returns the event status
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getEventsStatus(VOID);

    /**
     * Writes frequency limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_F_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFrequencyLimit(GMP232X_LIMIT_FREQ *freqLimit, UINT32 limitId);

    /**
     * Reads frequency limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_F_*)
     * @returns a pointer to the frequency limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_FREQ* getFrequencyLimit(UINT32 limitId);

    /**
     * Writes voltage fault ride through limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_VFRT*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setVfrtLimit(GMP232X_LIMIT_VFRT *VfrtLimit, UINT32 limitId);

    /**
     * Reads voltage fault ride through limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_VFRT*)
     * @returns a pointer to the voltage fault ride through limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_VFRT* getVfrtLimit(UINT32 limitId);

    /**
     * Writes frequency fault ride through limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_FFRT*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFfrtLimit(GMP232X_LIMIT_FFRT *FfrtLimit, UINT32 limitId);

    /**
     * Reads frequency fault ride through limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_FFRT*)
     * @returns a pointer to the frequency fault ride through limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_FFRT* getFfrtLimit(UINT32 limitId);

    /**
     * Writes voltage limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_V_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setVoltageLimit(GMP232X_LIMIT_V *VoltageLimit, UINT32 limitId);

    /**
     * Reads voltage limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_V_*)
     * @returns a pointer to the voltage limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_V* getVoltageLimit(UINT32 limitId);

    /**
     * Writes QU limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_QULIMIT*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setQULimit(GMP232X_LIMIT_QU *QULimit, UINT32 limitId);

    /**
     * Reads QU limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_QULIMIT*)
     * @returns a pointer to the QU limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_QU* getQULimit(UINT32 limitId);

    /**
     * Writes Vector Jump limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_VECTORJUMP*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setVectorJumpLimit(GMP232X_LIMIT_VECTORJUMP *VectorJumpLimit, UINT32 limitId);

    /**
     * Reads Vector Jump limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_VECTORJUMP*)
     * @returns a pointer to the Vector Jump limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_VECTORJUMP* getVectorJumpLimit(UINT32 limitId);

    /**
     * Writes Harmonic limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_HARM_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setHarmonicLimit(GMP232X_LIMIT_HARMONICS *HarmonicLimit, UINT32 limitId);

    /**
     * Reads Harmonic limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_HARM_*)
     * @returns a pointer to the Harmonic limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_HARMONICS* getHarmonicLimit(UINT32 limitId);

    /**
     * Writes Current limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_I_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setCurrentLimit(GMP232X_LIMIT_I *CurrentLimit, UINT32 limitId);

    /**
     * Reads Current limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_I_*)
     * @returns a pointer to the Current limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_I* getCurrentLimit(UINT32 limitId);

    /**
     * Writes total harmonic disturbance or total demand distortion limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_I_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setThdTddLimit(GMP232X_LIMIT_THDTDD *ThdTddLimit, UINT32 limitId);

    /**
     * Reads total harmonic disturbance or total demand distortion limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_I_*)
     * @returns a pointer to the THD or TDD limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_THDTDD* getThdTddLimit(UINT32 limitId);

    /**
     * Writes asymmetry limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_ASYM_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setAsymmetryLimit(GMP232X_LIMIT_ASYM *AsymmetryLimit, UINT32 limitId);

    /**
     * Reads asymmetry limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_ASYM_*)
     * @returns a pointer to the asymmetry limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_ASYM* getAsymmetryLimit(UINT32 limitId);

    /**
     * Writes rocof limit
     * @param[in] limitId - Specify the ID of the limit to be written (MIO_CMD_GMP232X_SETLIMIT_ROCOF)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRocofLimit(GMP232X_LIMIT_ROCOF *RocofLimit);

    /**
     * Reads asymmetry limit
     * @param[in] limitId - Specify the ID of the limit to be read (MIO_CMD_GMP232X_SETLIMIT_ROCOF)
     * @returns a pointer to the asymmetry limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_ROCOF* getRocofLimit(VOID);

    /**
     * Writes max power limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_MAX_POWER*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMaxPowerLimit(GMP232X_LIMIT_MAX_POWER *MaxPowerLimit, UINT32 limitId);

    /**
     * Reads max power limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_MAX_POWER*)
     * @returns a pointer to the max power limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_MAX_POWER* getMaxPowerLimit(UINT32 limitId);

    /**
     * Writes reverse power limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_REVERSE_POWER*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReversePowerLimit(GMP232X_LIMIT_REVERSE_POWER *ReversePowerLimit, UINT32 limitId);

    /**
     * Reads reverse power limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_REVERSE_POWER*)
     * @returns a pointer to the reverse power limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_REVERSE_POWER* getReversePowerLimit(UINT32 limitId);

    /**
     * Writes current direction limit
     * @param[in] limitId - Specify the ID of the limit to be written (GMP232X_LIM_DIR_CURRENT*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setCurrentDirectionLimit(GMP232X_LIMIT_DIR_CURRENT *CurrentDirectionLimit, UINT32 limitId);

    /**
     * Reads current direction limit
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIM_DIR_CURRENT*)
     * @returns a pointer to the current direction limit structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_DIR_CURRENT* getCurrentDirectionLimit(UINT32 limitId);

    /**
     * Reads limit status
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIMIT_STATE_*)
     * @returns the limit status
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getLimitStatus(UINT32 limitId);

    /**
     * Reads the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is half grid cycle (T/2) structure
     * @param[in] limitId - Specify the ID of the limit to be read (GMP232X_LIMIT_STATE_*)
     * @returns a pointer to data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_FRMS_FCS_VALUES* getFrms_Fcs(VOID);

    /**
     * Reads the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is continuous per sample structure
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_FRMS_FCC_VALUES* getFrms_Fcc(VOID);

    /**
     * Reads the True RMS values, RMS window length is half cycle (T), calculation cycle is half grid cycle (T/2) structure
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_TRMS_HCS_VALUES* getTrms_Hcs(VOID);

    /**
     * Reads the True RMS values, RMS window length is half cycle (T), calculation cycle is continuous per sample structure
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_TRMS_HCC_VALUES* getTrms_Hcc(VOID);

    /**
     * Reads the Power calculation structure of the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is half grid cycle (T/2)
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_POWERS_FRMS_FCS* getPowerFrms_Fcs(VOID);

    /**
     * Reads the Power calculation structure of the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is continuous per sample
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_POWERS_FRMS_FCC* getPowerFrms_Fcc(VOID);

    /**
     * Reads the Power calculation structure of the True RMS values, RMS window length is half cycle (T), calculation cycle is half grid cycle (T/2)
     * @returns a pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_POWERS_TRMS_HCS* getPowerTrms_Hcs(VOID);

    /**
     * Reads the Power calculation structure of the True RMS values, RMS window length is half cycle (T), calculation cycle is continuous per sample
     * @returns the pointer to the data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_POWERS_TRMS_HCC* getPowerTrms_Hcc(VOID);

    /**
     * Reads the Phase reference values
     * @returns a pointer to the phase reference structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_PHASEREF* getPhaseReferance(VOID);

    /**
     * Reads the Phase values
     * @returns a pointer to the phase structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_PHASE* getPhase(VOID);

    /**
     * Reads the Rate of change of frequency rotation direction
     * @returns a pointer to the rocof rotation direction structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_ROCOF_ROTDIR* getRocofRotDir(VOID);

    /**
     * Reads the Power factor
     * @returns a pointer to the Power factor structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_POWERFACTOR* getPowerFactor(VOID);

    /**
     * Reads the asymmetric data values
     * @returns the pointer to the asymmetric data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_ASYM* getAsym(VOID);

    /**
     * Reads the symmetric components values
     * @returns a pointer to the symmetric components structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SYMCOMPONENTS* getSymComponents(VOID);

    /**
     * Writes energy data with UINT64 values as input
     * @param[in] energyData	Pointer to energy data structure
     * @param[in] SourceSelect	Type selector TRMS or FRMS (GMP232X_SOURCE_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(GMP232X_ENERGY* energyData, UINT32 SourceSelect);

    /**
     * Reads the energy data
     * @param[in] SourceSelect	Type selector TRMS or FRMS; one of GMP232X_SOURCE_*
     * @returns a pointer to the energy data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_ENERGY* getEnergy(UINT32 SourceSelect);

    /**
     * Writes the scope configuration
     * @param[in] ScopeCfg - Scope configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setScopeConfig(GMP232X_SCOPE_CONFIG* ScopeCfg);

    /**
     * Reads the scope configuration
     * @returns the pointer to the scope configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SCOPE_CONFIG* getScopeConfig(VOID);

    /**
     * Trigger the scope logger manually
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID TriggerScope(VOID);

    /**
     * Export the scope data to file in Comtrade-Format (Automatically or manual scope trigger is needed before exporting data)
     * This function is a blocking function and returns when the files has been written.
     *
     * @param[in] pch8Filename - File for export
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScope(CHAR8* pch8Filename);

    /**
     * Export the scope data to file in Comtrade-Format (Automatically or manual scope trigger is needed before exporting data)
     * This function is non blocking
     * N.B. Use getExportScopeProgress to get status until status = PROGRESS_DONE (this will automatically release lock handle)
     *
     * @param[in] pch8Filename - File for export
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID exportScopeNB(CHAR8* pch8Filename);

    /**
     * Export the scope data progress (To be used when export is running in a background task)
     * Function releases scope lock handle when scope files is exported
     *
     * @returns a pointer to the scope export progress structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    MIO_PROGRESS_R* getExportScopeProgress(VOID);

    /**
     * Read the scope data (Automatically or manual scope trigger is needed before exporting data)
     * N.B. The last value must be read in order to release the scope lock!
     *
     * @param[in] ui32Index - Index First scope value to be read [0-GMP232X_SCOPE_MAXVALIDX] (0, 25, 50 ... 61400, 61425)
     * 				  A maximum of 25 recordings can be returned in one reading (NB: Last reading returns only 15 channels).
     * @param[in] ui32Timeout - timout in s for scope lock (≤ 100 s)
     *
     * @returns a pointer to the read scope data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SCOPE_DATA* exportScopeData(UINT32 ui32Index, UINT32 ui32Timeout);

    /**
     * Read the scope state (Used for testing if a scope has been triggered and which event triggered the scope recording)
     *
     * @returns a pointer to the read scope state structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SCOPE_STATE* getScopeState(VOID);

    /**
     * Read the hammonic values
     * @param[in] harmonicsId - Harmonics identifier to be read (GMP232X_HARMONICS_U* or GMP232X_HARMONICS_I*)
     * @param[in] indexStart - Begin index (inclusive); [0 - (GMP232X_MAX_HARMONICS - 1)]
     * @param[in] indexEnd - End index (inclusive); [0 - (GMP232X_MAX_HARMONICS - 1)]
     * @returns a pointer to the read hammonic data array structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_HARMONICS* getHarmonics(UINT32 harmonicsId, UINT32 indexStart, UINT32 indexEnd);

    /**
     * Set the GMP232x module state
     * @param[in] state - Module state to be set (one of GMP232X_STATE_*)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setModuleState(UINT32 state);

    /**
     * Reads the GMP232x module state
     * @returns the Current module state
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getModuleState(VOID);

    /**
     * Write the sample configuration
     * @param[in] sampleCfg - Sample configuration to be set
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSampleCfg(GMP232X_SAMPLE_CONFIG *sampleCfg);

    /**
     * Reads the sample configuration
     * @returns a pointer to the sample configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SAMPLE_CONFIG* getSampleCfg(VOID);

    /**
     * Reads the raw data sample values
     * This function must be executed every 1ms, to keep data continuous.
     * @returns the raw data sample structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SRawDataSamples_t* getRawDataSamples(VOID);

    /**
     * Reads the last raw data sample values
     * @returns a pointer to the raw data sample structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SAMPLE_VAL* getLastDataSample(VOID);

    /**
     * Writes the inhibit bit configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
	VOID setInhibitCfg(GMP232X_LIMIT_MASK *inihibitCfg);

    /**
     * Reads the inhibit bit configuration
     * @returns a pointer to the inhibit bit configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
	GMP232X_LIMIT_MASK* getInhibitCfg(VOID);

    /**
     * Read the hammonic values
     * @param[in] AlarmIdx - Alarm index to return
     * @param[in] nbEntries - Number of items to return (number of elements in the array HistoryData.
     * @returns a pointer to the read hammonic data array structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_HISTORY_ENTRY* getAlarmHistory(UINT32 AlarmIdx, UINT32 nbEntries);

    /**
     * Delete the alarm history list
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID deleteAlarmHistory(VOID);

    /**
     * Write the module configuration (Configuration can only be changed in config mode)
     * @param[in] moduleCfg - module configuration to be set
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setModuleCfg(GMP232X_CONFIG *moduleCfg);

    /**
     * Reads the module configuration
     * @returns a pointer to the module configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_CONFIG* getModuleCfg(VOID);

    /**
     * Write the simulation data
     * @param[in] simData - Simulation values data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSimData(GMP232X_SIMDATA *simData);

    /**
     * Reads the simulation data
     * @returns a pointer to the simulation data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SIMDATA* getSimData(VOID);

    /**
     * Reads the statistics data
     * @param[in] dataPointId - Data point ID (GMP232X_STATISTICS_*)
     * @returns a pointer to the statistics data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_STATISTIC* getStatistics(UINT32 dataPointId);

    /**
     * Reads the maximum number of statistics data types
     * @returns the number of statistics data points
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getStatisticsNumber(VOID);

    /**
     * Reads the statistics data
     * @param[in] StartIdx - Identifier of the data point to read
     * @param[in] nbDispStatData - Number of statistics data points to read
     * @param[in] pStat - pointer to Variables
     *
     * @returns the pStat pointer with data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_STATISTIC* getStatisticsDisplay(UINT32 StartIdx, UINT32 nbDispStatData, GMP232X_STATISTIC* pStat);

    /**
     * Resets the statistics data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID ResetStatistics(VOID);

    /**
     * Write the module configuration
     * @param[in] relayCfg - Relay default state to be set; 0 or 1
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRelayCfg(UINT32 relayCfg);

    /**
     * Reads the relay configuration
     * @returns the relay default state; 0 or 1
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getRelayCfg(VOID);

    /**
     * Force the relay value (Only allowed in simulation mode)
     * @param[in] setState - State to set the relay (0 or 1)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID forceRelay(UINT32 setState);

    /**
     * Reset the relay state (Tripped by grid event)
     * @param[in] Channel - Relay channel; (12 = Relay 1, 13 = Relay 2)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetRelay(UINT32 Channel);

    /**
     * Reads the switch count for the relays on the module
     * @returns a pointer to the switch count data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_SWITCHCOUNT* getSwitchCountRelays(VOID);

    /**
     * Reads the optimized variant with phi values for U and I
     * @returns a pointer to the phi value data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_PHASE_UI_S* getPhase_UI_S(VOID);

    /**
     * Reads a collection of relevant values regarding relevant symmetric components
     * @returns a pointer to the Symmetric components data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_BULK_SYMCOMPONENTS* getBulkSymComponents(VOID);

    /**
     * Reads a collection of Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is half grid cycle (T/2)
     * @returns a pointer to the FRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_BULK_FRMS_FCS* getBulkFRMS_FCS_Values(VOID);

    /**
     * Reads a collection of Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is continuous per sample
     * @returns a pointer to the FRMS HCC data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_BULK_FRMS_FCC* getBulkFRMS_FCC_Values(VOID);

    /**
     * Reads a collection of True RMS values, RMS window length is half cycle (T), calculation cycle is half grid cycle (T/2)
     * @returns a pointer to the TRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_BULK_TRMS_HCS* getBulkTRMS_HCS_Values(VOID);

    /**
     * Reads a collection of relevant THD and TDD values
     * @returns a pointer to the THD and TDD data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_BULK_THD_TDD* getBulkTHD_TDD_Values(VOID);

    /**
     * Virtual function: Write the relay switch count (only in VIRTUALRW mode)
     * @param[in] switchCount - pointer to the Switch count data structure to be set
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setRelaySwitchCount(GMP232X_SWITCHCOUNT *switchCount);

    /**
     * Virtual function: Write the asymmetric values (only in VIRTUALRW mode)
     * @param[in] asym - pointer to the Asymmetrics data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setAsym(GMP232X_ASYM *asym);

    /**
     * Virtual function: Write the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is continuous per sample (only in VIRTUALRW mode)
     * @param[in] frmsHcc - pointer to the FRMS HCC data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setFRMS_FCC(GMP232X_FRMS_FCC_VALUES *frmsHcc);

    /**
     * Virtual function: Write the Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is half grid cycle (T/2) (only in VIRTUALRW mode)
     * @param[in] frmsHcc - pointer to the FRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setFRMS_FCS(GMP232X_FRMS_FCS_VALUES *frmsHcs);

    /**
     * Virtual function: Write the True RMS values, RMS window length is half cycle (T), calculation cycle is continuous per sample structure values (only in VIRTUALRW mode)
     * @param[in] trmsHcc - pointer to the TRMS HCC data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setTRMS_HCC(GMP232X_TRMS_HCC_VALUES *trmsHcc);

    /**
     * Virtual function: Write the True RMS values, RMS window length is half cycle (T), calculation cycle is half grid cycle values (only in VIRTUALRW mode)
     * @param[in] trmsHcc - pointer to the TRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setTRMS_HCS(GMP232X_TRMS_HCS_VALUES *trmsHcs);

    /**
     * Virtual function: Write the phase values (only in VIRTUALRW mode)
     * @param[in] phase - pointer to the phase data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPhase(GMP232X_PHASE *phase);

    /**
     * Virtual function: Write the phase reference values (only in VIRTUALRW mode)
     * @param[in] phaseRef - pointer to the phase reference data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPhaseRef(GMP232X_PHASEREF *phaseRef);

    /**
     * Virtual function: Write the powerfactor values (only in VIRTUALRW mode)
     * @param[in] powerFactor - pointer to the powerfactor data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPowerFactor(GMP232X_POWERFACTOR *powerFactor);

    /**
     * Virtual function: Write the power Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is continuous per sample values (only in VIRTUALRW mode)
     * @param[in] powers - pointer to the power FRMS HCC data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPowersFRMS_FCC(GMP232X_POWERS_FRMS_FCC *powers);

    /**
     * Virtual function: Write the power Fundamental RMS values, RMS window length is full cycle (T), calculation cycle is half grid cycle (T/2) values (only in VIRTUALRW mode)
     * @param[in] powers - pointer to the power FRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPowersFRMS_FCS(GMP232X_POWERS_FRMS_FCS *powers);

    /**
     * Virtual function: Write the power True RMS values, RMS window length is half cycle (T), calculation cycle is continuous per sample structure values (only in VIRTUALRW mode)
     * @param[in] powers - pointer to the power TRMS HCC data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPowersTRMS_HCC(GMP232X_POWERS_TRMS_HCC *powers);

    /**
     * Virtual function: Write the power True RMS values, RMS window length is half cycle (T), calculation cycle is half grid cycle (T/2) values (only in VIRTUALRW mode)
     * @param[in] powers - pointer to the power TRMS HCS data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setPowersTRMS_HCS(GMP232X_POWERS_TRMS_HCS *powers);

    /**
     * Virtual function: Write the Rate of change of frequency rotation direction rotation direction values (only in VIRTUALRW mode)
     * @param[in] RocofRotDir - pointer to the ROCOF rotation direction data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setRocofRotDir(GMP232X_ROCOF_ROTDIR *rocofRotDir);

    /**
     * Virtual function: Write the symmetric component values (only in VIRTUALRW mode)
     * @param[in] symComponents - pointer to the symmetric component data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID vrw_setSymComponents(GMP232X_SYMCOMPONENTS *symComponents);

    /**
     * Reads the Reads the high resolution timestamp (same as used for sample value timestamps)
     * @returns high resolution timestamp
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT64 getHighResTime(VOID);

    /**
     * Resets a certain mean averager (or multiple)
     * @param[in] averager - Bitmask of the averager(s) to be reset (#GMP232X_AVERAGER1 or similar)
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID RESETAVERAGER(UINT32 averager);

    /**
     * Write the mean value configuration
     * @param[in] MeanCfg - configuration for the mean values
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMeanCfg(GMP232X_MEAN_CONFIG *MeanCfg);

    /**
     * Reads the mean value configuration
     * @returns the mean value configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_MEAN_CONFIG* getMeanCfg(VOID);

    /**
     * Write the relay limit configuration
     * @param[in] LimitRelayCfg - configuration for the relay limits
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRelayLimitCfg(GMP232X_LIMIT_RELAYCFG *LimitRelayCfg);

    /**
     * Reads the relay configuration
     * @returns the relay limit configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_RELAYCFG* getRelayLimitCfg(VOID);

    /**
     * Write the limit scope configuration
     * @param[in] LimitScopeCfg - configuration for the scope limits
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLimitScopeCfg(GMP232X_LIMIT_MASK *LimitScopeCfg);

    /**
     * Reads the limit scope configuration
     * @returns the scope limit configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_CONFIG_EXT* getExtendenCfg(VOID);

    /**
     * Write the extended configuration
     * @param[in] ExtendedCfg - Extended configuration for GMP232x module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setExtendenCfg(GMP232X_CONFIG_EXT *ExtendedCfg);

    /**
     * Reads the extended configuration
     * @returns the extended configuration for the GMP232x module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_MASK* getLimitScopeCfg(VOID);

    /**
     * Sets a relay manually
     * @param[in]  Channel           Relay channel
     * @param[in]  LimitId           Relay identifier to be set; #GMP232X_LIM_2_MANUAL_RELAY1 or similar
     * @param[in]  enable            Flag to enable or disable the relay
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setManualRelay(GMP232X_LIMIT_MASK *LimitId, UINT32 Channel, BOOL32 enable);

    /**
     * Reads the relay manually information
     * @param[in]  Channel           Relay channel
     * @param[in]  LimitId           Relay identifier to be set; #GMP232X_LIM_2_MANUAL_RELAY1 or similar
     * @returns the enabled or disabled information of the relay
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL32 getManualRelay(GMP232X_LIMIT_MASK *limitId, UINT32 Channel);

    /**
     * Generates a configuration checksum for specific values
     * @returns the checksum in 16 bytes long array
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT8* getCfgCheckSum(VOID);

    /**
     * Sets the negative system blocking configuration
     * @param[in]  LimitId         Limit identifier; #GMP232X_LIM_1_NEGSYS or similar
     * @param[in]  NegSys          Negative system settings
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLimitNegSys(GMP232X_LIMIT_MASK *LimitId, GMP232X_LIMIT_NEGSYS *NegSys);

    /**
     * Reads the negative system blocking configuration
     * @param[in]  LimitId           Limit identifier; #GMP232X_LIM_1_NEGSYS or similar
     * @returns the Negative system settings
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_NEGSYS* getLimitNegSys(GMP232X_LIMIT_MASK *LimitId);

    /**
     * Reads the module errors
     * @returns the Errors of the module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getError(VOID);

    /**
     * Reads the Reads the AutoStart setting of the module
     * @returns true if the AutoStart setting is active
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getAutoStart(VOID);

    /**
     * Reads the status of all limits
     * @returns Limit status information; bitmask etc. GMP232X_LIM_1_V_LO1
     * see GMP232X_LIMIT_STATUS for extra info
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GMP232X_LIMIT_STATUS getLimitStatus(VOID);

	/**
	 * Read certain mean value
	 * @note Updated each averager period (dependend on averager configuration)
	 * @param[in]   dataPointIdx    Specific datapoint index (#GMP232X_IDX_U_L1N_INST or similar)
	 * @param[in]  	averager		Identifier of the averaging point (#GMP232X_AVERAGER1 or similar) for dataPointIdx
	 * @returns the average value
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    GMP232X_MEAN* getMeanValue(UINT32 dataPointIdx, UINT32 averager);

	/**
	 * Reads mean values (#GMP232X_AVERAGER3 only) between a certain range, or a single
	 * @note Updated each averager period (dependend on averager configuration)
     * @param[in]  Idx_RangeStart     Begin of range (inclusive); see #GMP232X_IDX_HARM_MEAN_U1_H00
     * @param[in]  NbrOfValues    Number of data points to read, use 1 for a single data point
     * @param[in]  averager           Identifier of the averaging point (one of GMP232X_AVERAGER*)
     * @param[out] dataPoint[]        Where to return the data points read
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getMeanValueRanged(UINT32 Idx_RangeStart, UINT32 averager, UINT32 NbrOfValues, GMP232X_MEAN *dataPoints);

	/**
	 * Read certain mean values, or a single one
	 * @note Updated each averager period (dependend on averager configuration)
     * @param[in]  	NbrOfValues    	Number of data points in reqDataPoint[], use 1 for a single data point
	 * @param[in]  	reqDataPoint[]  Data point request structure, array of size dataPointLength
	 * @param[out] 	dataPoint[]     Where to return the data points read, array of size dataPointLength
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getMeanValueIndexed(UINT32 NbrOfValues, GMP232X_MEAN_REQUEST *reqDataPoint, GMP232X_MEAN *dataPoint);

    /**
     * Function to read all configured mean values for #GMP232X_AVERAGER1 or #GMP232X_AVERAGER2.
     * @note This function does not work for #GMP232X_AVERAGER3, to read mean values for #GMP232X_AVERAGER3 use gmp232x_GetMeanValueRanged() or gmp232x_GetMeanValueIndexed()
     * @param[in]  averager         Identifier of the averaging point
     * @param[out] meanValues[]     Data points read; always provide an array of length #GMP232X_MEAN_MAXCHAN
     * @param[out] NbrOfValues      Number of configured values found; use this when reading the array of meanValues
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getMeanValueConfigured(UINT32 averager, UINT32 *NbrOfValues, GMP232X_MEAN *meanValues);

    /**
     * Read certain statistic value
     * @note Updated dependend on statistic value; uses update rate of corresponding value
     * @param[in]  dataPointIdx[]     Array of data point identifiers (#GMP232X_IDX_U_L1N_INST or similar), array of size dataPointLength
	 * @returns the statistic value
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    GMP232X_STATISTIC* getStatisticValue(UINT32 StatisticId);

    /**
     * Reads statistic values between a certain range, or a single one
     * @note Updated dependend on statistic value; uses update rate of corresponding value
     * @param[in]  Id_RangeStart	Begin of range (inclusive); #GMP232X_IDX_U_L1N_INST or similar
     * @param[in]  NoOfPoints		Number of data points to read, use 1 for a single data point
     * @param[out] dataPoint[]		Where to return the data point read
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getStatisticValuesRanged(UINT32 Id_RangeStart, UINT32 NbrOfValues, GMP232X_STATISTIC *dataPoints);

    /**
     * Read certain statistic values, or a single one
     * @note Updated dependend on statistic value; uses update rate of corresponding value
     * @param[in]  dataPointIdx[]     Array of data point identifiers (#GMP232X_IDX_U_L1N_INST or similar), array of size dataPointLength
     * @param[in]  dataPointLength    Number of data points in dataPointId[], use 1 for a single data point
     * @param[out] dataPoint[]        Where to return the data points read, array of size DataPointLength
	 *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getStatisticValueIndexed(UINT32 *dataPointIdx, UINT32 NbrOfValues, GMP232X_STATISTIC *dataPoints);


    /**
     * Reads various history counter values
     * @param[out] historyCounters  Various counters related to the history
     *
	 * @throws a MIOexception when writing to card fails,
	 * or a MIOexception if pointer to card is invalid
	 */
    VOID getHistoryTotal(GMP232X_HISTORY_COUNT *historyCounters);

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
        return BasicIoModule::TYPE_GMP232x;
    }

private:
    /**
     * Takes the scope lock
     * @param[in] LockTimeout - Timeout when to release the lock timeout in the case of an error when an other process wants the lock; in seconds
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 TakeScopeLock(UINT32 LockTimeout);

    /**
     * Give the scope lock
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID GiveScopeLock(VOID);

    /**
     * Takes the history lock
     * @param[in] LockTimeout - Timeout when to release the lock timeout in the case of an error when an other process wants the lock; in seconds
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 TakeHistoryLock(UINT32 LockTimeout);

    /**
     * Give the history lock
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID GiveHistoryLock(VOID);

    /**
     * Initialize all values at construction.
     */
    VOID init(VOID);

    GMP232X_ASYM m_Asym;
    GMP232X_PHASE m_Phase;
    GMP232X_SIMDATA m_SimData;
    GMP232X_LIMIT_QU m_QuLimit;
    GMP232X_PHASEREF m_PhaseRef;
    GMP232X_CONFIG_EXT m_ExtendedCfg;
    GMP232X_LIMIT_NEGSYS m_NegSys;
    GMP232X_LIMIT_STATUS m_LimitStatus;
    GMP232X_MEAN_CONFIG m_MeanCfg;
    GMP232X_LIMIT_MASK m_LimitScopeCfg;
    GMP232X_LIMIT_RELAYCFG m_LimitRelayCfg;
    GMP232X_FRMS_FCS_VALUES m_Frms_Fcs;
    GMP232X_TRMS_HCS_VALUES m_Trms_Hcs;
    GMP232X_FRMS_FCC_VALUES m_Frms_Fcc;
    GMP232X_TRMS_HCC_VALUES m_Trms_Hcc;
    GMP232X_CONFIG m_moduleCfg;
    GMP232X_SAMPLE_CONFIG m_SampleCfg;
    GMP232X_LIMIT_FREQ m_FreqLimit;
    GMP232X_LIMIT_VFRT m_VfrtLimit;
    GMP232X_LIMIT_FFRT m_FfrtLimit;
    GMP232X_MEAN m_MeanValue;
    GMP232X_STATISTIC m_StatisticPoint;
    GMP232X_LIMIT_MASK m_InhibitCfg;
    GMP232X_PHASE_UI_S m_Phase_UI_S;
    timespec m_ModuleTime;
    GMP232X_LIMIT_ROCOF m_RocofLimit;
    GMP232X_SCOPE_STATE m_ScopeState;
    GMP232X_POWERFACTOR m_PowerFactor;
    UINT32 m_ModuleState;
    GMP232X_ROCOF_ROTDIR m_RocofRotDir;
    GMP232X_SCOPE_CONFIG m_ScopeConfig;
    GMP232X_LIMIT_THDTDD m_ThdTddLimit;
    GMP232X_HISTORY_ENTRY m_HistoryData;
    GMP232X_SCOPE_DATA m_GetScopeData;
    GMP232X_LIMIT_I m_CurrentLimit;
    GMP232X_LIMIT_V m_VoltageLimit;
    GMP232X_LIMIT_MAX_POWER m_MaxPowerLimit;
    GMP232X_LIMIT_HARMONICS m_HarmonicLimit;
    GMP232X_SYMCOMPONENTS m_SymComponents;
    GMP232X_POWERS_FRMS_FCS m_PowerFrms_Fcs;
    GMP232X_POWERS_FRMS_FCC m_PowerFrms_Fcc;
    GMP232X_POWERS_TRMS_HCS m_PowerTrms_Hcs;
    GMP232X_POWERS_TRMS_HCC m_PowerTrms_Hcc;
    MIO_PROGRESS_R m_ExportProgress;
    SRawDataSamples_t m_RawSampleDatas;
    GMP232X_LIMIT_ASYM m_AsymmetryLimit;
    GMP232X_SAMPLE_VAL m_LastSampleData;
    GMP232X_BULK_THD_TDD m_THD_TDD_Values;
    GMP232X_STATISTIC m_StatisticsData;
    GMP232X_ENERGY m_EnergyData;
    GMP232X_BULK_FRMS_FCS m_FRMS_FCS_Values;
    GMP232X_BULK_FRMS_FCC m_FRMS_FCC_Values;
    GMP232X_BULK_TRMS_HCS m_TRMS_HCC_Values;
    GMP232X_LIMIT_VECTORJUMP m_VectorJumpLimit;
    UINT32 m_ScopeLockHandle;
    GMP232X_SWITCHCOUNT m_RelaySwitchCount;
    GMP232X_HISTORY_LOCK m_HistoryLockHandle;
    GMP232X_BULK_SYMCOMPONENTS m_SymComponentsBulk;
    GMP232X_LIMIT_REVERSE_POWER m_ReversePowerLimit;
    GMP232X_LIMIT_DIR_CURRENT m_CurrentDirectionLimit;
    GMP232X_HARMONICS m_Hammonics[GMP232X_MAX_HARMONICS];
    UINT64 m_OldTimeStamp;
    UINT32 m_ui32StartIndex;
    UINT8 m_checkSumPart[GMP232X_CHECKSUMLENGTH];
};

#endif /** GMP232x_HPP_ */
