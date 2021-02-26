/**
 ********************************************************************************
 * @file     BasicIoModule.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicIoModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CBASICIOMODULEWITHEXCEPTION_HPP_
#define CBASICIOMODULEWITHEXCEPTION_HPP_


/**********************************************************************
 * system includes
 **********************************************************************/
#include <mio_e.h>
#include <mtypes.h>
#include <map>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "MIOerrorcode.hpp"
#include "../EventSession.hpp"
#include "../ErrorSession.hpp"
#include "../base/BasicEventListener.hpp"
#include "../base/BasicErrorListener.hpp"
#include "../mio/configuration/IOStrategy.hpp"
#include "MIOSystem.hpp"
#include "MIOexception.hpp"

/**********************************************************************
 * forward declaration
 **********************************************************************/
class BasicChannel;
class IOStrategy;

/**
 * check if specified Bits are set
 *
 * x = Value to check
 * y = Bitpattern
 */
#define BitCheck(value, pattern) ( (value & pattern) == pattern ? TRUE : FALSE )

/**
 * @brief Base Class for all IO-Modules
 *
 * Constructor is protected and therefor can only \n
 * be called von derived classes
 */
class BasicIoModule
{

    friend class BasicChannel;
    friend class AnalogChannel;
    friend class DigitalChannel;
    friend class ProcessImageIOStrategy;
    friend class StdIOStrategy;

public:

    static const SINT32 TYPE_UNKNOWN;

    static const SINT32 TYPE_DI212;
    static const SINT32 TYPE_DI216;
    static const SINT32 TYPE_DI232;

    static const SINT32 TYPE_DO216;
    static const SINT32 TYPE_DO232;
    static const SINT32 TYPE_DOR2XX;

    static const SINT32 TYPE_DIO216;
    static const SINT32 TYPE_DIO232;
    static const SINT32 TYPE_DIO2XX;
    static const SINT32 TYPE_DIO280;

    static const SINT32 TYPE_AI204;
    static const SINT32 TYPE_AI20XSI;

    static const SINT32 TYPE_AO202;
    static const SINT32 TYPE_AO20XSI;
    static const SINT32 TYPE_AO208;

    static const SINT32 TYPE_AIO2XX;
    static const SINT32 TYPE_AIO288;

    static const SINT32 TYPE_PTAI216;
    static const SINT32 TYPE_TI214;

    static const SINT32 TYPE_DMS202;
    static const SINT32 TYPE_AIC212;
    static const SINT32 TYPE_GIO212;

    static const SINT32 TYPE_CNT204;
    static const SINT32 TYPE_ISI222;
    static const SINT32 TYPE_ACR2XX;
    static const SINT32 TYPE_PWM202;
    static const SINT32 TYPE_RS204;

    static const SINT32 TYPE_GMP232;
    static const SINT32 TYPE_GMP232x;
    static const SINT32 TYPE_GM2XX;
    static const SINT32 TYPE_GSP274;

    static const SINT32 TYPE_BCH200;

    static const SINT32 TYPE_MBM201;
    static const SINT32 TYPE_PN201;
    static const SINT32 TYPE_CAN;
    static const SINT32 TYPE_ECAT201;
    static const SINT32 TYPE_OPCUAS;
    static const SINT32 TYPE_DA3284C;
    static const SINT32 TYPE_S60870_5;
    static const SINT32 TYPE_MMSCNLT;
    static const SINT32 TYPE_DNP3;

    /**
     *  possible errorcodes
     */
    enum EError_t
    {
        /** unspecified Update your Lib */
        eUnknown,
        /** No error */
        eOK,
        /** Module is on Bad Station */
        eBADSTATION,
        /** Ext./int. power failure */
        ePOWER,
        /** Open In/Out circuit */
        eBROKENWIRE,
        /** Short In/Out circuit */
        eSHORTCIRC,
        /** Temperature too high */
        eTEMPTOOHI,
        /** Decoder/Encoder error */
        eDECODER,
        /** Channel is disabled */
        eCHANDISABLED,
        /** Configuration not valid */
        eBADCONFIG,
        /** Internal watchdog error */
        eWATCHDOG,
        /** External error */
        eEXTERNAL,
        /** Module alive test failed */
        eDEAD,
        /** Output is disabled */
        eOUTDISABLED,
        /** External voltage too high */
        eVOLTAGETOHI,
        /** External voltage too low */
        eVOLTAGETOLO,
        /** Output current too high */
        eCURRENTTOHI,
        /** Profile not valid */
        eBADPROFILE
    //eSYSTEM,              /**< Generic errors */
    //eUSER                 /**< Driver specific error */
    };

