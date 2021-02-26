/**
 ********************************************************************************
 * @file     BasicIoModule.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicIoModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "BasicIoModule.hpp"
#include "BasicChannel.hpp"
#include <string.h>
#include <stdexcept>
#include <iostream>
#include "M1MIOSystem.hpp"

const SINT32 BasicIoModule::TYPE_UNKNOWN = -1;
/** Digital Inputs */
const SINT32 BasicIoModule::TYPE_DI212 = MIO_T_DI212;
const SINT32 BasicIoModule::TYPE_DI216 = MIO_T_DI216;
const SINT32 BasicIoModule::TYPE_DI232 = MIO_T_DI232;
/** Digital Outputs */
const SINT32 BasicIoModule::TYPE_DO216 = MIO_T_DO216;
const SINT32 BasicIoModule::TYPE_DO232 = MIO_T_DO232;
const SINT32 BasicIoModule::TYPE_DOR2XX = MIO_T_DOR2XX;
/** Digital In/Out-Modules */
const SINT32 BasicIoModule::TYPE_DIO216 = MIO_T_DIO216;
const SINT32 BasicIoModule::TYPE_DIO232 = MIO_T_DIO232;
const SINT32 BasicIoModule::TYPE_DIO280 = MIO_T_DIO280;
const SINT32 BasicIoModule::TYPE_DIO2XX = MIO_T_DIO2XX;

const SINT32 BasicIoModule::TYPE_AI204 = MIO_T_AI204;
const SINT32 BasicIoModule::TYPE_AI20XSI = MIO_T_AI20XSI;

const SINT32 BasicIoModule::TYPE_AO202 = MIO_T_AO202;
const SINT32 BasicIoModule::TYPE_AO20XSI = MIO_T_AO20XSI;
const SINT32 BasicIoModule::TYPE_AO208 = MIO_T_AO208;

const SINT32 BasicIoModule::TYPE_AIO2XX = MIO_T_AIO2XX;
const SINT32 BasicIoModule::TYPE_AIO288 = MIO_T_AIO288;

const SINT32 BasicIoModule::TYPE_PTAI216 = MIO_T_PTAI216;
const SINT32 BasicIoModule::TYPE_TI214 = MIO_T_TI214;
const SINT32 BasicIoModule::TYPE_DMS202 = MIO_T_DMS202;
const SINT32 BasicIoModule::TYPE_AIC212 = MIO_T_AIC2XX;
const SINT32 BasicIoModule::TYPE_GIO212 = MIO_T_GIO2XX;

const SINT32 BasicIoModule::TYPE_CNT204 = MIO_T_CNT204;
const SINT32 BasicIoModule::TYPE_ISI222 = MIO_T_ISI202;
const SINT32 BasicIoModule::TYPE_ACR2XX = MIO_T_ACR222;
const SINT32 BasicIoModule::TYPE_PWM202 = MIO_T_PWM202;
const SINT32 BasicIoModule::TYPE_RS204 = MIO_T_RS204;

const SINT32 BasicIoModule::TYPE_GMP232 = MIO_T_GMP232;
const SINT32 BasicIoModule::TYPE_GMP232x = MIO_T_GMP232X;
const SINT32 BasicIoModule::TYPE_GM2XX = MIO_T_GM2XX;
const SINT32 BasicIoModule::TYPE_GSP274 = MIO_T_GSP274;

const SINT32 BasicIoModule::TYPE_BCH200 = MIO_T_BCH200;

const SINT32 BasicIoModule::TYPE_MBM201 = MIO_T_MBM201;
const SINT32 BasicIoModule::TYPE_PN201 = MIO_T_PN201;
const SINT32 BasicIoModule::TYPE_CAN = MIO_T_CAN;
const SINT32 BasicIoModule::TYPE_ECAT201 = MIO_T_ECAT201;
const SINT32 BasicIoModule::TYPE_OPCUAS = MIO_T_OPCUAS;
const SINT32 BasicIoModule::TYPE_S60870_5 = MIO_T_S60870_5;
const SINT32 BasicIoModule::TYPE_MMSCNLT = MIO_T_MMSCNLT;
const SINT32 BasicIoModule::TYPE_DNP3 = MIO_T_DNP3;


const SINT32 BasicIoModule::TYPE_DA3284C = MIO_T_DA3284C;

