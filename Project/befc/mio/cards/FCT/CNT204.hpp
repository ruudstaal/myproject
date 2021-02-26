/**
 ********************************************************************************
 * @file     CNT204.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of counter module CNT204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CNT204_HPP_
#define CNT204_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Counter Module CNT204
 *
 * Channels:        4 (INC or HTL) \n
 * Digital Input:   4
 */
class CNT204: public BasicAnalogModule
{
public:
    static const UINT32 MODE_INC; /**< Increment Mode */
    static const UINT32 MODE_COUNT; /**< Increment Mode */
    static const UINT32 MODE_INC_TIME; /**< Timemeasurement betweeb pos Edges of A-Signal */
    static const UINT32 MODE_COUNT_TIME; /**< Timemeasurement between positive Edges of Input */
    static const UINT32 MODE_DIFF_TIME; /**< Timemeasurement between pos Edge of C1 and pos Edge of C2 */
    static const UINT32 MODE_TRIGG; /**< use trigger mode */

    static const UINT32 MODE_SINGLE; /**< Single Count of Incremental Mode */
    static const UINT32 MODE_DOUBLE; /**< Double Count of Incremental Mode */
    static const UINT32 MODE_QUAD; /**< Quad Count of Incremental Mode */

    static const UINT32 MODE_CONTINUOUS; /**< continuous reset of inc-Channel */
    static const UINT32 MODE_NO_ZERO; /**< deactivate usage of Zero-Impulse */
    static const UINT32 MODE_NO_HOME; /**< deactivate usage of Referenceswitch */
    static const UINT32 MODE_PULSE_DIR; /**< activate Pulse-Direction Mode */
    static const UINT32 MODE_SYNC; /**< use Sync Interrupt */
    static const UINT32 MODE_RESET; /**< deprecated */
    static const UINT32 MAXFILTER; /**< Minimum Filtertime */
    static const UINT32 MINFILTER; /**< Maximum Filtertime */

    /**
     * Flags for Timemeasurement
     */
    typedef struct
    {
        BOOL8 b8NewValue;
        BOOL8 b8ValueLost;
    } SFlags_t;

    /**
     * default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    CNT204();

    /**
     * Constructor
     *
     * @param[in] ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit CNT204(UINT32 ui32CardNumber);

    /**
     * default Destructor
     */
    virtual ~CNT204();

    /**
     *  DO COMMANDS
     */

    /**
     * @brief Read Value of selected Channel and clear Flags
     *
     * Flags for Timemeasurement  will be reseted!! \n
     * Flags are not reseted by using getValue(...)
     *
     * @param[in] ui8Channel - selected Channel
     * @param[in] psFlags - optional pointer to Flags Structure
     * @return value of the channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getValueAndFlags(UINT8 ui8Channel, SFlags_t *psFlags = NULL);

    /**
     * @brief Read Counter Value
     *
     * if channel is not used in Syncmode it is recommended \n
     * to use getValue(...)
     *
     * @param[in] ui8Channel - selected Channel
     * @returns counter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getCounter(UINT8 ui8Channel);

    /**
     * @brief Read Digital Input
     *
     * @param[in] ui8Channel - selected Input channel
     * @param[in] pb8Value - pointer to variable
     *
     * @returns value of the digital channel
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getInput(UINT8 ui8Channel);

    /**
     * @brief write Value to Reference Register
     *
     * if actual value of counter is equal to this value \n
     * the Reference Compare Interrupt will be send.
     *
     * @param[in] ui8Channel - selected Channel
     * @param[in] si32Value - Value to activate ReferenceCompare IRQ
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value);

    /**
     * @brief Read Value of Reference Register
     *
     * @param[in] ui8Channel - selected Channel
     * @param[in] psi32Value - pointer to Variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getReferenceRegister(UINT8 ui8Channel);

    /**
     * @brief Read State of Reference Register
     *
     * TRUE  = Reference done \n
     * FALSE = Reference not done
     *
     * @param[in] ui8Channel - selected Channel
     * @returns value of reference state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getReferenceState(UINT8 ui8Channel);

    /**
     * @brief Read Value of Strobe Register
     *
     * Strobe can be triggerd by Digital Input
     *
     * @param[in] ui8Channel - selected Channel
     * @returns value of strobe register
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getStrobeRegister(UINT8 ui8Channel);

    /**
     * @brief Read State of Strobe Register
     *
     * Strobe can be triggered by Digital Input \n
     * TRUE  = Trigger done \n
     * FALSE = Trigger not done
     *
     * @param[in] ui8Channel - selected Channel
     * @returns value of strobe state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getStrobeState(UINT8 ui8Channel);

    /**
     * @brief Reset Strobe Trigger State
     *
     * @param[in] ui8Channel - selected Channel
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetStrobeState(UINT8 ui8Channel);

    /**
     * @brief Enable Reference mode
     *
     * @param[in] ui8Channel - selected Channel
     * @param[in] b8Value - TRUE = Enable
     *                  FALSE = Disable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID enableReset(UINT8 ui8Channel, BOOL8 b8Value);

    /**
     * @brief Read State of Null-Impulse
     *
     * @param[in] ui8Channel - selected Channel
     * @returns value of zero state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getZeroState(UINT8 ui8Channel);

    /**
     * @brief Read State of Referenceswitch
     *
     * @param[in] ui8Channel - selected Channel
     * @returns value of ref switch state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getRefSwitchState(UINT8 ui8Channel);

    /**
     * @brief Set Input filter
     *
     * set Filter for Digital Input
     *
     * @see MINFILTER, MAXFILTER
     *
     * @param[in] ui8Channel - selected Channel
     * @param[in] ui32Value - new Value for Filter
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * @brief Read Frequency from Module
     *
     * @param[in] pui32Value - pointer to Variable
     * @returns the frequency value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFrequency(VOID);

    /**
     * @brief Receive Timemeasurement flags
     *
     * @param[in] ui8Channel - selected Channel
     * @returns a pointer to the flags data structure
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SFlags_t* getFlags(UINT8 ui8Channel);

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/

    /**
     * @brief Attach to Power Fail Interrupt
     *
     * @param[in] pSession - Error Session from System
     * @param[in] pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener = NULL);

    /**
     * @brief Attach to external pulse detected
     *
     * @param[in] pSession - Error Session from System
     * @param[in] ui8Channel - selected Channel (0 = means Module)
     * @param[in] pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachExternalVoltage(ErrorSession *pSession, UINT8 ui8Channel,
            BasicErrorListener *pListener = NULL);

    /**
     * @brief Attach to Decoder Error
     *
     * @param[in] pSession - Error Session from System
     * @param[in] ui8Channel - selected Channel (0 = means Module)
     * @param[in] pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachDecoderError(ErrorSession *pSession, UINT8 ui8Channel,
            BasicErrorListener *pListener = NULL);

    /**
     * @brief Attach to Reference Compare Interrupt
     *
     * @see setReferenceRegister
     *
     * @param[in] pSession - Event Session from System
     * @param[in] ui8Channel - selected Channel (0 = means Module)
     * @param[in] pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachReferenceCompare(EventSession *pSession, UINT8 ui8Channel,
            BasicEventListener *pListener = NULL);

    /**
     * @brief Attach to Reset Interrupt
     *
     * @see enableReset to activate
     *
     * @param[in] pSession - Event Session from System
     * @param[in] ui8Channel - selected Channel (0 = means Module)
     * @param[in] pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachReset(EventSession *pSession, UINT8 ui8Channel,
            BasicEventListener *pListener = NULL);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_CNT204;
    }

private:
    SFlags_t m_Flags;
};

#endif /** CNT204_HPP_ */
