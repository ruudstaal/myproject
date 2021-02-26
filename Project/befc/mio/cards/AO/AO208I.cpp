/**
 ********************************************************************************
 * @file     AO208I.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog output module AO208I
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AO208I.hpp"

const UINT32 AO208I::MODE_AO_20mA = MIO_M_20MA;
const UINT32 AO208I::MODE_AO_4_20mA = MIO_M_04_20MA;

/**----------------------------------------------------------------- */
AO208I::AO208I() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AO208I::AO208I(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AO208I::~AO208I()
{
}

