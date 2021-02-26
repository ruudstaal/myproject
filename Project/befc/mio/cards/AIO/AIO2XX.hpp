/**
 ********************************************************************************
 * @file     AIO2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input and output module AIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AIO2XX_HPP_
#define AIO2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include "gio2xx.h"

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 16 Bit Analog Input Output Module
 *
 * AIO208, AIO216
 *
 * Input: \n
 * +/-10V, +/-1V, +/-100mV, +/-10mV \n
 * +/-20mA, 4-20mA \n
 * Typ J, K, T, N, E, R, S, B \n
 * PT100, PT200, PT500, PT1000 \n
 *
 * Output: \n
 * +/-10V, 0-10V \n
 * 0-20mA, 4-20mA, 0-2mA, 0-200uA \n
 */
class AIO2XX: public BasicAnalogModule
{

public:

    /************************************************************
     *                      DATATYPES
     ************************************************************/

    /**
     * Values for Input Filter
     */
    typedef enum
    {
        eFilter_4khz,
        eFilter_2khz,
        eFilter_1khz,
        eFilter_500hz,
        eFilter_250hz,
        eFilter_125hz,
        eFilter_62_5hz,
        eFilter_31_2hz,
        eFilter_15_6hz,
        eFilter_7_8hz,
        eFilter_3_9hz,
        eFilter_1_9hz,
        eFilter_0_97hz,
        eFilter_0_50hz

    } EFilter_t;

    /**
     * Structure for Limits
     */
    typedef struct
    {
        SINT32 si32Min;
        SINT32 si32Max;
    } SMinMax_t;

    /************************************************************
     *                      CONSTANTS
     ************************************************************/

    /** Channel Disabled */
    static const UINT32 MODE_DISABLED;
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
    AIO2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AIO2XX(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~AIO2XX();

    /**
     * @brief Read Stateflags of Module
     *
     * @return State flags of module
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getEventState(VOID);

    /**
     * @brief Set Filter for Analog Input
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Filter
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, AIO2XX::EFilter_t eValue);

    /**
     * @brief Get Filter for Analog Input
     *
     * @param ui8Channel - selected Channel
     * @return filter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AIO2XX::EFilter_t getFilter(UINT8 ui8Channel);

    /**
     * @brief Set Limits for MinMax Event
     *
     * @param ui8Channel - selected Channel
     * @param psValue - pointer to value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLimits(UINT8 ui8Channel, AIO2XX::SMinMax_t *psValue);

    /**
     * @brief Get Limits for MinMax Event
     *
     * @param ui8Channel - selected Channel
     * @return a point to the Min Max data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AIO2XX::SMinMax_t* getLimits(UINT8 ui8Channel);

    /**
     * @brief Read Temperature of Chip
     *
     * @param ui8Channel - selected Channel
     * @return Temperature of the chip
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getChipTemperature(UINT8 ui8Channel);

    /**
     * @brief Set Cold Junction Compensation
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setCompensation(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * @brief Get Cold Junction Compensation
     *
     * @param ui8Channel - selected Channel
     * @return cold junction compensation value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getCompensation(UINT8 ui8Channel);

    /**
     * @brief Activate/Deactivate Halfband Filter
     *
     * @param ui8Channel - selected Channel
     * @param b8Active - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setHalfband(UINT8 ui8Channel, BOOL8 b8Active);

    /**
     * @brief Read actual State of Halfband Filter
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
     * @brief Activate/Deactivate Interpolation of Filter
     *
     * @param ui8Channel - selected Channel
     * @param b8Active - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setInterpolation(UINT8 ui8Channel, BOOL8 b8Active);

    /**
     * @brief Read actual State of Interpolation of Filter
     *
     * @param ui8Channel - selected Channel
     * @return TRUE  = Filter is active
     *         FALSE = Filter is not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getInterpolation(UINT8 ui8Channel);

protected:

    /**
     * @brief get Type of Module
     *
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AIO2XX;
    }
private:
    AIO2XX::SMinMax_t m_MinMaxLimits;
};

#endif /** AIO2XX_HPP_ */
