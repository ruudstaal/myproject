/**
 ********************************************************************************
 * @file     DIO216.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DIO216.hpp"

/** Channelmodes */
const UINT32 DIO216::MODE_POSEDGE = MIO_M_POSEDGE;
const UINT32 DIO216::MODE_NEGEDGE = MIO_M_NEGEDGE;
const UINT32 DIO216::MODE_BOTHEDGES = MIO_M_BOTHEDGES;

/**-----------------------------------------------------------------*/
DIO216::DIO216() :
        BasicDigitalModule()
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO216::DIO216(UINT32 ui32CardNumber) :
        BasicDigitalModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**-----------------------------------------------------------------*/
DIO216::~DIO216()
{

}

/**-----------------------------------------------------------------*/
VOID DIO216::attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener)
{
    BasicIoModule::attachError(pSession, 0,
    MIO_E_POWER, pListener);
}

