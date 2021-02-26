/**
 ********************************************************************************
 * @file     BasicMixedModule.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicMixedModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "BasicMixedModule.hpp"
#include "mcpp.hpp"
#include <iostream>
#include "AnalogChannel.hpp"
#include "DigitalChannel.hpp"
#include "MIOexception.hpp"
#include <cstring>

/**-----------------------------------------------------------------*/
BasicMixedModule::BasicMixedModule() :
        BasicIoModule()
{
    initInternal();
}

/**-----------------------------------------------------------------*/
BasicMixedModule::BasicMixedModule(UINT32 ui32CardNumber, BOOL8 b8CreateChannels) :
        BasicIoModule(ui32CardNumber)
{
    initInternal();
}

BasicMixedModule::BasicMixedModule(UINT32 ui32CardNumber, MIOSystem *pMioSystem, BOOL8 b8CreateChannels) : BasicIoModule(ui32CardNumber, pMioSystem) {
    initInternal();
}


VOID BasicMixedModule::initInternal(VOID)
{
    if (m_CardInfo.MaxChan == 0)
    {
        m_psi32GetValuesBuffer = NULL;
        m_pValuesDirtyBuffer = NULL;
    }
    else
    {
        m_psi32GetValuesBuffer = new SINT32[m_CardInfo.MaxChan];
        memset(m_psi32GetValuesBuffer, 0, m_CardInfo.MaxChan * 4); /** 4 bytes for each SINT32 */
        m_pValuesDirtyBuffer = new BOOL8[m_CardInfo.MaxChan];
        memset(m_pValuesDirtyBuffer, 0, m_CardInfo.MaxChan);
    }
    createChannels();
}

/**-----------------------------------------------------------------*/
BasicMixedModule::~BasicMixedModule()
{
    SAFE_DELETE(m_psi32GetValuesBuffer);
    SAFE_DELETE(m_pValuesDirtyBuffer);
}

/**-----------------------------------------------------------------*/
VOID BasicMixedModule::createChannels(VOID)
{
    UINT32 i;

    BasicChannel *l_pChannel = NULL;
    SINT32 res = 0;
    if (0 == m_CardInfo.MaxChan)
    {
        return;
    }

    MIO_CHANINF ChanInf;
    for (i = 0; i < m_CardInfo.MaxChan; ++i)
    {

        res = m_pMioSystem->getChanInf(m_pDriverId, i + 1, &ChanInf);
        if (res == 0)
        {

            if ((ChanInf.Category & MIO_CATEG_DI) || (ChanInf.Category & MIO_CATEG_DO))
            {
                l_pChannel = new DigitalChannel();
            }
            else
            {
                l_pChannel = new AnalogChannel();
            }

            //if(ChanInf.Flags & MIO_FLG_READ){} /** Could check for channel is read/write? */
            l_pChannel->setChannelNumber(i + 1);
            l_pChannel->setParentModule(this);
            m_ChannelList[i + 1] = l_pChannel;
        }
        else
        {
            throw MIOexception("BasicMixedModule::createChannels - Could not get channel info",
                    m_ui32CardNumber, (i + 1), res);
        }
    }
}

/**-----------------------------------------------------------------*/
VOID BasicMixedModule::setValue(UINT32 ui32Channel, SINT32 si32Value)
{
    checkWriteState();

    if (ui32Channel >= 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        if(m_psi32GetValuesBuffer[ui32Channel - 1] == si32Value)
        {
            return;
        }
        m_psi32GetValuesBuffer[ui32Channel - 1] = si32Value;
        m_pValuesDirtyBuffer[ui32Channel - 1] = TRUE;
    }
    else
    {
        throw MIOexception("BasicMixedModule::setValue: Invalid channel", m_ui32CardNumber,
                ui32Channel, MIO_ER_BADHANDLE);
    }
    markAsDirty();
}

/**-----------------------------------------------------------------*/
SINT32 BasicMixedModule::getValue(UINT32 ui32Channel)
{
    checkReadState();

    if (ui32Channel > 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        return m_psi32GetValuesBuffer[ui32Channel - 1];
    }
    throw MIOexception("BasicMixedModule::getValue::Wanted channel outside card range", this->m_CardInfo.CardNb, -1,
            ui32Channel);
}

BOOL8 BasicMixedModule::getBoolValue(UINT32 ui32Channel)
{
    checkReadState();

    BasicChannel *pChannel = getBasicChannel(ui32Channel);
    if (pChannel->isDigitalChannel())
    {
        return (BOOL8) m_psi32GetValuesBuffer[ui32Channel - 1];
    }
    throw MIOexception("BasicMixedModule::getBoolValue::Channel not digital",
            this->m_CardInfo.CardNb, ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID BasicMixedModule::setValuesInternal(SINT32 *psi32Value, UINT32 ui32BufferSize)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicMixedModule::setValues::invalid module pointer", m_ui32CardNumber,
                MIO_ER_BADCONF);
    }

    UINT32 int_buffersize = ui32BufferSize;
    if (int_buffersize > m_CardInfo.MaxChan)
    {
        int_buffersize = m_CardInfo.MaxChan;
    }

    memcpy(m_psi32GetValuesBuffer, psi32Value, int_buffersize * 4);
}

/**-----------------------------------------------------------------*/
void BasicMixedModule::setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicMixedModule::setValues::invalid module pointer", m_ui32CardNumber,
        MIO_ER_BADCONF);
    }

    if (ui32Channel > 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        m_psi32GetValuesBuffer[ui32Channel - 1] = si32Value;
    }
    else
    {
        throw MIOexception("Requested channel outside card range", this->m_CardInfo.CardNb, -1,
                ui32Channel);
    }

    if (setDirtyflag)
    {
        markAsDirty();
    }
}

/**-----------------------------------------------------------------*/
VOID BasicMixedModule::setValue(UINT32 ui32Channel, BOOL8 boolValue)
{
    checkWriteState();

    BasicChannel *pChannel = getBasicChannel(ui32Channel);
    if (pChannel->isDigitalChannel())
    {
        (dynamic_cast<DigitalChannel*>(pChannel))->setValue(boolValue);
        markAsDirty();
    }
    else
    {
        throw MIOexception("BasicMixedModule::setValue::Channel is not digital", getCardNumber(),
                ui32Channel);
    }
}

/**-----------------------------------------------------------------*/
VOID BasicMixedModule::setValues(SINT32 *psi32Value, UINT32 ui32BufferSize)
{
    //Will throw exception if not allowed to write
    checkWriteState();

    if (psi32Value == NULL)
    {
        throw MIOexception("BasicMixedModule::setValues::Pointer to value array was NULL",
                m_ui32CardNumber, -1);
    }

    /** Set the values internally */
    setValuesInternal(psi32Value, ui32BufferSize);

    /** mark the card for writing at end of cycle. */
    markAsDirty();
}

/**-----------------------------------------------------------------*/
SINT32* BasicMixedModule::getValues(VOID)
{
    checkReadState();

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicMixedModule::getValues::invalid module pointer", m_ui32CardNumber,
                MIO_ER_BADCONF);
    }

    if (NULL == m_psi32GetValuesBuffer)
    {
        m_psi32GetValuesBuffer = new SINT32[m_CardInfo.MaxChan];
        memset(m_psi32GetValuesBuffer, 0, m_CardInfo.MaxChan * 4); /** 4 bytes for each SINT32 */
    }

    return m_psi32GetValuesBuffer;
}
