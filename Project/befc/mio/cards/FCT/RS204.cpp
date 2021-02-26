/**
 ********************************************************************************
 * @file     RS204.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of serial interface module RS204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "RS204.hpp"

/**-----------------------------------------------------------------*/
RS204::RS204() :
        BasicIoModule()
{
    /** Check card type */
    checkCardType();

}

/**-----------------------------------------------------------------*/
RS204::RS204(UINT32 ui32CardNumber) :
        BasicIoModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();

    for (UINT32 i = 0; i < 4; ++i)
    {
        m_Port[i].setCard(ui32CardNumber);
        m_Port[i].setPortNumber(i + 1);
    }

}

/**-----------------------------------------------------------------*/
RS204::~RS204()
{

}

/**-----------------------------------------------------------------*/
VOID RS204::createChannels(VOID)
{
}

/**-----------------------------------------------------------------*/
BOOL8 RS204::getPort(UINT8 ui8Portnumber, SerialPort **pPort)
{
    if (1 > ui8Portnumber || 4 < ui8Portnumber)
    {
        *pPort = NULL;
        return FALSE;
    }

    *pPort = &m_Port[ui8Portnumber - 1];

    return TRUE;
}

/**-----------------------------------------------------------------*/
VOID RS204::attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession, 0,
    MIO_E_POWER, pListener);
}
