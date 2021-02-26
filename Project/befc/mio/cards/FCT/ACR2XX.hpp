/**
 ********************************************************************************
 * @file     ACR2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of axis control module ACR2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef ACR2XX_HPP_
#define ACR2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************
 */

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Stepper Module ACR222
 *
 * Controller for two Stepper Amplifier
 */
class ACR2XX: public BasicAnalogModule
{

public:

    typedef MIO_ACR_PROFILE SProfile_t; /**< Structure for moving */
    typedef MIO_ACR_DRVDATA SDriveData_t; /**< In/Out Configuration */
    typedef MIO_ACR_RESOLUTION SResolution_t; /**< Configuration if Resolution */

    /**
     * Encoder Settings
     */
    typedef enum
    {
        eQuad, /**< 2-phase, Quad-Encoder **/
        eDouble, /**< 2-phase, Double-Encoder **/
        eSingle, /**< 2-phase, Single-Encoder **/
        eNegative /**< 2-phase, negative logic **/
    } EEncoderMode_t;

    /**
     * @brief Homing Modes
     *
     * @see SHome_t
     */
    typedef enum
    {
        /**
         * Reference Clockwise \n
         * using Referenceswitch and Nullimpulse
         */
        eCW_REF_NULL = 2,
        /**
         * Reference Counterclockwise \n
         * using Referenceswitch and Nullimpulse
         */
        eCCW_REF_NULL = 3,
        /**
         * Reference Clockwise \n
         * using Referenceswitch
         */
        eCW_REF = 5,
        /**
         * Reference Coutnerclockwise \n
         * using Referenceswitch
         */
        eCCW_REF = 6
    } EHomeMode_t;

    /**
     * @brief Structure for Homing
     *
     */
    typedef struct
    {
        /** Profile type */
        EHomeMode_t Method;
        /** Speed for search Referenceswitch INC/sec */
        UINT32 FirstSearchVelocity;
        /** Speed for search zero-pulse in INC/sec */
        UINT32 SecondSearchVelocity;
        /** Ramp Up and Down in INC/sec2 */
        UINT32 Acceleration;
        /** Must be 0 for now */
        UINT32 Spare[2];
    } SHome_t;

    /**
     * @brief Structure for Common Settings
     */
    typedef struct
    {
        /** TRUE  = higher motor current during acceleration,
         *  FALSE = normal motor current
         */
        BOOL8 b8Boost;
        /** TRUE  = reduced motor current on stop,
         *  FALSE = normal motor current
         */
        BOOL8 b8Standby;
        /** TRUE  = half step,
         *  FALSE = full step
         */
        BOOL8 b8Step;
        /** TRUE  = Stop on full Step,
         *  FALSE = Stop on full or half Step
         */
        BOOL8 b8Index;
        /** Mode of Encoder*/
        EEncoderMode_t eMode;
    } SSettings_t;

    /**
     * @brief Single State from History
     */
    typedef struct
    {
        BOOL8 b8Stop; /**< TRUE = Stop **/
        BOOL8 b8Run; /**< TRUE = Run **/
        BOOL8 b8TargetReached; /**< TRUE = Target Reached **/
        BOOL8 b8Follow; /**< TRUE = Following Error **/
    } SState_t;

    /**
     * @brief Structure for Statehistory
     */
    typedef struct
    {
        UINT8 u8Counter; /**< State Change Counter **/
        SState_t sState[6]; /**< last 6 changes **/
    } SStateHistory_t;

    /**
     * @brief Structure for all Digital Inputs
     *
     */
    typedef struct
    {
        BOOL8 b8PosLimit; /**< positive endswitch **/
        BOOL8 b8NegLimit; /**< negative endswitch **/
        BOOL8 b8EmyStop; /**< Emergency Stop */
        BOOL8 b8Reference; /**< Reference switch */
        BOOL8 b8ZeroPulse; /**< Zero Pulse of Encoder */
    } SDigitalInput_t;