    /**
     * Information about Card
     */
    typedef MIO_CARDINF SInfo_t;

    /**
     * Extended information about Card
     */
    typedef MIO_EXTCDINF SExtInfo_t;

    /**
     * Extended information 2 about Card
     */
    typedef MIO_EXTCDINF2 SExtInfo2_t;

    /**
     * map with all available channels
     */
    typedef std::map<UINT32, BasicChannel*> ChannelList_t;

    void setIoSystem(MIOSystem *pMioSystem) {m_pMioSystem = pMioSystem;};

protected:

    /** Parameterlist for DoCommands */
    typedef SINT32 PARAMETERLIST[6];
    /** Identifier for Card */
    VOID* m_pDriverId;
    /** Card Number  */
    UINT32 m_ui32CardNumber;
    /** Info about Card  */
    MIO_CARDINF m_CardInfo;
    /** returnvalue from MIO-functions  */
    SINT32 m_si32Error;
    /** Array of Channels, should be build in inherited class  */
    ChannelList_t m_ChannelList;

    /** Access to the MIO system of the M1 controller */
    MIOSystem *m_pMioSystem;

    /**
     * Read Type ID
     *
     * must be implemented by derived class
     */
    virtual SINT32 getTypeId(VOID) = 0;

    /**
     * Initialize the module.
     *
     * Function is called by base class when cardnumber is set.
     */
    virtual void initInternal() = 0;

    /**
     * @brief Default Constructor
     */
    BasicIoModule();

    /**
     * @brief Constructor
     *
     * @param CardNumber configured Cardnumber
     *
     * @throws a MIOexception when card number has already been initialized,
     * or a MIOexception when the card number is invalid,
     * or a MIOexception when getting driver id from card fails,
     * or a MIOexception if getting card information fails.
     */
    explicit BasicIoModule(UINT32 CardNumber);


    /**
     * @brief Constructor
     *
     * @param CardNumber configured Cardnumber
     * @param pSystem A way of defining how the MIO system should work
     * @throws a MIOexception when card number has already been initialized,
     * or a MIOexception when the card number is invalid,
     * or a MIOexception when getting driver id from card fails,
     * or a MIOexception if getting card information fails.
     */
    explicit BasicIoModule(UINT32 CardNumber, MIOSystem *pSystem);

    /**
     * @brief Read Driver ID
     */
    VOID* getDriverId(VOID);

    /**
     * @brief get selected Channel
     * @return return pointer channel class
     *
     * @throws a MIOexception when channel list is empty
     * or a MIOexception when channel is not found in the channel list!
     */
    BasicChannel* getBasicChannel(UINT32 ui32Channel);

    /**
     * @brief Get number of channels for the card
     * @return return number of channels
     *
     */
    UINT32 getNbOfChannels();

    /**
     * @brief Execute Special Operations on IO-Module
     *
     * @param ui32Command - Command Code see MIO_CMD_xxx
     * @param ui32Channel - Channelnumber or 0
     *
     * @throws a MIOexception when execution of mio_doCmd fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID doCommmand(UINT32 ui32Command, UINT32 ui32Channel);

    /**
     * @brief Execute Special Operations on IO-Module
     *
     * @param ui32Command - Command Code see MIO_CMD_xxx
     * @param ui32Channel - Channelnumber or 0
     * @param si32Value - Value for command
     *
     * @throws a MIOexception when execution of mio_doCmd fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID doCommmand(UINT32 ui32Command, UINT32 ui32Channel, SINT32 si32Value);

    /**
     * @brief Execute Special Operations on IO-Module
     *
     * @param ui32Command - Command Code see MIO_CMD_xxx
     * @param ui32Channel - Channelnumber or 0
     * @param pParameter - List of Parameters
     * @param ui8Size - Number of used Parameters
     *
     * @throws a MIOexception when execution of mio_doCmd fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID doCommmand(UINT32 ui32Command, UINT32 ui32Channel, PARAMETERLIST *pParameter,
            UINT8 ui8Size);

    /**
     * @brief Sets an IOStrategy for the Module. THis means, it will notify the
     * Module when a value is changed.
     *
     */
    void setIOStrategy(IOStrategy *pIOStrategy);

