/*
 * SviProcGetBlkReply.hpp
 *
 *  Created on: Mar 13, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETBLKREPLY_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETBLKREPLY_HPP_

#include <SmiCallReply.hpp>
#include "ParametrizedObject.hpp"

class SviProcGetBlkReply: public SmiCallReply, public ParametrizedObject
{
public:
    SviProcGetBlkReply();
    virtual ~SviProcGetBlkReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);
    SINT32 getReturnCode();
    UINT32 getDataLength();
    int getReplySize();
    UINT8* getData();

    //In case reply states that BLK should be read with MultiBLK calls.
    bool useMultiBlk(){return isMultiBlk;}
    UINT32 getBufferId(){return bufferId;}
    UINT32 getBufferlength(){return bufferlength;}

private:
    SINT32 returnCode;
    UINT32 dataLength;
    UINT8* data;

    //In case value should be set with MultiBLK
    bool isMultiBlk;
    UINT32 bufferId;
    UINT32 bufferlength;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETBLKREPLY_HPP_ */
