/**
 ********************************************************************************
 * @file     MBM201.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of modbus master module MBM201
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MBM201_HPP_
#define MBM201_HPP_

#include "BasicMixedModule.hpp"

class MBM201 : public BasicMixedModule
{
public:
	explicit MBM201(UINT32 CardNb);
	virtual ~MBM201();

    /**
     * Default Constructor
     */
	MBM201();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_MBM201;
    }
};

#endif /** MBM201_HPP_ */