    /**
     * @brief Runmode for one Axis
     */
    typedef enum
    {
        eModeRamp = 0, /**< Ramp */
        eModeReference = 1, /**< move reference */
        eModeFreeRun = 2, /**< velocity move */
        eModeProfile = 3 /**< move profile */
    } EMode_t;

    /**
     * @brief Moving Profile for one Axis
     */
    typedef enum
    {
        eProfileLinear = 0, /**< Linear Profile **/
        eProfileSinus = 1, /**< Sinus Profile **/
        eProfileParabolic = 2, /**< Parabolic Profile **/
        eProfileFrequency = 3 /**< Frequency Mode **/
    } EProfile_t;

    /**
     * @brief Structure of Controlword
     */
    typedef struct
    {
        BOOL8 b8DisableVoltage;
        BOOL8 b8QuickStop;
        BOOL8 b8Stop;
        BOOL8 b8Start;
        BOOL8 b8DualStart;
        BOOL8 b8MoveRelative;
        BOOL8 b8ChangeSpeed;
        EMode_t eMode;
    } SControlword_t;

    /**
     * @brief Structure of Statusword
     */
    typedef struct
    {
        BOOL8 b8DisableVoltage;
        BOOL8 b8QuickStop;
        BOOL8 b8Stop;
        BOOL8 b8Start;
        BOOL8 b8TargetReached;
        BOOL8 b8FollowingError;
        BOOL8 b8Error;
        BOOL8 b8ChangeSpeed;
        EProfile_t eProfile;
        BOOL8 b8Busy;
        EMode_t eMode;
        BOOL8 b8Undefined; /**< TRUE = other Bits not valid! */
    } SStatusword_t;

    /**@{ @name Operation Modes for Channels 3/4 */
    static const UINT32 MODE_LINEAR;/**< Linear Interpolation **/
    static const UINT32 MODE_SINUS;/**< Sinus2 Interpolation **/
    static const UINT32 MODE_PARABOLIC;/**< Parabolic Interpolation **/
    static const UINT32 MODE_FREQUENCY;/**< Setvalue is Frequency **/
    /** @} */

    /**
     * Default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    ACR2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit ACR2XX(UINT32 ui32CardNumber);

    /**
     * Initialize all values at construction.
     */
    VOID init();

    /**
     *  DefaultDestructor
     */
    virtual ~ACR2XX();

    /**
     * write new controlword
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psControl - pointer to data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if parameter is invalid
     */
    VOID setControlWord(UINT8 ui8Channel, SControlword_t *psControl);

    /**
     * Read actual Statusword
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to status word data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if pointer to analog channel is invalid.
     */
    SStatusword_t* getStatusWord(UINT8 ui8Channel);

    /**
     * *******************************************************
     *     Do Commands
     * *******************************************************
     */

