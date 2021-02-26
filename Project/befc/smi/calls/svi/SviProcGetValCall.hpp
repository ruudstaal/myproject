/*
 * SviProcGetValCall.hpp
 *
 *  Created on: Mar 8, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETVALCALL_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETVALCALL_HPP_

#include <svi/ParametrizedObject.hpp>
#include "svi.h"
#include "SmiCall.hpp"

class SviProcGetValCall: public SmiCall, public ParametrizedObject
{
public:
    SviProcGetValCall();
    virtual ~SviProcGetValCall();

    UINT32 getDataSize();
    UINT8* getData();

    SVI_ADDR getAddr();
    void setAddr(SVI_ADDR address);

private:
    SVI_ADDR addr;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETVALCALL_HPP_ */
