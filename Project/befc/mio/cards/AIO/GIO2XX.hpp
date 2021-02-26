/**
 ********************************************************************************
 * @file     GIO2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of general purpose input and output module GIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef GIO2XX_HPP_
#define GIO2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include "gio2xx.h"

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicMixedModule.hpp"
#include "../../common/base/DigitalChannel.hpp"

/**
 * @brief General IO Module GIO212
 *
 * Available Channels depending on Configuration \n
 *
 * Input: \n
 * Digital In   : max 12 \n
 * INC-Counter  : max 6 \n
 * Analog In    : max 12 \n
 * -10/+10V, -1/+1V, -100/+100mV, -10/+10mV \n
 * -20/+20mA, 4-20mA \n
 * Thermocouple J, K, T, N, E, R, S, B \n
 * PT100, PT200, PT500, PT1000 \n
 *
 * Output: \n
 * Digital Out  : max 12 \n
 * PWM          : max 12 \n
 * Analog Out   : max 12 \n
 * -10/+10V, 0-10V \n
 * 0-20mA, 4-20mA, 0-2mA, 0-200uA \n
 *
 */
class GIO2XX: public BasicMixedModule
{

public:

    /************************************************************
     *                      CONSTANTS
     ************************************************************/

    /**
     * Values for Analog Input Filter
     */
    typedef enum
    {
        eAnalogFilter_4khz = 0,
        eAnalogFilter_2khz,
        eAnalogFilter_1khz,
        eAnalogFilter_500hz,
        eAnalogFilter_250hz,
        eAnalogFilter_125hz,
        eAnalogFilter_62_5hz,
        eAnalogFilter_31_2hz,
        eAnalogFilter_15_6hz,
        eAnalogFilter_7_8hz,
        eAnalogFilter_3_9hz,
        eAnalogFilter_1_9hz,
        eAnalogFilter_0_97hz,
        eAnalogFilter_0_50hz

    } EAnalogFilter_t;

    /**
     * Values for Digital Input Filter
     */
    typedef enum
    {
        eDigitalFilter_OFF = 0,
        eDigitalFilter_16us,
        eDigitalFilter_32us,
        eDigitalFilter_64us,
        eDigitalFilter_128us,
        eDigitalFilter_256us,
        eDigitalFilter_512us,
        eDigitalFilter_1ms,
        eDigitalFilter_2ms,
        eDigitalFilter_4ms,
        eDigitalFilter_8ms,
        eDigitalFilter_16ms,
        eDigitalFilter_32ms,
        eDigitalFilter_65ms,
        eDigitalFilter_131ms,
        eDigitalFilter_262ms

    } EDigitalFilter_t;

    /**
     * Structure for Limits
     */
    typedef struct
    {
        SINT32 si32Min;
        SINT32 si32Max;
    } SMinMax_t;

    /**
     * Structure for PWM Output
     */
    typedef GIO_DOPULSETIME SPulseConfig_t;

    /************************************************************
     *                      CONSTANTS
     ************************************************************/

