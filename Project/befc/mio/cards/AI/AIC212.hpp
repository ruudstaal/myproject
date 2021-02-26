/**
 ********************************************************************************
 * @file     AIX212.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AIC212
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AIC212_HPP_
#define AIC212_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"
#include "../../common/EventSession.hpp"
#include "../../common/base/BasicEventListener.hpp"

/**
 * @brief Condition Monitoring Module AIC212
 */
class AIC212: public BasicAnalogModule
{

public:
    /**
     * @brief Rate of compression
     *
     * Enumeration from eRate0, eRate1... eRate9
     *
     * 0 = maximum Speed \n
     * 9 = maximum compression
     */
    typedef enum
    {
        eRate0 = 0,
        eRate1 = 1,
        eRate2 = 2,
        eRate3 = 3,
        eRate4 = 4,
        eRate5 = 5,
        eRate6 = 6,
        eRate7 = 7,
        eRate8 = 8,
        eRate9 = 9
    } ECompression_t;

    /**
     * @brief State of Module
     */
    typedef enum
    {
        eState_Idle = 0, /**< Module does nothing */
        eState_Recording, /**< Module is recording */
        eState_Exporting, /**< Module exports record */
        eState_Reading /**< Module reads record */
    } EStatus_t;

    /**
     * @brief Modes for Start
     */
    typedef enum
    {
        eStartNow = 0, /**< start immediatly */
        eStartHome, /**< start at Reference event */
        eStartSync, /**< start at next Sync interrupt */
        eStartRef /**< start at Reference of Channel 13 */
    } EStart_t;

    /**
     * @brief Structure of Wavefile
     */
    typedef struct
    {
        CHAR8 ch8Riff[4]; /**< contains 'RIFF' */
        UINT32 ui32Size; /**< filesize        */
        CHAR8 ch8Wave[4]; /**< contains 'WAVE' */
    } WAVEFILE;

    /**
     * @brief Type for Fileoperations
     */
    typedef UINT32 FILEHANDLE;

    /**@{ @name Filter */
    static const UINT32 MAXFILTER; /**< Maximum */
    static const UINT32 MINFILTER; /**< Minimum */
    /**@}*/

    /**@{ @name Samplerate Channel 1-12 */
    static const UINT32 MODE_50KHZ; /**< 50 kHz */
    static const UINT32 MODE_25KHZ; /**< 25 kHz */
    static const UINT32 MODE_12KHZ; /**< 12 kHz */
    static const UINT32 MODE_6KHZ; /**< 6 kHz */
    /**@}*/

    /**@{ @name Modes Channel 13,14 */
    static const UINT32 MODE_INC; /**< Increment Mode */
    static const UINT32 MODE_CONTINUOUS; /**< continuous reset of inc-Channel */
    static const UINT32 MODE_NO_ZERO; /**< deactivate usage of Zero-Impulse */
    static const UINT32 MODE_NO_HOME; /**< deactivate usage of Referenceswitch */
    static const UINT32 MODE_PULSE_DIR; /**< activate Pulse-Direction Mode */
    static const UINT32 MODE_SINGLE; /**< Single Count of Inc */
    static const UINT32 MODE_DOUBLE; /**< Double Count of Inc */
    static const UINT32 MODE_QUAD; /**<  Quad Count of Inc */
    static const UINT32 MODE_COUNT_TIME; /**< Timemeasurement between positive Edges of Input */
    static const UINT32 MODE_DIFF_TIME; /**< Timemeasurement between pos Edge of C1 and pos Edge of C2 */
    static const UINT32 MODE_SYNC; /**< use Sync Interrupt */
    static const UINT32 MODE_TRIGG; /**< use trigger mode */
    static const UINT32 MODE_RESET; /**< deprecated */
    /**@}*/

    /**
     * @brief Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AIC212();

    /**
     * @brief Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AIC212(UINT32 ui32CardNumber);

    /**
     * @brief Destructor
     */
    virtual ~AIC212();

    /*************************************************************
     * Error and Event Interrupts
     *************************************************************/

    /**
     * @brief Attach to Reference Compare Interrupt
     *
     * @param pSession - Event Session from System
     * @param ui8Channel - channel to attach (13 or 14)
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachReference(EventSession *pSession, UINT8 ui8Channel, BasicEventListener *pListener =
    NULL);

    /**
     * @brief Attach to Strobe Interrupt
     *
     * @param pSession - Event Session from System
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching strobe event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachStrobe(EventSession *pSession, BasicEventListener *pListener = NULL);

    /***********************************************************
     * DoCommands
     ************************************************************/

