/**
 ********************************************************************************
 * @file     DIO232.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DIO232.hpp"

/** Channelmodes */
const UINT32 DIO232::MODE_POSEDGE = MIO_M_POSEDGE;
const UINT32 DIO232::MODE_NEGEDGE = MIO_M_NEGEDGE;
const UINT32 DIO232::MODE_BOTHEDGES = MIO_M_BOTHEDGES;

/**-----------------------------------------------------------------*/
DIO232::DIO232() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO232::DIO232(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO232::~DIO232()
{
}

/**-----------------------------------------------------------------*/
VOID DIO232::setFilterTime(UINT8 ui8Channel, UINT32 ui32Time)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) ui32Time);

}

/**-----------------------------------------------------------------*/
UINT32 DIO232::getFilterTime(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 ui32Time;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER, l_ui32Channel, (SINT32) &ui32Time);
    return ui32Time;
}
