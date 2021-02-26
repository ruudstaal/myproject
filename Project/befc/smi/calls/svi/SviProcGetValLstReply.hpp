/*
 * SviProcGetValLstReply.hpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTREPLY_HPP_
#define RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTREPLY_HPP_

#include "ParametrizedObject.hpp"
#include <SmiCallReply.hpp>

class SviProcGetValLstReply: public SmiCallReply, public ParametrizedObject
{
public:
    SviProcGetValLstReply();

    void readReply(SmiStream *pStream);
    SINT32 getReturnCode();
    int getReplySize();
    void callFailed(UINT32 reason);

    void setListSize(UINT32 size);

    virtual ~SviProcGetValLstReply();

    UINT32 getListSize() const
    {
        return listSize;
    }

    UINT32* getValues() const
    {
        return pValues;
    }

private:

    UINT32 *pValues;

    UINT32 listSize;

    SINT32 returnCode;

};

#endif /* RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTREPLY_HPP_ */
