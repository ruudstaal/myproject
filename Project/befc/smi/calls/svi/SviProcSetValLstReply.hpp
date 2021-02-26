/*
 * SviProcSetValLstReply.hpp
 *
 *  Created on: Mar 23, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTREPLY_HPP_
#define RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTREPLY_HPP_

#include <SmiCallReply.hpp>

class SviProcSetValLstReply: public SmiCallReply
{
public:
    SviProcSetValLstReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);
    SINT32 getReturnCode();
    int getReplySize();

    virtual ~SviProcSetValLstReply();

private:
    SINT32 returnCode;
};

#endif /* RES_BEFC_SMI_CALLS_SVI_SVIPROCSETVALLSTREPLY_HPP_ */
