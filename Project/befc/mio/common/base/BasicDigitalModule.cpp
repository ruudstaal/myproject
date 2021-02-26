/**
 ********************************************************************************
 * @file     BasicDigitalModule.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicDigitalModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <iostream>
#include "BasicDigitalModule.hpp"
#include "mcpp.hpp"
#include <cstring>

/**-----------------------------------------------------------------*/
BasicDigitalModule::BasicDigitalModule() :
        BasicIoModule()
{
    initInternal();
}

/**-----------------------------------------------------------------*/
BasicDigitalModule::BasicDigitalModule(UINT32 ui32CardNumber) :
        BasicIoModule(ui32CardNumber)
{
    initInternal();
}

/**-----------------------------------------------------------------*/
BasicDigitalModule::~BasicDigitalModule()
{
    SAFE_DELETE(m_pValues);
}

/**-----------------------------------------------------------------*/
void BasicDigitalModule::initInternal(VOID)
{
    if (m_CardInfo.MaxChan == 0)
    {
        m_pValues = NULL;
    }
    else
    {
        m_pValues = new BOOL8[m_CardInfo.MaxChan];
        memset(m_pValues, 0, m_CardInfo.MaxChan);
    }

    createChannels();
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::createChannels(VOID)
{
    BasicChannel *l_pChannel = NULL;
    UINT32 i;

    if (0 == m_CardInfo.MaxChan)
    {
        return;
    }

    /** initalize Channels of Module */
    for (i = 0; i < m_CardInfo.MaxChan; ++i)
    {
        l_pChannel = new DigitalChannel();
        l_pChannel->setChannelNumber(i + 1);
        l_pChannel->setParentModule(this);

        m_ChannelList[i + 1] = l_pChannel;

    }
}

/**-----------------------------------------------------------------*/
DigitalChannel* BasicDigitalModule::getDigitalChannel(UINT32 ui32Channel)
{
    return dynamic_cast<DigitalChannel*>(getBasicChannel(ui32Channel));
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::setValue(UINT32 ui32Channel, BOOL8 b8Value)
{
    checkWriteState();

    setValueInternal(ui32Channel, b8Value);

    /** With this marking, changes are applied to IO in end of cycle. */
    markAsDirty();
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::setValueInternal(UINT32 ui32Channel, BOOL8 b8Value)
{
    if (ui32Channel < 1 || ui32Channel > m_CardInfo.MaxChan)
    {
        throw MIOexception("BasicDigitalModule::getValue::Invalid channel number", ui32Channel, -1);
    }

    m_pValues[ui32Channel - 1] = b8Value;
}

/**-----------------------------------------------------------------*/
void BasicDigitalModule::setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag)
{
    if (ui32Channel < 1 || ui32Channel > m_CardInfo.MaxChan)
    {
        throw MIOexception("BasicDigitalModule::getValue::Invalid channel number", ui32Channel, -1);
    }

    m_pValues[ui32Channel - 1] = (BOOL8) si32Value;

    if (setDirtyflag)
    {
        markAsDirty();
    }
}

/**-----------------------------------------------------------------*/
BOOL8 BasicDigitalModule::getValue(UINT32 ui32Channel)
{
    checkReadState();

    if (ui32Channel <= 0 || ui32Channel > m_CardInfo.MaxChan)
    {
        throw MIOexception("BasicDigitalModule::getValue::Invalid channel number", ui32Channel, -1);
    }

    return m_pValues[ui32Channel - 1];
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::setValues(SINT32 *pb32Value)
{
    checkWriteState();

    SINT32 *l_p32Value = pb32Value;
    for (UINT32 ui32Channel = 0; ui32Channel < m_CardInfo.MaxChan; ui32Channel++, l_p32Value++)
    {
        m_pValues[ui32Channel] = (BOOL8) (*l_p32Value);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::setValues(BOOL8 *pb8Value)
{
    checkWriteState();

    if (pb8Value == NULL)
    {
        throw MIOexception("BasicDigitalModule::setValues::Pointer to value array was NULL",
                m_ui32CardNumber, -1);
    }

    BOOL8 *l_pb8Value = pb8Value;
    for (UINT32 ui32Channel = 0; ui32Channel < m_CardInfo.MaxChan; ++ui32Channel, l_pb8Value++)
    {
        m_pValues[ui32Channel] = *l_pb8Value;
    }

    markAsDirty();
}

/**-----------------------------------------------------------------*/
BOOL8* BasicDigitalModule::getValues()
{
    checkReadState();

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicDigitalModule::getValues::invalid module pointer",
                m_ui32CardNumber, MIO_ER_BADCONF);
    }

    if (NULL == m_pValues)
    {
        m_pValues = new BOOL8[m_CardInfo.MaxChan];
        memset(m_pValues, 0, m_CardInfo.MaxChan);
    }

    return m_pValues;
}

/**-----------------------------------------------------------------*/
VOID BasicDigitalModule::attachInterrupt(EventSession* pSession, UINT32 ui32Channel,
        BasicEventListener* pListener)
{
    BasicIoModule::attachEvent(pSession, ui32Channel,MIO_EV_VALUE, pListener);
}

