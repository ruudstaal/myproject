/**
 ********************************************************************************
 * @file     ECAT201.hpp
 * @author   Torben
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Sep 13, 2017 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of EtherCAT module ECAT201
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2017
 *******************************************************************************/

#ifndef ECAT201_HPP_
#define ECAT201_HPP_

#include "BasicAnalogModule.hpp"

class ECAT201 : public BasicAnalogModule
{
public:
	explicit ECAT201(UINT32 CardNb);
	virtual ~ECAT201();

    /**
     * Default Constructor
     */
	ECAT201();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_ECAT201;
    }
};

#endif /** ECAT201_HPP_ */
