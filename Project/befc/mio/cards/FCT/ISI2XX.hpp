/**
 ********************************************************************************
 * @file     ISI2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of position module ISI2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef ISI2XX_HPP_
#define ISI2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Counter Module ISI222
 *
 * Inc or SSI Input : 2 \n
 * Analog Out       : 2 \n
 * Digital IN       : 2 (INIT, TRIG) \n
 */
class ISI2XX: public BasicAnalogModule
{
public:

    static const UINT32 MODE_INC;/**< Increment Mode */
    static const UINT32 MODE_SINGLE;/**< Single Count of Incremental Mode */
    static const UINT32 MODE_DOUBLE;/**< Double Count of Incremental Mode */
    static const UINT32 MODE_QUAD;/**< Quad Count of Incremental Mode */
    static const UINT32 MODE_NO_ZERO;/**< deactivate usage of Zero-Impulse */
    static const UINT32 MODE_NO_HOME;/**< deactivate usage of Referenceswitch */
    static const UINT32 MODE_AUTOLD;/**< Load Value from SET-Register */
    static const UINT32 MODE_LATCH_REF;/**< Save counter in Reference Register on REF-Input */
    static const UINT32 MODE_LATCH_STROBE;/**< Save counter in Strobe Register on REF-Input */
    static const UINT32 MODE_LATCH_STROBE_TRIG;/**< Save counter in Strobe Register on TRIG-Input */
    static const UINT32 MODE_SYNC;/**< use Sync Interrupt */
    static const UINT32 MODE_PULSEDIR;/**< activate Pulse-Direction-Mode */
    static const UINT32 MODE_RESET;/**< @deprecated use EnableReset(...) instead */

    static const UINT32 MODE_SSI;/**< SSI Mode */
    static const UINT32 MODE_VROUT;/**< set signal V/R to 1 */
    static const UINT32 MODE_SETOUT;/**< set signal SET to 1 */
    static const UINT32 MODE_NOPARITY;/**< disable Parity Bit */
    static const UINT32 MODE_PAR_EVEN;/**< Even Parity */
    static const UINT32 MODE_PAR_ODD;/**< Odd Parity */
    static const UINT32 MODE_BINARY;/**< binary transmission */
    static const UINT32 MODE_GRAY;/**< gray transmission */

    static const UINT32 MAX_SSI_FREQUENCY;/**< Maximum Filtertime */
    static const UINT32 MIN_SSI_FREQUENCY;/**< Minimum Filtertime */

    static const UINT32 MAXFILTER;/**< Maximum Filtertime */
    static const UINT32 MINFILTER;/**< MinimumFiltertime */

    /**
     *
     */
    typedef enum
    {
        eHighActive = MIO_HIGHACTIVE, eLowActive = MIO_LOWACTIVE
    } EInputLevel_t;

