/**
 ********************************************************************************
 * @file     CAN.hpp
 * @author   Torben
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Sep 13, 2017 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of CAN logical module CAN
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2017
 *******************************************************************************/

#ifndef CAN_HPP_
#define CAN_HPP_

#include "BasicAnalogModule.hpp"

class CAN : public BasicAnalogModule
{
public:
	explicit CAN(UINT32 CardNb);
	virtual ~CAN();

    /**
     * Default Constructor
     */
	CAN();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_CAN;
    }
};

#endif /** CAN_HPP_ */
