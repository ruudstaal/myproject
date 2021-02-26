/**
 ********************************************************************************
 * @file     DI216.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input module DI216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DI216.hpp"

/**-----------------------------------------------------------------*/
DI216::DI216()
    : BasicDigitalModule()
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI216::DI216(UINT32 ui32CardNumber)
    : BasicDigitalModule(ui32CardNumber)
{
	/** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI216::~DI216()
{
}


