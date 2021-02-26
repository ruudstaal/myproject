/*
 * SviProcGetValReply.hpp
 *
 *  Created on: Mar 8, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETVALREPLY_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETVALREPLY_HPP_

#include <svi/ParametrizedObject.hpp>
#include "SmiCallReply.hpp"

class SviProcGetValReply : public SmiCallReply, public ParametrizedObject
{
public:
    SviProcGetValReply();
    virtual ~SviProcGetValReply();

    void readReply(SmiStream *pStream);
    SINT32 getReturnCode();
    int getReplySize();
    void callFailed(UINT32 reason);

    SVI_GETVAL_R getReply();

private:
    SVI_GETVAL_R reply;

};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETVALREPLY_HPP_ */
