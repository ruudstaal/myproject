/**
 ********************************************************************************
 * @file     DI212.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input module DI212
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DI212.hpp"

/**-----------------------------------------------------------------*/
DI212::DI212() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI212::DI212(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DI212::~DI212()
{
}

