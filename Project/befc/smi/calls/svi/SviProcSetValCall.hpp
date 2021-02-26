/*
 * SviProcSetValCall.hpp
 *
 *  Created on: Mar 21, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCSETVALCALL_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCSETVALCALL_HPP_

#include <SmiCall.hpp>

class SviProcSetValCall: public SmiCall
{
public:
    SviProcSetValCall();
    UINT32 getDataSize();
    UINT8* getData();

    void setSVIAddr(SVI_ADDR address);
    void setValue(UINT32 value);

    UINT32 getValue();

    virtual ~SviProcSetValCall();
private:
    SVI_SETVAL_C call;

};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCSETVALCALL_HPP_ */