/**-----------------------------------------------------------------*/
BasicIoModule::BasicIoModule() : m_pMioSystem(NULL)
{
    initBase();
}

/**-----------------------------------------------------------------*/
BasicIoModule::BasicIoModule(UINT32 CardNumber) : m_pMioSystem(NULL)
{
    initBase();
    setCardNumberInternal(CardNumber);
}



/**-----------------------------------------------------------------*/

/**-----------------------------------------------------------------*/
BasicIoModule::BasicIoModule(UINT32 CardNumber, MIOSystem *pSystem) : m_pMioSystem(pSystem)
{
    initBase();
    setCardNumberInternal(CardNumber);
}



/**-----------------------------------------------------------------*/
BasicIoModule::~BasicIoModule()
{
    /** Ignore exception */
    BasicIoModule::ChannelList_t::iterator it;
    for (it = m_ChannelList.begin(); it != m_ChannelList.end(); ++it)
    {
        SAFE_DELETE(it->second);
    }

    m_ChannelList.clear();
    /** do not have to delete m_pDriverId */

    SAFE_DELETE(m_pMioSystem);
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::initBase(VOID)
{
    m_pDriverId = NULL;
    m_ui32CardNumber = 0;
    m_si32Error = 0;
    m_pIOStrategy = NULL;
    memset(&m_SInfo, 0, sizeof(m_SInfo));
    memset(&m_SExtInfo, 0, sizeof(m_SExtInfo));
    memset(&m_SExtInfo2, 0, sizeof(m_SExtInfo2));
    memset(&m_eError, 0, sizeof(m_eError));
    memset(&m_CardInfo, 0, sizeof(m_CardInfo));
    m_pIOStrategy = NULL;

    //Default handling of the MIO system is the 'real' system.
    if(m_pMioSystem == NULL){
        m_pMioSystem = new M1MIOSystem();
    }
}

VOID BasicIoModule::checkReadState() {
    //Add additional checks which makes sense (related to card type..)
    if (m_Error == MIO_E_DEAD)
    {
        throw MIOexception("Cannot read from a card which has state 'Dead'", m_ui32CardNumber, MIO_E_DEAD);
    }
}

VOID BasicIoModule::checkWriteState() {
    //Add additional checks which makes sense (related to card type..)
    if (m_Error == MIO_E_DEAD)
    {
        throw MIOexception("Cannot write to a card which has state 'Dead'", m_ui32CardNumber, MIO_E_DEAD);
    }
}

VOID BasicIoModule::setCardNumberInternal(UINT32 ui32CardNumber)
{
    /** enable set only once! */
    if (0 != m_ui32CardNumber)
    {
        throw std::invalid_argument(
                "BasicIoModule::setCardNumber: Card number was already initialized. Please only call setCardNumber once.");
    }

    if (0 == ui32CardNumber)
    {
        throw MIOexception("BasicIoModule::setCardNumber: invalid parameter ", ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_ui32CardNumber = ui32CardNumber;

    m_pDriverId = m_pMioSystem->getDrv(ui32CardNumber);

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::setCardNumber: failed to get driver id ", ui32CardNumber,
                MIO_ER_BADCARD);
    }

    /**
     * Check if a card is found at given cardnumber
     * and Type is correct. If type is not the same
     * this instance will not work!
     */

    m_si32Error = m_pMioSystem->getCardInf(m_pDriverId, &m_CardInfo);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::setCardNumber: failed to get card info("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), ui32CardNumber, m_si32Error);
    }

}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::setCardNumber(UINT32 ui32CardNumber)
{
    setCardNumberInternal(ui32CardNumber);

    /** We need to initialize the object now. This will call the virtual function. */
    initInternal();
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::reset(VOID)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::reset: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->reset(m_pDriverId);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::reset: failed to reset card("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::setMode(UINT32 ui32Value)
{

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::setMode: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->setCardMode(m_pDriverId, ui32Value);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::setMode: failed to set card mode("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error, ui32Value);
    }
}

/**-----------------------------------------------------------------*/
UINT32 BasicIoModule::getMode(VOID)
{
    UINT32 m_CardMode;

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::getMode: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->getCardMode(m_pDriverId, &m_CardMode);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::getMode: failed to get card mode("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error);
    }
    return m_CardMode;
}

/**-----------------------------------------------------------------*/
SINT32 BasicIoModule::getMioError(VOID)
{
    return m_si32Error;
}

/**-----------------------------------------------------------------*/
void* BasicIoModule::getDriverId(VOID)
{
    return m_pDriverId;
}

/**-----------------------------------------------------------------*/
void BasicIoModule::setDriverId(VOID *pDriverId)
{
    m_pDriverId = pDriverId;
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::doCommmand(UINT32 ui32Command, UINT32 ui32Channel)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::doCommmand: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::doCommmand: failed to execute do command("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, ui32Command, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::doCommmand(UINT32 ui32Command, UINT32 ui32Channel, SINT32 si32Value)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::doCommmand: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, si32Value);

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::doCommmand: failed to execute do command("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, ui32Command, m_si32Error,
                (UINT32) si32Value);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::doCommmand(UINT32 ui32Command, UINT32 ui32Channel, PARAMETERLIST *pParameter,
        UINT8 ui8Size)
{
    PARAMETERLIST l_Parameter;

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::doCommmand: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    memcpy(&l_Parameter[0], pParameter, sizeof(PARAMETERLIST));

    switch (ui8Size)
    {
        case 1:
            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0]);
            break;
        case 2:

            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0], l_Parameter[1] );
            break;

        case 3:
            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0], l_Parameter[1], l_Parameter[2]);
            break;

        case 4:
            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0], l_Parameter[1], l_Parameter[2], l_Parameter[3]);
            break;

        case 5:
            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0], l_Parameter[1], l_Parameter[2], l_Parameter[3], l_Parameter[4]);
            break;

        case 6:
            m_si32Error = m_pMioSystem->doCmd(m_pDriverId, ui32Channel, ui32Command, l_Parameter[0], l_Parameter[1], l_Parameter[2], l_Parameter[3], l_Parameter[4], l_Parameter[5]);
            break;

        default:
            std::stringstream msg;
            msg << "BasicIoModule::doCommmand: Invalid Index (" << ui8Size << ") of ParameterList.";
            throw std::invalid_argument(msg.str());

    }

    if (MIO_E_OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::doCommmand: failed to execute do command("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, ui32Command, m_si32Error);
    }
}

