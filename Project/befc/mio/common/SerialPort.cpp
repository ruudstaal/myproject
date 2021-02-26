/**
 ********************************************************************************
 * @file     SerialPort.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SerialPort
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SerialPort.hpp"
#include <string.h>
#include <stdio.h>
#include <ioLib.h>
#include <log_e.h>

const int SerialPort::INVALID = -1;

/**-----------------------------------------------------------------*/
SerialPort::SerialPort() :
        m_ui32Port(0), m_ui32Card(0), m_iHandle(SerialPort::INVALID), m_pListener(NULL)
{
    memset(&m_ch8Port[0], 0, sizeof(m_ch8Port));
}

/**-----------------------------------------------------------------*/
SerialPort::~SerialPort()
{
}

/**-----------------------------------------------------------------*/
VOID SerialPort::setCard(UINT32 ui32CardNumber)
{
    m_ui32Card = ui32CardNumber;
}

/**-----------------------------------------------------------------*/
VOID SerialPort::setPortNumber(UINT32 ui32PortNumber)
{
    m_ui32Port = ui32PortNumber;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::openPort(VOID)
{
    size_t l_si32Size = sizeof(m_ch8Port) - 1;
    SINT32 l_si32Retcode;

    l_si32Retcode = snprintf(&m_ch8Port[0], l_si32Size, "/tyCo/%d/%d", m_ui32Card, m_ui32Port);

    if (0 > l_si32Retcode)
    {
        log_Err("Open Port %s Failed", m_ch8Port);
        return FALSE;
    }

    m_iHandle = open(m_ch8Port, O_RDWR, 0);

    if (0 < m_iHandle)
    {
        if (FALSE == flush())
        {
            log_Info("Failed to delete buffer in COM");
        }

        if (OK == ioctl(m_iHandle, FIOSETOPTIONS, OPT_RAW))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::closePort(VOID)
{
    if (ERROR == close(m_iHandle))
    {
        return FALSE;
    }

    m_iHandle = SerialPort::INVALID;

    return TRUE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::flush(VOID)
{
    if (OK == ioctl(m_iHandle, FIOFLUSH, 0))
    {
        return TRUE;
    }

    return FALSE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::setValue(CHAR8* pch8Data, UINT32 ui32Size)
{
    int l_Retcode = 0;

    if (0 == ui32Size)
    {
        ui32Size = strlen(pch8Data);
    }

    l_Retcode = (int) ui32Size;

    if (l_Retcode == write(m_iHandle, pch8Data, ui32Size))
    {
        return TRUE;
    }

    return FALSE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::getValue(CHAR8* pch8Data, UINT32 *pui32Size)
{
    UINT32 l_ui32Bytes;

    if (TRUE == getReceivedBytes(&l_ui32Bytes))
    {

        if (l_ui32Bytes < *pui32Size)
        {
            *pui32Size = l_ui32Bytes;
        }

        if (0 == read(m_iHandle, pch8Data, *pui32Size))
        {
            return TRUE;
        }

    }

    return FALSE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::getReceivedBytes(UINT32 *pui32Bytes)
{
    UINT32 l_ui32Bytes = 0;

    if (ERROR != ioctl(m_iHandle, FIONREAD, (SINT32) &l_ui32Bytes))
    {
        *pui32Bytes = l_ui32Bytes;
        return TRUE;
    }

    *pui32Bytes = 0;

    return FALSE;
}

/**-----------------------------------------------------------------*/
BOOL8 SerialPort::attachListener(BasicEventListener* pListener)
{

    if (SerialPort::INVALID == m_iHandle)
    {
        return FALSE;
    }

    if (ERROR != ioctl(m_iHandle, FIOPROTOHOOK, (int) &SerialPort::callback))
    {
        if (ERROR != ioctl(m_iHandle, FIOPROTOARG, (int) this))
        {
            m_pListener = pListener;
            return TRUE;
        }
    }

    m_pListener = NULL;

    return FALSE;
}

/**-----------------------------------------------------------------*/
STATUS SerialPort::receivedData(UINT32 ui32Sign)
{
    if (NULL != m_pListener)
    {
        if (0 == m_pListener->EventOccured(m_ui32Card, m_ui32Port, ui32Sign))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/**-----------------------------------------------------------------*/
STATUS SerialPort::callback(UINT32 ui32Userpara, UINT32 ui32Sign)
{

    SerialPort *l_pSerialPort = reinterpret_cast<SerialPort*>(ui32Userpara);

    if (NULL != l_pSerialPort)
    {
        return l_pSerialPort->receivedData(ui32Sign);
    }

    return FALSE;
}