    /**
     * @brief Sets value internally. This functions is for internal use only.
     *
     * @param ui32Channel - Channelnumber starting from 1
     * @param si32Value - Value to be set
     * @param setDirtyflag - Whether or nor to notify the IOStrategy
     *
     * @throws a MIOexception when channel value is invalid.
     */
    virtual void setValueInternal(UINT32 ui32Channel, SINT32 si32Value,
            BOOL8 setDirtyflag = FALSE) = 0;

    /**
     * @brief Evaluates if module can be read from according to current error code
     *
     * throws a MIOexception if read is not possible
     */
    VOID checkReadState();

    /**
     * @brief Evaluates if module can be written to, according to current error code
     *
     * throws a MIOexception if write is not possible
     */
    VOID checkWriteState();

public:

    void initBase();

    /**
     * @brief Default Destructor
     */
    virtual ~BasicIoModule();

    /**
     * @brief Set Cardnumber if Default Constructor
     *        was used
     *
     * @param ui32CardNumber configured Cardnumber
     *
     * @throws a MIOexception when card number has already been initialized,
     * or a MIOexception when the card number is invalid,
     * or a MIOexception when getting driver id from card fails,
     * or a MIOexception if getting card information fails.
     */
    VOID setCardNumber(UINT32 ui32CardNumber);

    /**
     * @brief Reset Module
     *
     * @throws a MIOexception when resetting card fails,
     * or a MIOexception if pointer to card is invalid
     * */
    VOID reset(VOID);

    /**
     * @brief Read Last Error from MIO-Functions
     *
     * @see constants MIO_E_ from mio.h
     */
    SINT32 getMioError(VOID);

    /**
     * @brief Get Infostructure of Channel
     *
     * @throws a MIOexception when getting info from card fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @returns pointer to SInfo_t (get card info)
     * @throws a MIOexception when failing to get card infomation from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BasicIoModule::SInfo_t* getInfo(VOID);

    /**
     * @brief Get extenden info structure of Channel
     *
     * @throws a MIOexception when getting info from card fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @returns pointer to SExtInfo_t (get card info)
     * @throws a MIOexception when failing to get card infomation from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BasicIoModule::SExtInfo_t* getExtInfo(VOID);

    /**
     * @brief Get Extended info structure 2 of Channel
     *
     * @throws a MIOexception when getting extended info 2 from card fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @returns pointer to SInfo_t (get card info)
     * @throws a MIOexception when failing to get card infomation from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BasicIoModule::SExtInfo2_t* getExtInfo2(VOID);

   /**
     * \brief Get driver version number
     *
     * \throws a MIOexception when getting driver version number fails
     *
     * \returns pointer to MIO_VERSION
     * \throws a MIOexception when failing to get driver version number
     */
	MIO_VERSION* getVersion(VOID);
	
    /**
     * @brief Check if Module is Really existing
     *
     * @returns FALSE Card is not in REAL Mode
     * @returns TRUE Card is in REAL Mode
     */
    BOOL8 isCardReal(VOID);

    /**
     * @brief Check if Module is simulated
     *
     * Inputs are NOT writeable!
     *
     * @returns FALSE Card is not in Virtual Mode
     * @returns TRUE Card is in Virtual Mode
     */
    BOOL8 isCardVirtual(VOID);

    /**
     * @brief Check if Module is simulated
     *
     * Inputs are writeable!
     *
     * @returns FALSE Card is not in Virtual RW Mode
     * @returns TRUE Card is in Virtual RW Mode
     */
    BOOL8 isCardVirtualRW(VOID);

    /**
     * @brief Check if found Card matches to local
     *
     * The check is only active if it is calls from \n
     * application. The Library does not call it!
     *
     * @throws a MIOexception when card type does not match selected type
     *
     * @see getTypeId
     */
    VOID checkCardType(VOID);

