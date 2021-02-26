/**
 ********************************************************************************
 * @file     DA3284C.hpp
 * @author   TOGR
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jul 26, 2016 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of decentral CAN module DA3284C
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2016
 *******************************************************************************/

#ifndef DA3284C_HPP_
#define DA3284C_HPP_

#include "BasicMixedModule.hpp"

class DA3284C : public BasicMixedModule
{
public:
	explicit DA3284C(UINT32 CardNb);
	virtual ~DA3284C();

    /**
     * Default Constructor
     */
	DA3284C();

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DA3284C;
    }
};

#endif /** DA3284C_HPP_ */
