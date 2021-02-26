/**
 ********************************************************************************
 * @file     DOR206.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital output module DOR206
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DOR206.hpp"

/**-----------------------------------------------------------------*/
DOR206::DOR206() :
        BasicDigitalModule()
{
}

/**-----------------------------------------------------------------*/
DOR206::DOR206(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DOR206::~DOR206()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
VOID DOR206::ResetSwitchCount(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_RESETSWITCHCOUNT, l_ui32Channel);
}

/**-----------------------------------------------------------------*/
UINT32 DOR206::getSwitchCount(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32pCount = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETSWITCHCOUNT, l_ui32Channel, (SINT32) &l_ui32pCount);

    return l_ui32pCount;
}