    /**
     *
     */
    typedef enum
    {
        ePositive = MIO_M_POSEDGE, eNegative = MIO_M_NEGEDGE
    } EEdge_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    ISI2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit ISI2XX(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~ISI2XX();

    /*************************************************************
     *
     *    DO COMMANDS
     *
     *************************************************************/

    /**
     * Enable Referencemode
     *
     * @param ui8Channel - selected Channel
     * @param b8Value - TRUE = Enable
     *                  FALSE = Disable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID enableReset(UINT8 ui8Channel, BOOL8 b8Value);

    /**
     * Set Reference Register and Enable Reference-Compare-Interrupt
     * if counter and register are equal the
     * Reference-Interupt will be activated
     *
     * @param ui8Channel - selected Channel
     * @param si32Value - counter to compare
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value);

    /**
     * Read Value of Reference Register
     *
     * @param ui8Channel - selected Channel
     * @return value of reference register
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getReferenceRegister(UINT8 ui8Channel);

    /**
     * Read State of Reference Register
     * TRUE  = Reference done
     * FALSE = Reference not done
     *
     * @param ui8Channel - selected Channel
     * @return reference state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getReferenceState(UINT8 ui8Channel);

    /**
     * Read Value of Strobe Register
     * Strobe can be triggerd by Digital Input
     *
     * @param ui8Channel - selected Channel
     * @return value of strobe register
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getStrobeRegister(UINT8 ui8Channel);

    /**
     * Read State of Strobe Register
     * Strobe can be triggerd by Digital Input
     *
     * @param ui8Channel - selected Channel
     * @return state of strobe register
     * 			TRUE = Trigger done
     *          FALSE = Trigger not done
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getStrobeState(UINT8 ui8Channel);

    /**
     * Read State of Null-Impulse
     *
     * @param ui8Channel - selected Channel
     * @return reference state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getZeroState(UINT8 ui8Channel);

    /**
     * Read State of Referenceswitch
     *
     * @param ui8Channel - selected Channel
     * @return reference switch state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getRefSwitchState(UINT8 ui8Channel);

    /***
     * write Frequency from Module
     * default : 100 (= MIN_SSI_FREQUENCY)
     * @see MAX_SSI_FREQUENCY, MIN_SSI_FREQUENCY
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSSIFrequency(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read Frequency from Module
     * see constants MAX_SSI_FREQUENCY, MIN_SSI_FREQUENCY
     *
     * @param ui8Channel - selected Channel
     * @return the frequency value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getSSIFrequency(UINT8 ui8Channel);

    /**
     * write lenght of SSI-Dataword
     * Values: 0-32 Bit
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSSIDataLen(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read lenght of SSI-Dataword
     * Values: 0-32 Bit
     *
     * @param ui8Channel - selected Channel
     * @return length of the SSI-Dataword
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getSSIDataLen(UINT8 ui8Channel);

    /**
     * write Delay between two Datapackets
     * Values: 10-65535 us
     * Default: 50us
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSSIDelay(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read Delay between two Datapackets
     * Values: 10-65535 us
     * Default: 50us
     *
     * @param ui8Channel - selected Channel
     * @return the delay value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getSSIDelay(UINT8 ui8Channel);

    /**
     *  Set Input filter frequency for Digital IN
     *  see constants MINFILTER/MAXFILTER
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - new Value for Filter
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     *  Get Input filter for Digital IN
     *  see constants MINFILTER/MAXFILTER
     *
     * @param ui8Channel - selected Channel
     * @return the input filter frequency
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFilter(UINT8 ui8Channel);

    /**
     * Set Mode of Reference Input
     * possible Channels are 7 or 8
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setInputMode(UINT8 ui8Channel, ISI2XX::EInputLevel_t eValue);

    /**
     * Get Mode of Reference Input
     * possible Channels are 7 or 8
     *
     * @param ui8Channel - selected Channel
     * @return the input level
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    ISI2XX::EInputLevel_t getInputMode(UINT8 ui8Channel);

    /**
     * Read Counter Value
     * if channel is not used in Syncmode it is recommended
     * to use getValue(...)
     *
     * @param ui8Channel - selected Channel
     * @return counter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getCounter(UINT8 ui8Channel);

    /**
     * Activate cyclic check of Encoder
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value to check (0 = deactivated)
     *                  - > 0 Encoder Value between two Null-pulses
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEncoderCheck(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     *  Get Value of Encoder Check
     *
     * @param ui8Channel - selected Channel
     * @return the encoder check value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getEncoderCheck(UINT8 ui8Channel);

    /**
     * Set Value to Reset-Register
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value to check
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setResetRegister(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Get Value of Reset-Register
     *
     * @param ui8Channel - selected Channel
     * @return the SET register value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getResetRegister(UINT8 ui8Channel);

    /**
     * Set Value to GateTime-Register
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value to check
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setGateTime(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Get Value of GetTime-Register
     *
     * @param ui8Channel - selected Channel
     * @return the Gate time
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getGateTime(UINT8 ui8Channel);

    /**
     * Set Offset value of Reference Register
     *
     * @param ui8Channel - selected Channel
     * @param ui32Value - Value to check
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReferenceOffset(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Get Offset value of Reference Register
     *
     * @param ui8Channel - selected Channel
     * @return reference offset value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getReferenceOffset(UINT8 ui8Channel);

    /**
     * Set Edge of Nullimpulse
     *
     * @param ui8Channel - selected Channel
     * @param eValue - Value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setNullEdge(UINT8 ui8Channel, ISI2XX::EEdge_t eValue);

    /**
     * Set Edge of Nullimpulse
     *
     * @param ui8Channel - selected Channel
     * @return the edge trigger value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    ISI2XX::EEdge_t getNullEdge(UINT8 ui8Channel);

    /**
     * Enable Brokenwire Detection of NULL-Impulse
     *
     * @param ui8Channel - selected Channel
     * @param b8Value - TRUE = activate
     *                  FALSE = deactivate
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setBrokenWireDetection(UINT8 ui8Channel, BOOL8 b8Value);

    /**
     * get state of Brokenwire Detection of NULL-Impulse
     *
     * @param ui8Channel - selected Channel
     * @return reference switch state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getBrokenWireDetection(UINT8 ui8Channel);

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

    /**
     * Attach to Reference Compare Interrupt
     * call setReferenceRegister(...) to activate
     *
     * @param pSession - Event Session from System
     * @param ui8Channel - selected Channel (0 = means Module)
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachReferenceCompare(EventSession *pSession, UINT8 ui8Channel,
            BasicEventListener *pListener = NULL);

    /**
     * Attach to Reset Interrupt
     * call enableReset(...) to activate
     *
     * @param pSession - Event Session from System
     * @param ui8Channel - selected Channel (0 = means Module)
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachReset(EventSession *pSession, UINT8 ui8Channel,
            BasicEventListener *pListener = NULL);
protected:

    /**
     * get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_ISI222;
    }
};

#endif /** ISI2XX_HPP_ */
