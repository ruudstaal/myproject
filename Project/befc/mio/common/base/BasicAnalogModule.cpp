/**
 ********************************************************************************
 * @file     BasicAnalogModule.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicAnalogModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "BasicAnalogModule.hpp"
#include "mcpp.hpp"
#include <cstring>

/**-----------------------------------------------------------------*/
BasicAnalogModule::BasicAnalogModule() :
        BasicIoModule()
{
    initInternal();
}

/**-----------------------------------------------------------------*/
BasicAnalogModule::BasicAnalogModule(UINT32 ui32CardNumber, BOOL8 b8CreateChannels) :
        BasicIoModule(ui32CardNumber)
{
    initInternal();
}

VOID BasicAnalogModule::initInternal(VOID)
{
    if (m_CardInfo.MaxChan == 0)
    {
        m_psi32GetValuesBuffer = NULL;
    }
    else
    {
        m_psi32GetValuesBuffer = new SINT32[m_CardInfo.MaxChan];
        memset(m_psi32GetValuesBuffer, 0, m_CardInfo.MaxChan * 4); /** 4 bytes for each SINT32 */
    }
    createChannels();
}

/**-----------------------------------------------------------------*/
BasicAnalogModule::~BasicAnalogModule()
{
    SAFE_DELETE(m_psi32GetValuesBuffer);
}

/**-----------------------------------------------------------------*/
VOID BasicAnalogModule::createChannels(VOID)
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
        l_pChannel = new AnalogChannel();
        l_pChannel->setChannelNumber(i + 1);
        l_pChannel->setParentModule(this);

        m_ChannelList[i + 1] = l_pChannel;
    }
}

/**-----------------------------------------------------------------*/
AnalogChannel* BasicAnalogModule::getAnalogChannel(UINT32 ui32Channel)
{
    return dynamic_cast<AnalogChannel*>(getBasicChannel(ui32Channel));
}

/**-----------------------------------------------------------------*/
VOID BasicAnalogModule::setValue(UINT32 ui32Channel, SINT32 si32Value)
{
    checkWriteState();

    if (ui32Channel >= 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        m_psi32GetValuesBuffer[ui32Channel - 1] = si32Value;
    }
    else
    {
        throw MIOexception("BasicAnalogModule::setValue::Invalid channel", m_ui32CardNumber,
                ui32Channel, MIO_ER_BADHANDLE);
    }
    markAsDirty();
}

/**-----------------------------------------------------------------*/
SINT32 BasicAnalogModule::getValue(UINT32 ui32Channel)
{
    checkReadState();

    if (ui32Channel > 0 && ui32Channel <= m_CardInfo.MaxChan)
    {
        return m_psi32GetValuesBuffer[ui32Channel - 1];
    }
    throw MIOexception("BasicAnalogModule::getValue::Requested channel outside card range", this->m_CardInfo.CardNb, -1,
            ui32Channel);
}

VOID BasicAnalogModule::setValuesInternal(SINT32 *psi32Value, UINT32 ui32BufferSize)
{
    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicAnalogModule::setValues::invalid module pointer", m_ui32CardNumber,
        MIO_ER_BADCONF);
    }

    UINT32 int_buffersize = ui32BufferSize;
    if (int_buffersize > m_CardInfo.MaxChan)
    {
        int_buffersize = m_CardInfo.MaxChan;
    }

    memcpy(m_psi32GetValuesBuffer, psi32Value, int_buffersize * 4);
}

void BasicAnalogModule::setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag)
{
    m_psi32GetValuesBuffer[ui32Channel - 1] = si32Value;
    if (setDirtyflag)
    {
        markAsDirty();
    }
}

/**-----------------------------------------------------------------*/
VOID BasicAnalogModule::setValues(SINT32 *psi32Value, UINT32 ui32BufferSize)
{
    checkWriteState();

    if (psi32Value == NULL)
    {
        throw MIOexception("BasicAnalogModule::setValues: Pointer to value array was NULL",
                m_ui32CardNumber, -1);
    }

    /** Set the values internally */
    setValuesInternal(psi32Value, ui32BufferSize);

    /** mark the card for writing at end of cycle. */
    markAsDirty();
}

/**-----------------------------------------------------------------*/
SINT32* BasicAnalogModule::getValues(VOID)
{
    checkReadState();

    if (NULL == m_pDriverId)
    {
        throw MIOexception("BasicAnalogModule::getValues::invalid module pointer", m_ui32CardNumber,
        MIO_ER_BADCONF);
    }

    if (NULL == m_psi32GetValuesBuffer)
    {
        m_psi32GetValuesBuffer = new SINT32[m_CardInfo.MaxChan];
        memset(m_psi32GetValuesBuffer, 0, m_CardInfo.MaxChan * 4); /** 4 bytes for each SINT32 */
    }

    return m_psi32GetValuesBuffer;
}
