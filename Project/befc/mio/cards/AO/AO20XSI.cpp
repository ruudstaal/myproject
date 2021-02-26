/**
 ********************************************************************************
 * @file     AO20XSI.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog output module AO20XSI
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AO20XSI.hpp"

/**-----------------------------------------------------------------*/
AO20XSI::AO20XSI() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
AO20XSI::AO20XSI(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
AO20XSI::~AO20XSI()
{
}