    /**
     * @brief Set Mode of Channel
     *
     * @throws a MIOexception when failing to set mode to card fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @param ui32Value - Value to Set
     *
     * @throws a MIOexception when failing to set mode to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMode(UINT32 ui32Value);

    /**
     * @brief Get Mode of Channel
     *
     * @throws a MIOexception when failing to get mode from card fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @return card mode.
     *
     * @throws a MIOexception when failing to get mode from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getMode();

    /**
     * @brief Get Card Number of Module
     *
     * @returns Cardnumber
     */
    UINT32 getCardNumber(VOID);

    /**
     * @brief Read internal Errorstate of Module, updated by process image
     *
     * @returns pointer to EError_t
     *
     * @throws a MIOexception when failing to get error information from the card.
     */
    BasicIoModule::EError_t* getError(VOID);

    UINT32 getErrorAsUint32(VOID);

    /**
     * @brief Read Errorstate of Module
     *
     * @returns pointer to EError_t
     *
     * @throws a MIOexception when failing to get error information from the card.
     */
    BasicIoModule::EError_t* getError(BOOL8 Update);


    UINT32 getErrorAsUint32(BOOL8 Update);

    /**
     * @brief Returns whether module is digital or not
     */
    virtual BOOL8 isDigitalModule() = 0;

    /**
     * @brief Returns whether module is mixed or not.
     *
     * A mixed module indicates that it can have both Analog and
     * digital channels.
     */
    virtual BOOL8 isMixedModule() = 0;

    /**
     * @brief Returns datatype for the channel.
     *
     */
    UINT32 getChannelDatatype(UINT32 channelNb);

    /**
     * @brief Returns data size for the channel in bytes.
     *
     */
    UINT32 getChannelDataSize(UINT32 channelNb);

    /**
     * @brief Sets the MIO system
     *
     */
    void setMIOSystem(MIOSystem *pSystem);


    /**
     * @brief Gets the configured MIO system
     *
     */
    MIOSystem* getMIOSystem()
    {
        return m_pMioSystem;
    }

protected:



    /**
     * @brief set Driver ID
     *
     * @see CProcessimage::addCard
     *
     * @param pDriverId Handle of Driver
     */
    VOID setDriverId(VOID* pDriverId);

    /**
     * Attach for Event interrupts
     *
     * @param pSession      Handle of Session
     * @param ui32Channel   Number of Channel to attach
     * @param ui32EventType Eventtype to attach
     * @param pListener     Pointer to Listener Interface
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachEvent(EventSession* pSession, UINT32 ui32Channel, UINT32 ui32EventType,
            BasicEventListener *pListener = NULL);

    /**
     * Detach Event interrupts
     *
     * @param pSession      Handle of Session
     * @param ui32Channel   Number of Channel to attach
     * @param ui32EventType Eventtype to attach
     *
     * @throws a MIOexception when detaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID detachEvent(EventSession* pSession, UINT32 ui32Channel, UINT32 ui32EventType);

    /**
     * Attach for Error interrupts
     *
     * @param pSession      Handle of Session
     * @param ui32Channel   Number of Channel to attach
     * @param ui32ErrorType Eventtype to attach
     * @param pListener     Pointer to Listener Interface
     *
     * @throws a MIOexception when attaching error to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachError(ErrorSession* pSession, UINT32 ui32Channel, UINT32 ui32ErrorType,
            BasicErrorListener* pListener = NULL);

    void markAsDirty();
    /**
     * Detach Error interrupts
     *
     * @param pSession      Handle of Session
     * @param ui32Channel   Number of Channel to attach
     * @param ui32ErrorType Eventtype to attach
     *
     * @throws a MIOexception when detaching error to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID detachError(ErrorSession* pSession, UINT32 ui32Channel, UINT32 ui32ErrorType);

private:
    IOStrategy *m_pIOStrategy;

    virtual VOID createChannels(VOID) = 0;

    void setCardNumberInternal(UINT32 ui32CardNumber);


    /**-----------------------------------------------------------------*/

    EError_t m_eError;
    UINT32 m_Error;

    SInfo_t m_SInfo;
    SExtInfo_t m_SExtInfo;
    SExtInfo2_t m_SExtInfo2;
	MIO_VERSION m_VerStruct;
};

/**********************************************************************
 * INLINE METHODS
 **********************************************************************/

