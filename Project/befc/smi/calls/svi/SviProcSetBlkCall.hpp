/*
 * SviProcSetBlkCall.hpp
 *
 *  Created on: Mar 29, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCSETBLKCALL_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCSETBLKCALL_HPP_

#include <SmiCall.hpp>

class SviProcSetBlkCall: public SmiCall
{
public:
    SviProcSetBlkCall();

    UINT32 getDataSize();
    UINT8* getData();

    void setSVIAddr(SVI_ADDR address);
    void setData(UINT8* data, UINT32 length);



    virtual ~SviProcSetBlkCall();

private:

    struct BlkStructure {
      SVI_ADDR addr;
      UINT32 buffLength;
      UINT8* data;
    };

    BlkStructure data;

    UINT8* pPayload;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCSETBLKCALL_HPP_ */
