/*
 * SviProcSetBlkReply.hpp
 *
 *  Created on: Mar 29, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCSETBLKREPLY_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCSETBLKREPLY_HPP_

#include <SmiCallReply.hpp>
#include "ParametrizedObject.hpp"

class SviProcSetBlkReply: public SmiCallReply, public ParametrizedObject
{
public:
    SviProcSetBlkReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);
    SINT32 getReturnCode();
    int getReplySize();

    bool useMultiBlk(){return isMultiBlk;}
    UINT32 getBufferId(){return bufferId;}

    virtual ~SviProcSetBlkReply();
private:
    SINT32 retCode;

    //In case value should be set with MultiBLK
    bool isMultiBlk;
    UINT32 bufferId;

};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCSETBLKREPLY_HPP_ */