    /**
     * @brief Get temporary Path
     *
     * @param pch8Directory - path
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setTemporaryDir(CHAR8 *pch8Directory);

    /**
     * @brief Get actual configured temporary Path
     *
     * @param pch8Directory - path
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID getTemporaryDir(CHAR8 *pch8Directory);

    /**
     * @brief Set compression Rate of ZIP-Export
     *
     * @param Compression - compression rate
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setCompressionRate(ECompression_t Compression);

    /**
     * @brief Read actual compression Rate of ZIP-Export
     *
     * @return compression rate
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    ECompression_t getCompressionRate(VOID);

    /**
     * @brief Set duration of record
     *
     * @param ui16Len - duration 1-65535
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setRecordLen(UINT16 ui16Len);

    /**
     * @brief Read configured duration of record
     *
     *  possible values are 1 - 65535
     *
     * @return recording duration (measured in 1024 samples/channel)
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT16 getRecordLen(VOID);

    /**
     * @brief Read actual State of Module
     *
     * @return Status of Module
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AIC212::EStatus_t getStatus(VOID);

    /**
     * @brief Start Recording
     *
     * @param Mode - Start Mode
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID startRecording(AIC212::EStart_t Mode);

    /**
     * @brief Stop Recording
     *
     * Stop before configured Recordlength is reached
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID stopRecording(VOID);

    /**
     * @brief Read Frequency of Module
     *
     * @return Frequency [Hz]
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFrequency(VOID);

    /**
     * @brief Read size of installed Memory
     *
     * @return Size of Memory [Byte]
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getMemSize(VOID);

    /**
     * @brief Read Channelvalues from Record
     *
     * @param ui32FirstIndex - first Value to read
     * @param pui32Count - number of values to read
     *                     returns the number of read values
     * @param psi32Values - buffer to store values
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID getRecordedValues(UINT32 ui32FirstIndex, UINT32* pui32Count, SINT32* psi32Values);

    /**
     * @brief Export Record into File
     *
     * @param pch8Filename - Path and Name of File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID startExport(CHAR8 *pch8Filename);

    /**
     * @brief Open exported Record
     *
     * @param pHandle - handle for file
     * @param pch8Filename - Path and Name of File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID openRecord(AIC212::FILEHANDLE *pHandle, CHAR* pch8Filename);

    /**
     * @brief Close Recording
     *
     * @param handle - handle of File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID closeRecord(AIC212::FILEHANDLE handle);

    /**
     * @brief Read Header from opened File
     *
     * @see openRecord
     *
     * @param ui8Channel - Channel 1-13
     * @param handle - handle of file
     * @return Wave file header
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AIC212::WAVEFILE* readHeader(UINT8 ui8Channel, AIC212::FILEHANDLE handle);

    /**
     * @brief Read Values from File
     *
     * @see openRecord
     *
     * @param ui8Channel - channel 1-13
     * @param handle - handle of file
     * @param ui32FirstIndex - first Value to read
     * @param pui32Count - number of values to read
     *                     returns the number of read values
     * @param psi32Values - buffer to store values
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID readSamples(UINT8 ui8Channel, AIC212::FILEHANDLE handle, UINT32 ui32FirstIndex,
            UINT32* pui32Count, SINT32* psi32Values);

    /**
     * @brief Set Path to File whith Values to simulate
     *
     * @note Only possible in Mode VirtualRW
     *
     * @param pch8Filename - path and name of File
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSimulationValues(CHAR8 pch8Filename);

    /**
     * @brief Read actual Value of Counterinputs
     *
     * @note Only for Channel 13 and 14
     *
     * @param ui8Channel - selected Channel 13/14
     * @return actual value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getCounter(UINT8 ui8Channel);

    /**
     * @brief Disable Reference Function
     *
     * @note Only Channel 13 (INC-Mode)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID disableReference(VOID);

    /**
     * @brief Enable Reference Function
     *
     * @note Only Channel 13 (INC-Mode)
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID enableReference(VOID);

    /**
     * @brief Read State of Reference State
     *
     * @note Only Channel 13
     *
     * @return TRUE  = Reference DONE
     *         FALSE =  Reference not DONE
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 isReferenceDone(VOID);

    /**
     * @brief Set Reference Value
     *
     * If Inputvalue (counter) and Registervalue are equal \n
     * the Reference-Event will be triggered \n
     *
     * @see attachReference
     *
     * @param ui8Channel - selected Channel 13/14
     * @param si32Value - Position value for Reference compare
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setReferenceRegister(UINT8 ui8Channel, SINT32 si32Value);

    /**
     * @brief Read Value of Reference Register
     *
     * @note Only Channel 13 and 14
     *
     * @param ui8Channel - selected Channel 13/14
     * @param psi32Value - Value of Referenceregister
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getReferenceRegister(UINT8 ui8Channel);

    /**
     * @brief Read Value of Stroberegister
     *
     * @note Only for Channel 13
     *
     * @return Reference register value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getStrobeRegister(VOID);

    /**
     * @brief Read State of Stroberegister
     *
     * @return TRUE  = triggered
     *         FALSE = not triggered
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 isStrobeTriggerd(VOID);

    /**
     * @brief Reset Stroberegister of Channel 13
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID resetStrobeRegister(VOID);

    /**
     * @brief Read State of NULL Impulse
     *
     * @note Only Channel 13
     *
     * @return TRUE  = Signal active
     *         FALSE = Signal not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 isZeroInputActive(VOID);

    /**
     * @brief Set Filtertime of Input
     *
     * @note Only Channel 13 and 14
     *
     * @see MINFILTER, MAXFILTER
     *
     * @param ui8Channel - selected Channel 13/14
     * @param ui32Filter - Filtertime in us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, UINT32 ui32Filter);

    /**
     * @brief Read Filter of Input
     *
     * @note Only Channel 13 and 14
     *
     * @param ui8Channel - selected Channel 13/14
     * @Return filter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFilter(UINT8 ui8Channel);

    /**
     * @brief Read Status of Reference-Switch
     *
     * @param ui8Channel - selected Channel 13/14
     * @return TRUE = Ref-Input active
     *         FALSE = Ref-Input not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getInputState(UINT8 ui8Channel);

    /**
     * @brief Read Status of Reference-Switch
     *
     * @param ui8Channel - selected Channel 13/14
     * @return TRUE = Ref-Input active
     *         FALSE = Ref-Input not active
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getReferenceSwitch(UINT8 ui8Channel);

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
        return BasicIoModule::TYPE_AIC212;
    }
private:
    AIC212::WAVEFILE m_WaveHeader;

};

#endif /** AIC212_HPP_ */
