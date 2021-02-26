/**
 ********************************************************************************
 * @file     PN201.hpp
 * @author   Torben
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Sep 13, 2017 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProfiNet module PN201
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2017
 *******************************************************************************/

#ifndef PN201_HPP_
#define PN201_HPP_

#include "BasicAnalogModule.hpp"

class PN201 : public BasicAnalogModule
{
public:
	explicit PN201(UINT32 CardNb);
	virtual ~PN201();

    /**
     * Default Constructor
     */
	PN201();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_PN201;
    }
};

#endif /** PN201_HPP_ */