    /** Channel Disabled */
    static const UINT32 MODE_DISABLED;
    /** Modes for Digital Input */
    static const UINT32 MODE_DI_TYPE1;
    static const UINT32 MODE_DI_TYPE2;
    static const UINT32 MODE_DI_TYPE3;
    static const UINT32 MODE_DI_SOURCE;
    static const UINT32 MODE_DI_CMP;
    /** Modes for Digital Output */
    static const UINT32 MODE_DO_PUSHPULL;
    static const UINT32 MODE_DO_LOWSIDE;
    static const UINT32 MODE_DO_HIGHSIDE;
    /** Modes for Analog Input */
    static const UINT32 MODE_AI1_10V;
    static const UINT32 MODE_AI1_1V;
    static const UINT32 MODE_AI1_100mV;
    static const UINT32 MODE_AI1_10mV;
    static const UINT32 MODE_AI_RANGE1;
    static const UINT32 MODE_AI_RANGE2;
    static const UINT32 MODE_AI_20mA;
    static const UINT32 MODE_AI_4_20mA;
    /** Modes for Analog Input */
    static const UINT32 MODE_AO_V;
    static const UINT32 MODE_AO_V_EXT;
    static const UINT32 MODE_AO_0_20mA;
    static const UINT32 MODE_AO_4_20mA;
    static const UINT32 MODE_AO_0_2mA;
    static const UINT32 MODE_AO_0_200uA;
    /** Modes for Counter */
    static const UINT32 MODE_CNT_EDGE;
    static const UINT32 MODE_CNT_PERIOD;
    static const UINT32 MODE_CNT_PULSE;
    static const UINT32 MODE_DCNT_EDGE_TRIG;
    static const UINT32 MODE_DCNT_EDGE_RESET;
    static const UINT32 MODE_DCNT_EDGE_GATE;
    static const UINT32 MODE_DCNT_EDGE_DIR;
    /** Modes for Incremental Input */
    static const UINT32 MODE_INC_1;
    static const UINT32 MODE_INC_2;
    static const UINT32 MODE_INC_4;
    /** Modes for PWM Output */
    static const UINT32 MODE_PWM_PUSHPULL;
    static const UINT32 MODE_PWM_LOWSIDE;
    static const UINT32 MODE_PWM_HIGHSIDE;
    static const UINT32 MODE_PWM_DUAL_PP;
    static const UINT32 MODE_PWM_DUAL_LS;
    static const UINT32 MODE_PWM_DUAL_HS;
    /** Modes for Thermocouple */
    static const UINT32 MODE_TC_J;
    static const UINT32 MODE_TC_K;
    static const UINT32 MODE_TC_T;
    static const UINT32 MODE_TC_N;
    static const UINT32 MODE_TC_E;
    static const UINT32 MODE_TC_R;
    static const UINT32 MODE_TC_S;
    static const UINT32 MODE_TC_B;
    /** Modes for PTxxx */
    static const UINT32 MODE_PT100_2;
    static const UINT32 MODE_PT100_3;
    static const UINT32 MODE_PT100_4;
    static const UINT32 MODE_PT200_2;
    static const UINT32 MODE_PT200_3;
    static const UINT32 MODE_PT200_4;
    static const UINT32 MODE_PT500_2;
    static const UINT32 MODE_PT500_3;
    static const UINT32 MODE_PT500_4;
    static const UINT32 MODE_PT1000_2;
    static const UINT32 MODE_PT1000_3;
    static const UINT32 MODE_PT1000_4;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    GIO2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GIO2XX(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~GIO2XX();

    /**
     * Read Stateflags of Module
     *
     * @return State flags of module
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getEventState(VOID);

    /**
     * Set Filter for Analog Input
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Filter
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setAnalogFilter(UINT8 ui8Channel, GIO2XX::EAnalogFilter_t eValue);

    /**
     * Get Filter for Analog Input
     *
     * @param ui8Channel - selected Channel
     * @return Filter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GIO2XX::EAnalogFilter_t getAnalogFilter(UINT8 ui8Channel);

    /**
     * Set Limits for MinMax Event
     *
     * @param ui8Channel - selected Channel
     * @param psValue - Limit value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLimits(UINT8 ui8Channel, GIO2XX::SMinMax_t *psValue);

    /**
     * Get Limits for MinMax Event
     *
     * @param ui8Channel - selected Channel
     * @param psValue - Limit value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GIO2XX::SMinMax_t* getLimits(UINT8 ui8Channel);

    /**
     * Read Temperature of Chip
     *
     * @param ui8Channel - selected Channel
     * @return temperature of the chip
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getChipTemperature(UINT8 ui8Channel);

    /**
     * Set Cold Junction Compensation
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value for compensation
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setCompensation(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Get Cold Junction Compensation
     *
     * @param ui8Channel - selected Channel
     * @return cold junction compensation value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getCompensation(UINT8 ui8Channel);

    /**
     * Activate/Deactivate Halfband Filter
     *
     * @param ui8Channel - selected Channel
     * @param b8Active - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setHalfband(UINT8 ui8Channel, BOOL8 b8Active);

    /**
     * Read actual State of Halfband Filter
     *
     * @param ui8Channel - selected Channel
     * @return TRUE  = Filter is active
     *         FALSE = Filter is not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getHalfband(UINT8 ui8Channel);

    /**
     * Activate/Deactivate Interpolation of Filter
     *
     * @param ui8Channel - selected Channel
     * @param b8Active - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setInterpolation(UINT8 ui8Channel, BOOL8 b8Active);

    /**
     * Read actual State of Interpolation of Filter
     *
     * @param ui8Channel - selected Channel
     * @return TRUE  = Filter is active
     *         FALSE = Filter is not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getInterpolation(UINT8 ui8Channel);

    /**
     * Read Input State of selected Channel
     * Makes it possible to read out the current state (status) of a
     * digital input or output. If the channel is configured as a counter,
     * the current status of the counter signals can be queried.
     *
     * @param ui8Channel - selected Channel
     * @return TRUE  = Channel value is high
     *         FALSE = Channel value is low
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getInputState(UINT8 ui8Channel);

    /**
     * Set Filtertime for Digital Inputs
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Value for Time
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setDigitalFilter(UINT8 ui8Channel, GIO2XX::EDigitalFilter_t eValue);

    /**
     * Get Filtertime for Digital Inputs
     *
     * @param ui8Channel - selected Channel
     * @return Value for filter Time
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GIO2XX::EDigitalFilter_t getDigitalFilter(UINT8 ui8Channel);

    /**
     * Set Configuration of PWM Output
     *
     * @param ui8Channel - selected Channel
     * @param psValue - Pointer to Structure with Configuration
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setPulseConfig(UINT8 ui8Channel, GIO2XX::SPulseConfig_t *psValue);

    /**
     * Get Configuration of PWM Output
     *
     * @param ui8Channel - selected Channel
     * @return  Pointer to Structure with PWM output Configuration
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    GIO2XX::SPulseConfig_t* getPulseConfig(UINT8 ui8Channel);

    /**
     * Set duration of PWM-period
     *
     * @param ui8Channel - selected Channel
     * @param ui32Time - period in us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setPwmPeriod(UINT8 ui8Channel, UINT32 ui32Time);

    /**
     * Get duration of PWM-period
     *
     * @param ui8Channel - selected Channel
     * @return PWM periode time in us
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPwmPeriod(UINT8 ui8Channel);

    /**
     * Start PWM Output
     *
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID startPwm(UINT8 ui8Channel);

    /**
     * Stop PWM Output
     *
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID stopPwm(UINT8 ui8Channel);

    /**
     * Read PWM State
     *
     * @param ui8Channel - selected Channel
     * @return TRUE = Active \n
     *         FALSE = not Active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getPwmState(UINT8 ui8Channel);

    /**
     * Set Value to Reference Register
     * If Position or Counter Value and Register is equal
     * the ReferenceCompare -Event will be triggered
     *
     * @param ui8Channel - selected Channel
     * @param si32Value - Value to Compare
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value);

    /**
     * Get Value to Reference Register
     *
     * @param ui8Channel - selected Channel
     * @return value of reference register
     *
     * @returns TRUE - success
     *          FALSE - failed
     */
    SINT32 getReferenceRegister(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_GIO212;
    }

private:
    GIO2XX::SMinMax_t m_MinMaxLimits;
    GIO2XX::SPulseConfig_t m_PulseConfig;
};

#endif /** GIO2XX_HPP_ */
