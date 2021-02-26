/**
 ********************************************************************************
 * @file     BasicChannel.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "BasicChannel.hpp"
#include "MIOSystem.hpp"
#include "string.h"

/**-----------------------------------------------------------------*/
BasicChannel::BasicChannel() :
        m_ui32Channel(0), m_pModule(NULL), m_si32Error(0), m_si32GetValue(0)
{
    memset(&chanRange, 0, sizeof(chanRange));
}

/**-----------------------------------------------------------------*/
BasicChannel::~BasicChannel()
{
}

/**-----------------------------------------------------------------*/
VOID BasicChannel::setBasicValue(SINT32 si32Value)
{
    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::setBasicValue: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }
    m_si32Error = m_pModule->m_pMioSystem->setValue(m_pModule->getDriverId(), m_ui32Channel, si32Value);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::setBasicValue: failed to write value to card("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicChannel::setActive(BOOL8 b8Active)
{
    UINT32 l_ui32Select = 0;

    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::setActive: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }

    if (TRUE == b8Active)
    {
        l_ui32Select = 1;
    }

    m_si32Error = m_pModule->m_pMioSystem->setSelect(m_pModule->getDriverId(), m_ui32Channel, l_ui32Select);
    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::setActive: failed to set active information to card("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
SINT32 BasicChannel::getBasicValue(VOID)
{

    SINT32 si32Value;

    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::getBasicValue: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pModule->m_pMioSystem->getValue(m_pModule->getDriverId(), m_ui32Channel, &si32Value);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::getBasicValue: failed to read value from card("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }

    return si32Value;
}

/**-----------------------------------------------------------------*/
UINT32 BasicChannel::getFormat()
{
    return (chanRange.Format);
}


/**-----------------------------------------------------------------*/
VOID BasicChannel::setMode(UINT32 ui32Value)
{
    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::setMode: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pModule->m_pMioSystem->setChanMode(m_pModule->getDriverId(), m_ui32Channel, ui32Value);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::setMode: failed to set channel mode("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }
}

/**-----------------------------------------------------------------*/
UINT32 BasicChannel::getMode(VOID)
{
    UINT32 ui32Value;
    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::getMode: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pModule->m_pMioSystem->getChanMode(m_pModule->getDriverId(), m_ui32Channel, &ui32Value);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::getMode: failed to get channel mode("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }

    return ui32Value;
}

/**-----------------------------------------------------------------*/
VOID BasicChannel::setChannelNumber(UINT32 ui32Channel)
{
    m_ui32Channel = ui32Channel;
}

/**-----------------------------------------------------------------*/
UINT32 BasicChannel::getChannelNumber(VOID)
{
    return m_ui32Channel;
}

/**-----------------------------------------------------------------*/
VOID BasicChannel::setParentModule(BasicIoModule* pModule)
{
    m_pModule = pModule;

    m_pModule->m_pMioSystem->findChanRange((MIO_DRV*)m_pModule->getDriverId(), m_ui32Channel, &chanRange);
}

/**-----------------------------------------------------------------*/
SINT32 BasicChannel::getMioError(VOID)
{
    return m_si32Error;
}

/**-----------------------------------------------------------------*/
BasicChannel::SInfo_t* BasicChannel::getInfo(VOID)
{
    if (NULL == m_pModule)
    {
        throw MIOexception("BasicChannel::getInfo: invalid module pointer", 0, m_ui32Channel,
                MIO_ER_BADPARM);
    }

    m_si32Error = m_pModule->m_pMioSystem->getChanInf(m_pModule->getDriverId(), m_ui32Channel, &m_SInfo);

    if (0 != m_si32Error)
    {
        std::stringstream msg;
        msg << "BasicChannel::getInfo: failed to get channel info("
                << MIOerrorcode::errorCodesLookup(m_si32Error) << ")";
        throw MIOexception(msg.str(), m_pModule->getCardNumber(), m_ui32Channel, m_si32Error);
    }

    return &m_SInfo;
}