    /**
     * Set Motion Profile
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psProfile - pointer to Profiledata
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setProfile(UINT8 ui8Channel, SProfile_t *psProfile);

    /**
     *  Read Motion Profile
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to Profiledata data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SProfile_t* getProfile(UINT8 ui8Channel);

    /**
     * Set Homing Parameter
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psHome - pointer to Homing-data
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setHome(UINT8 ui8Channel, SHome_t *psHome);

    /**
     *  Read Homing Parameter
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to Homing-data structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SHome_t* getHoming(UINT8 ui8Channel);

    /**
     * Set Drive Configuration
     * Set Polarity and Direction Mode
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psData - pointer to Drivedata
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setDriveData(UINT8 ui8Channel, SDriveData_t *psData);

    /**
     * Read Drive Configuration
     * Read Polarity and Direction Mode
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to Drive configuration structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SDriveData_t* getDriveData(UINT8 ui8Channel);

    /**
     * Set Resolution Configuration
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psResolution - pointer to Resolutiondata
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setResoultion(UINT8 ui8Channel, SResolution_t *psResolution);

    /**
     * Read Resolution Configuration
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to Resolution configurator structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SResolution_t* getResoultion(UINT8 ui8Channel);

    /**
     * Set common parameters
     *
     * @param ui8Channel - selected Axis 1/2
     * @param psSettings - pointer to Settings
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setSettings(UINT8 ui8Channel, SSettings_t *psSettings);

    /**
     * Read common parameters
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to settings structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SSettings_t* getSettings(UINT8 ui8Channel);

    /**
     * Set Deceleration for Quickstop
     *
     * @param ui8Channel - selected Axis 1/2
     * @param ui32Value - Setvalue
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setQuickDecel(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read Deceleration for Quickstop
     *
     * @param ui8Channel - selected Axis 1/2
     * @return the quickstop deceleration value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getQuickDecel(UINT8 ui8Channel);

    /**
     * Set value of following Error
     *
     * @param ui8Channel - selected Axis 1/2
     * @param ui32Value - Setvalue
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setErrorWindow(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read the permissible maximum size of the position lag
     *
     * @param ui8Channel - selected Axis 1/2
     * @return the position lag information
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getErrorWindow(UINT8 ui8Channel);

    /**
     * Set maximum Frequency
     * Channel must be in U/F Mode
     *
     * @param ui8Channel - selected Axis 1/2
     * @param ui32Value - Setvalue
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMaxFrequency(UINT8 ui8Channel, UINT32 ui32Value);

    /**
     * Read maximum Frequency
     * Channel must be in U/F Mode
     *
     * @param ui8Channel - selected Axis 1/2
     * @return the maximum frequency value
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getMaxFrequency(UINT8 ui8Channel);

    /**
     * Read State History
     * The last 6 Statechanges are logged
     *
     * @param ui8Channel - selected Axis 1/2
     * @return a pointer to the history state structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SStateHistory_t* getStateHistory(UINT8 ui8Channel);

    /**
     * Read Errorcode from Module
     * Value is only available if Someone is attached to
     * at least one Errorinterrupt
     *
     * @param ui8Channel - selected Axis 1/2
     * @return error code
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getErrorCode(UINT8 ui8Channel);

    /**
     * Read State of Reference Input
     *
     * @param ui8Channel - selected Axis 1/2
     * @return reference switch state
     * 			TRUE = Active
     *          FALSE = Inactive
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getReferenceSwitchState(UINT8 ui8Channel);

    /**
     * Read State of all Inputs
     *
     * @param ui8Channel - selected Axis 1/2
     * @return pointer to input switch state structure
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SDigitalInput_t* getSwitchState(UINT8 ui8Channel);

    /**
     * Read State of zero-pulse from Encoder
     *
     * @param ui8Channel - selected Axis 1/2
     * @return zero state pulse
     * 			TRUE = Active
     *          FALSE = Inactive

     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8 getZeroState(UINT8 ui8Channel);

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
     * Attach to Reset Interrupt
     * call enableReset(...) to activate
     *
     * @param pSession - Event Session from System
     * @param ui8Channel - selected Axis 1/2
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
        return BasicIoModule::TYPE_ACR2XX;
    }

    /**
     * Build State from given Value
     *
     * History is copied into one 32-Bit Variable
     * There are 6 entries (e) and a 16 Bit Counter (c)
     * each entry contains 4 Status Bits
     *
     * 32                                       0
     *   cccc cccc eeee eeee eeee eeee eeee eeee
     *
     */
    VOID buildState(SState_t* psState, UINT32 ui32Value, UINT8 ui8Index);

    /**
     * Build Counter from given Value
     *
     * History is copied into one 32-Bit Variable
     * There are 6 entries (e) and a 16 Bit Counter (c)
     * each entry contains 4 Status Bits
     *
     * 32                                       0
     *   cccc cccc eeee eeee eeee eeee eeee eeee
     *
     */
    VOID buildCounter(UINT8* pui8Counter, UINT32 ui32Value);

private:
    SProfile_t m_Profile;
    SHome_t m_Homing;
    SDriveData_t m_DriveData;
    SResolution_t m_Resoultion;
    SSettings_t m_Setting;
    SStateHistory_t m_StateHistory;
    SDigitalInput_t m_SwitchState;
    SStatusword_t m_StatusWord;
};

#endif /** ACR2XX_HPP_ */
