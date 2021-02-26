/**
 ********************************************************************************
 * @file     DI232.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input module DI232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DI232.hpp"

/**-----------------------------------------------------------------*/
DI232::DI232() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI232::DI232(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI232::~DI232()
{

}

/**-----------------------------------------------------------------*/
VOID DI232::setFilter(UINT8 ui8Channel, UINT32 ui32Time)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) ui32Time);

}

/**-----------------------------------------------------------------*/
UINT32 DI232::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32pTime = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER, l_ui32Channel, (SINT32) &l_ui32pTime);
    return l_ui32pTime;
}
