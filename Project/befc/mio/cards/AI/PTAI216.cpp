/**
 ********************************************************************************
 * @file     PTAI216.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module PTAI216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "PTAI216.hpp"

const UINT32 PTAI216::MODE_10V = MIO_M_10V;
const UINT32 PTAI216::MODE_1V = MIO_M_1V;
const UINT32 PTAI216::MODE_20mA = MIO_M_20MA;
const UINT32 PTAI216::MODE_PT100 = MIO_M_PT100;
const UINT32 PTAI216::MODE_PT1000 = MIO_M_PT1000;

/**----------------------------------------------------------------- */
PTAI216::PTAI216() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
PTAI216::PTAI216(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
PTAI216::~PTAI216()
{
}

