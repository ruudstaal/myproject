/*
 * SviProcGetBlkCall.hpp
 *
 *  Created on: Mar 13, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETBLKCALL_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETBLKCALL_HPP_

#include <SmiCall.hpp>

class SviProcGetBlkCall: public SmiCall
{
public:
    SviProcGetBlkCall();

    UINT32 getDataSize();
    UINT8* getData();

    void setAddr(SVI_ADDR address);
    SVI_ADDR getAddr();

    UINT32 getLength();

    void setLength(UINT32 length);

    virtual ~SviProcGetBlkCall();

private:
    SVI_GETBLK_C data;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETBLKCALL_HPP_ */