/**-----------------------------------------------------------------*/
inline BOOL8 BasicIoModule::isCardReal(VOID)
{
    MIO_DRV* l_pCard = (MIO_DRV*) m_pDriverId;

    if (NULL == l_pCard)
    {
        return FALSE;
    }

    return BitCheck(l_pCard->Mode, MIO_REAL);
}

/**-----------------------------------------------------------------*/
inline BOOL8 BasicIoModule::isCardVirtual(VOID)
{
    MIO_DRV* l_pCard = (MIO_DRV*) m_pDriverId;

    if (NULL == l_pCard)
    {
        return FALSE;
    }

    return BitCheck(l_pCard->Mode, MIO_VIRTUAL);
}

/**-----------------------------------------------------------------*/
inline BOOL8 BasicIoModule::isCardVirtualRW(VOID)
{
    MIO_DRV* l_pCard = (MIO_DRV*) m_pDriverId;

    if (NULL == l_pCard)
    {
        return FALSE;
    }

    return BitCheck(l_pCard->Mode, MIO_VIRTUALRW);
}

/**-----------------------------------------------------------------*/
inline UINT32 BasicIoModule::getCardNumber(VOID)
{
    return m_ui32CardNumber;
}

/**-----------------------------------------------------------------*/
inline BasicIoModule::EError_t* BasicIoModule::getError(VOID)
{
    return(&m_eError);
}

/**-----------------------------------------------------------------*/
inline BasicIoModule::EError_t* BasicIoModule::getError(BOOL8 Update)
{
    UINT32 l_ui32Error = MIO_E_OK;

    m_si32Error = m_pMioSystem->getError(m_pDriverId, 0, &l_ui32Error);
    if (OK != m_si32Error)
    {
        throw MIOexception("BasicIoModule::getError: failed to get error information",
                m_ui32CardNumber, m_si32Error);
    }

    /**
     * do mapping between MIO_Error
     * and Enum
     */
    m_Error = l_ui32Error;  // Update raw error value
    switch (l_ui32Error)
    {
    case (MIO_E_OK):
        m_eError = eOK;
        break;
    case (MIO_E_BADSTATION):
        m_eError = eBADSTATION;
        break;
    case (MIO_E_POWER):
        m_eError = ePOWER;
        break;
    case (MIO_E_BROKENWIRE):
        m_eError = eBROKENWIRE;
        break;
    case (MIO_E_SHORTCIRC):
        m_eError = eSHORTCIRC;
        break;
    case (MIO_E_TEMPTOOHI):
        m_eError = eTEMPTOOHI;
        break;
    case (MIO_E_DECODER):
        m_eError = eDECODER;
        break;
    case (MIO_E_CHANDISABLED):
        m_eError = eCHANDISABLED;
        break;
    case (MIO_E_BADCONFIG):
        m_eError = eBADCONFIG;
        break;
    case (MIO_E_WATCHDOG):
        m_eError = eWATCHDOG;
        break;
    case (MIO_E_EXTERNAL):
        m_eError = eEXTERNAL;
        break;
    case (MIO_E_DEAD):
        m_eError = eDEAD;
        break;
    case (MIO_E_OUTDISABLED):
        m_eError = eOUTDISABLED;
        break;
    case (MIO_E_VOLTAGETOHI):
        m_eError = eVOLTAGETOHI;
        break;
    case (MIO_E_VOLTAGETOLO):
        m_eError = eVOLTAGETOLO;
        break;
    case (MIO_E_CURRENTTOHI):
        m_eError = eCURRENTTOHI;
        break;
    case (MIO_E_BADPROFILE):
        m_eError = eBADPROFILE;
        break;

    default:
        m_eError = eUnknown;
    }
    return &m_eError;
}

/**-----------------------------------------------------------------*/
inline UINT32 BasicIoModule::getErrorAsUint32(VOID)
{
    return(m_Error);
}

inline UINT32 BasicIoModule::getErrorAsUint32(BOOL8 Update)
{
    UINT32 l_ui32Error = MIO_E_OK;

    m_si32Error = m_pMioSystem->getError(m_pDriverId, 0, &l_ui32Error);
    if (OK != m_si32Error)
    {
        throw MIOexception("BasicIoModule::getError: failed to get error information",
                m_ui32CardNumber, m_si32Error);
    }

    m_Error = l_ui32Error;

    return(m_Error);
}

#endif /** CBASICIOMODULEWITHEXCEPTION_HPP_ */
