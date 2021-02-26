/*
 * SviProcSetValLstCall.hpp
 *
 *  Created on: Mar 22, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTCALL_HPP_
#define RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTCALL_HPP_

#include "ParametrizedObject.hpp"
#include <SmiCall.hpp>
#include "svi.h"

class SviProcSetValLstCall: public SmiCall, public ParametrizedObject
{
public:
    static const UINT32 SETVALLST_MAXITEMSINCALL = 64;

    SviProcSetValLstCall();

    UINT32 getDataSize();

    UINT8* getData();

    void setValues(SVI_ADDR *pAddrList, UINT32 *pValues, UINT32 length);

    virtual ~SviProcSetValLstCall();

private:

    UINT32 dataLength;

    UINT8* data;


};

#endif /* RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTCALL_HPP_ */
