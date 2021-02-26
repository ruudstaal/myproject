/**
 ********************************************************************************
 * @file     DIO280.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO280
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DIO280.hpp"

/**-----------------------------------------------------------------*/
DIO280::DIO280() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO280::DIO280(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO280::~DIO280()
{

}