void BasicIoModule::setIOStrategy(IOStrategy *pIOStrategy)
{
    m_pIOStrategy = pIOStrategy;
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::attachEvent(EventSession* pSession, UINT32 ui32Channel, UINT32 ui32EventType,
        BasicEventListener *pListener)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::attachEvent: invalid driver id", m_ui32CardNumber,
                ui32Channel, MIO_ER_BADPARM);
    }

//    //lint -e{1717}
//            (VOID (*)())EventSession::EventISR, (UINT32)pListener);
    m_si32Error = m_pMioSystem->attachEvent(m_pDriverId, pSession->getSessionId(), ui32Channel, ui32EventType,
        //lint -e{1717}
                (VOID (*)())EventSession::EventISR, (UINT32)pListener);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::attachEvent: failed to attach event("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::detachEvent(EventSession* pSession, UINT32 ui32Channel, UINT32 ui32EventType)
{
    m_si32Error = m_pMioSystem->detachEvent(m_pDriverId, pSession->getSessionId(), ui32Channel, ui32EventType);
    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::detachEvent: failed to detach event("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, m_si32Error);
    }

}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::attachError(ErrorSession* pSession, UINT32 ui32Channel, UINT32 ui32ErrorType,
        BasicErrorListener* pListener)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::attachError: invalid driver id", m_ui32CardNumber,
                ui32Channel, MIO_ER_BADPARM);
    }

