/**
 ********************************************************************************
 * @file     DO232.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital output module DO232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DO232.hpp"

/**-----------------------------------------------------------------*/
DO232::DO232() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DO232::DO232(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DO232::~DO232()
{
}

