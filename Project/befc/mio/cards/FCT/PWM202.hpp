/**
 ********************************************************************************
 * @file     PWM202.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of pulse width modulation module PWM202
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef PWM202_HPP_
#define PWM202_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Pulsemodulation Module PWM202
 *
 */
class PWM202: public BasicAnalogModule
{

public:

    static const UINT32 MODE_OPERATE;/**< PWM Mode Operate */
    static const UINT32 MODE_PWM;/**< Output is in PWM Mode */
    static const UINT32 MODE_CONTROL;/**< Output is in Currentcontrol mode */
    static const UINT32 MODE_SMA;/**< Currentcontrol in Sign/Magitude Control */
    static const UINT32 MODE_LAP;/**< Currentcontrol in locked Antiphasecontrol */

    static const UINT32 MODE_BRAKE;/**< PWM Mode Brake */
    static const UINT32 MODE_BRAKE_UPPER;/**< Configuration of Brakemode: Shortcircuit to Vcc */
    static const UINT32 MODE_BRAKE_LOWER;/**< Configuration of Brakemode: Shortcircuit to GND */
    static const UINT32 MODE_BRAKE_OPEN;/**< Configuration of Brakemode: Open Connectors */
    static const UINT32 MODE_ALIGN_EDGE;/**< Change of Setvalue align to pos edge */
    static const UINT32 MODE_ALIGN_CENTER;/**< Change of Setvalue align to center */
    static const UINT32 MODE_PRESCALE;/**< Mode is only for READ @see 탎age of Pulsewidht > 16 Bit */

    static const REAL32 MAXSAMPLE;/**< Maximum Sampletime */
    static const REAL32 MINSAMPLE;/**< Minimum Sampletime */

    static const REAL32 MAXPROPORTIONAL;/**< Maximum P-Part */
    static const REAL32 MINPROPORTIONAL;/**< Minimum P-Part */

    static const REAL32 MAXINTEGRAL;/**< Maximum Integral Term */
    static const REAL32 MININTEGRAL;/**< Minimum Integral Term */
    /**
     * Loadtype
     */
    typedef enum
    {
        eResistive = 0, eInductive = 1
    } ELoadType_t;

    /**
     * Resolution
     */
    typedef enum
    {
        eLow = 0, /**< 5 Ampere */
        eHigh = 1 /**< 1.5 Ampere */
    } EResolution_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    PWM202();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit PWM202(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~PWM202();

    /**
     * Set Period Time in 탎
     * values greater than 65535 are devided by 256
     *
     * 0..65535 : 0 .. 65535탎
     * > 65535  : only steps with 256탎 possible
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Time in 탎
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setPeriod(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * get Period Time in 탎
     * values greater than 65535 are devided by 256
     *
     * @param ui8Channel - selected Channel
     * @return the period time in 탎
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getPeriod(UINT8 ui8Channel);

    /**
     * Set Channel to Operate-Mode
     *
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID operate(UINT8 ui8Channel);

    /**
     * Set Channel to Brake-Mode
     *
     * @param ui8Channel - selected Channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID brake(UINT8 ui8Channel);

    /**
     * Get State of Operation
     *
     * @param ui8Channel - selected Channel
     * @return operation state
     * 			TRUE = Operate
     *          FALSE = Brake
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getOpState(UINT8 ui8Channel);

    /**
     * Set Time for Currentcontrol
     * 0...32767 ms
     * see constants MINSAMPLE, MAXSAMPLE
     *
     * @param ui8Channel - selected Channel
     * @param r32Value -Time in ms
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSampleTime(UINT8 ui8Channel, REAL32 r32Value);

    /**
     * Set P-Part for current control
     * 0...32767 (100%)
     * see constants MAXPROPORTIONAL, MINPROPORTIONAL
     *
     * @param ui8Channel - selected Channel
     * @param r32Value - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setProportionalTerm(UINT8 ui8Channel, REAL32 r32Value);

    /**
     * Set I-Part for current control
     * 0...1000 ms
     * see constants MAXINTEGRALL, MININTGERAL
     *
     * @param ui8Channel - selected Channel
     * @param r32Value - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setIntegralTerm(UINT8 ui8Channel, REAL32 r32Value);

    /**
     * Get Sampletime of currentcontrol
     *
     * @param ui8Channel - selected Channel
     * @return sample time of current control
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    REAL32 getSampleTime(UINT8 ui8Channel);

    /**
     * Get P-Part for current control
     *
     * @param ui8Channel - selected Channel
     * @return proportional part of current control
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    REAL32 getProportionalTerm(UINT8 ui8Channel);

    /**
     * Set I-Part for current control
     *
     * @param ui8Channel - selected Channel
     * @return the Integrational part of the currenc control
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    REAL32 getIntegralTerm(UINT8 ui8Channel);

    /**
     * Set Loadtype Resistive/Inductive
     *
     * @param ui8Channel - selected Channel
     * @param eValue - value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setLoadType(UINT8 ui8Channel, PWM202::ELoadType_t eValue);

    /**
     * Set Maximum Current of channel
     * if this value is reached the channel is
     * switched off.
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - maximum current
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMaxCurrent(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * get Maximum Current of the channel
     *
     * @param ui8Channel - selected Channel
     * @return the maximum current of the channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getMaxCurrent(UINT8 ui8Channel);

    /**
     * Set Resolution of channel
     * Low Resolution  = 5 A
     * High Resolution = 1.5 A
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Resolution
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setResolution(UINT8 ui8Channel, EResolution_t eValue);

    /**
     * Get Resolution of the channel
     * Low Resolution  = 5 A
     * High Resolution = 1.5 A
     *
     * @param ui8Channel - selected Channel
     * @return resolution of the channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    EResolution_t getResolution(UINT8 ui8Channel);

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/

    /**
     * Attach to Power Fail Interrupt
     *
     * @param pSession - Error Session from System
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener = NULL);

protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_PWM202;
    }
};

#endif /** PWM202_HPP_ */