//    //lint -e{1717}
//            (VOID (*)())ErrorSession::ErrorISR, (UINT32)pListener);


    m_si32Error = m_pMioSystem->attachError(m_pDriverId, pSession->getSessionId(), ui32Channel, ui32ErrorType,
    (VOID (*)())ErrorSession::ErrorISR, (UINT32)pListener);


    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::attachError: failed to attach event("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::detachError(ErrorSession* pSession, UINT32 ui32Channel, UINT32 ui32ErrorType)
{
    m_si32Error = m_pMioSystem->detachError(m_pDriverId, pSession->getSessionId(), ui32Channel, ui32ErrorType);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::detachError: failed to detach event("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, ui32Channel, m_si32Error);
    }
}

UINT32 BasicIoModule::getChannelDatatype(UINT32 channelNb) {
    MIO_CHAN_RANGE chanRange;
    m_pMioSystem->findChanRange((MIO_DRV*)m_pDriverId, channelNb, &chanRange);
    return chanRange.Format;
}

UINT32 BasicIoModule::getChannelDataSize(UINT32 channelNb) {
    MIO_CHAN_RANGE chanRange;
    m_pMioSystem->findChanRange((MIO_DRV*)m_pDriverId, channelNb, &chanRange);
    return chanRange.len;
}

void BasicIoModule::setMIOSystem(MIOSystem *pSystem) {
    SAFE_DELETE(m_pMioSystem);
    m_pMioSystem = pSystem;
}

/**-----------------------------------------------------------------*/
BasicChannel* BasicIoModule::getBasicChannel(UINT32 ui32Channel)
{
    BasicIoModule::ChannelList_t::iterator it;

    if (m_ChannelList.empty())
    {
        throw MIOexception(
                "BasicIoModule::getBasicChannel: invalid configuration channel list size = 0",
                m_ui32CardNumber, ui32Channel, MIO_ER_BADCONF);
    }
    /**
     * ma_pChannel points to first channel.
     * Selected Channel (ui32Channel) is calculated as
     * offset to first channel.
     */
    if (ui32Channel > 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        it = m_ChannelList.find(ui32Channel);
        if (it == m_ChannelList.end())
        {
            throw MIOexception("BasicIoModule::getBasicChannel: channel not in channel list",
                    m_ui32CardNumber, ui32Channel, MIO_ER_BADCONF);
        }

        return it->second;
    }

    throw MIOexception(
            "BasicIoModule::getBasicChannel: invalid parameter channel number is invalid ",
            ui32Channel, MIO_ER_BADPARM);
}

/**-----------------------------------------------------------------*/
UINT32 BasicIoModule::getNbOfChannels()
{
    return(m_CardInfo.MaxChan);
}

/**-----------------------------------------------------------------*/
VOID BasicIoModule::checkCardType(VOID)
{
    if (m_CardInfo.Type == 0)
    {
        return; /** Not able to check card type since not initialized. (NOT an error) */
    }

    if (m_CardInfo.Type != this->getTypeId())
    {
        std::stringstream msg;
        msg << "BasicIoModule::BasicIoModule: Typecheck Failed! Found " << m_CardInfo.Type
                << " instead of " << this->getTypeId();
        m_pDriverId = NULL;
        throw MIOexception(msg.str(), m_ui32CardNumber, MIO_ER_BADTYPE);
    }
}

/**-----------------------------------------------------------------*/
BasicIoModule::SInfo_t* BasicIoModule::getInfo(VOID)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::getInfo: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->getCardInf(m_pDriverId, &m_SInfo);

    if (OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::getInfo: failed to get card info("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error);
    }

    return &m_SInfo;
}

void BasicIoModule::markAsDirty()
{
    if (m_pIOStrategy == NULL)
    {
        return;
    }
    m_pIOStrategy->markModuleAsDirty(this);
}
/**-----------------------------------------------------------------*/
BasicIoModule::SExtInfo_t* BasicIoModule::getExtInfo(VOID)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::getExtInfo: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->getExtCardInf(m_CardInfo.CardNb, &m_SExtInfo);

    if (OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::getExtInfo: failed to get card info("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error);
    }

    return &m_SExtInfo;
}

/**-----------------------------------------------------------------*/
BasicIoModule::SExtInfo2_t* BasicIoModule::getExtInfo2(VOID)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicIoModule::getExtInfo2: invalid driver id", m_ui32CardNumber,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pMioSystem->getExtCardInf2(m_CardInfo.CardNb, &m_SExtInfo2);

    if (OK != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicIoModule::getExtInfo2: failed to get card info(" << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_ui32CardNumber, m_si32Error);
    }

    return &m_SExtInfo2;
}

/* ----------------------------------------------------------------- */
MIO_VERSION* BasicIoModule::getVersion(VOID)
{
    PARAMETERLIST l_param;

    if (NULL == m_pDriverId)
    {
		throw MIOexception("BasicIoModule::getVersion: invalid driver id", m_ui32CardNumber, MIO_ER_BADPARM);
    }

    l_param[0] = (SINT32)&m_VerStruct;

    doCommmand(MIO_CMD_GETVERSION, 0, &l_param, 1);

    return &m_VerStruct;
}
