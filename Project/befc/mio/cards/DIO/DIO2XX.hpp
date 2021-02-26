/**
 ********************************************************************************
 * @file     DIO2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DIO2XX_HPP_
#define DIO2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input/Output Module
 * Class for use with DIO248 DIO264, DIO280
 *
 * Channels     : 48   , 64   , 80    \n
 * Input        : 16-32, 24-40, 32-48 \n
 * Output       : 16-32, 24-40, 32-48 \n
 * In or Out    : 16    \n
 * Interrupt    : 8     \n
 *
 * Counter      : 4     \n
 */
class DIO2XX: public BasicDigitalModule
{

public:

    /**@{ @name Channelmodes 1-16 */
    static const UINT32 MODE_INPUT; /**< Channel is Input */
    static const UINT32 MODE_OUTPUT; /**< Channel is Input */
    /**@}*/

    /**@{ @name Channelmodes 17-24 */
    static const UINT32 MODE_POSEDGE; /**<  use positive Edge of Input */
    static const UINT32 MODE_NEGEDGE; /**<  use negative Edge of Input */
    static const UINT32 MODE_BOTHEDGES; /**<  use positive and negative Edge of Input */
    /**@}*/

    /**@{ @name Channelmodes 81-84 */
    static const UINT32 MODE_INC; /**<  Increment Counter Mode */
    static const UINT32 MODE_GATE_TIME; /**<  count pulses of Signal A within defined gatetime */
    static const UINT32 MODE_PERIOD; /**< Timemeasurement between pos Edges of A-Signal */
    static const UINT32 MODE_SINGLE; /**<  Single Count of Inc */
    static const UINT32 MODE_DOUBLE; /**<  Double Count of Inc */
    static const UINT32 MODE_QUAD; /**<  Quad Count of Inc */
    /**@}*/

    /**
     * @brief Confiuration of PWM Signal
     *
     * Values will be rounded to the next \n
     * Stepvalue
     */
    typedef struct
    {
        UINT32 Enabled; /**< 0 == disabled, !0 == enabled */
        UINT32 Period; /**< Period duration in us \n
         | Min   | Max       |Step |
         |-------|-----------|-----|
         |1000   |1080000    |132  |
         */
        UINT32 PulseWidth; /**< Pulse width in % of Period \n
         | Value | Percent|
         |-------|--------|
         |0      |0       |
         |32767  |100     |
         */
        UINT32 PullTime; /**< Additional Time in us on Activation \n
         | Min   | Max       |Step    |
         |-------|-----------|--------|
         |0      |2000000    |135000  |
         */
    } sPWM_CONFIG_t;

    /**
     * Definiton of Interruptmode
     */
    typedef enum
    {
        eFALLING_EDGE, /**< use falling edge */
        eRISING_EDGE /**< use rising edge */
    } eEDGE_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DIO2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DIO2XX(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DIO2XX();

    /**
     * Set Configuration of PWM Output
     *
     * @param ui8Channel - Channel of Module
     * @param pConfig - Variable to store data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setPwmConfig(UINT8 ui8Channel, sPWM_CONFIG_t *pConfig);

    /**
     * Read PWM Configuration
     *
     * @param ui8Channel - Channel of Module
     * @returns pointer to PWM configuration structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    sPWM_CONFIG_t* getPwmConfig(UINT8 ui8Channel);

    /**
     *  Set Time of Input Filter
     *
     * @param ui8Channel - Channel of Module
     * @param ui32Time - Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, UINT32 ui32Time);

    /**
     * Get Time of Input Filter
     *
     * @param ui8Channel - Channel of Module
     * @return Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFilter(UINT8 ui8Channel);

    /**
     * Set Value for Measurement Mode GATETIME
     *
     * @param ui8Channel - Channel of Module
     * @param ui32Time - Time in us to set, 0 - 270336 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setGateTime(UINT8 ui8Channel, UINT32 ui32Time);

    /**
     * Get Value for Measurement Mode GATETIME
     *
     * @param ui8Channel - Channel of Module
     * @return configured Time, 0 - 270336 us
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getGateTime(UINT8 ui8Channel);

    /**
     * Set Value for Counterchannels at Reset
     *
     * @param ui8Channel - Channel of Module
     * @param ui32Value - value for Resetregister
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setResetValue(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Get Value for Counterchannels at Reset
     *
     * @param ui8Channel - Channel of Module
     * @return Reset register
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getResetValue(UINT8 ui8Channel);

    /**
     * Check if Output channels measures an external signal
     *
     * @param ui8Channel - Channel of Module
     * @param pui16Channels - Actual pin levels on the card including deactivated outputs that if forced high
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if parameter is invalid
     */
    VOID getPinLevel(UINT8 ui8Channel, UINT16 *pui16Channels);

    /**
     * Get value from Stroberegister
     *
     * @param ui8Channel - Channel of Module
     * @return strobe register value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getStrobeRegister(UINT8 ui8Channel);

    /**
     *  Activate reset
     *
     * @param ui8Channel - Channel of Module
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID enableReset(UINT8 ui8Channel);

    /**
     *  Read State of Reset
     *
     * @param ui8Channel - Channel of Module
     * \Return 0 = Reset not active
     *         1 = Reset active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 resetActive(UINT8 ui8Channel);

    /**
     *  Set Mode of Nullindex
     *
     * @param ui8Channel - Channel of Module
     * @param Mode - Value for Mode
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setNullSwitchMode(UINT8 ui8Channel, DIO2XX::eEDGE_t Mode);

    /**
     *  Get Mode of Nullindex
     *
     * @param ui8Channel - Channel of Module
     * @param pMode - Variable to Store value
     *
     * @returns TRUE - done
     *          FALSE - error
     */
    DIO2XX::eEDGE_t getNullSwitchMode(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DIO2XX;
    }

private:
    sPWM_CONFIG_t m_PwmCfg;

};

#endif /** DIO2XX_HPP_ */
