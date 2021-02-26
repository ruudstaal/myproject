/*
 * SviProcSetValReply.hpp
 *
 *  Created on: Mar 27, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCSETVALREPLY_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCSETVALREPLY_HPP_

#include <SmiCallReply.hpp>
#include "ParametrizedObject.hpp"

class SviProcSetValReply: public SmiCallReply, public ParametrizedObject
{
public:

    SviProcSetValReply();
    virtual ~SviProcSetValReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);
    SINT32 getReturnCode();
    int getReplySize();

private:
    SINT32 retCode;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCSETVALREPLY_HPP_ */
