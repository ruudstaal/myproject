/*
 * SviProcGetXAddrReply.hpp
 *
 *  Created on: May 21, 2019
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRREPLY_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRREPLY_HPP_

#include <SmiCallReply.hpp>
#include "ParametrizedObject.hpp"

class SviProcGetXAddrReply: public SmiCallReply, public ParametrizedObject
{
public:
    SviProcGetXAddrReply();

    ~SviProcGetXAddrReply(){};

    void readReply(SmiStream *pStream);

    void callFailed(UINT32 reason);

    SINT   getReplySize();
    
    SINT32 getReturnCode();
    
    SVI_GETXADDR_R getResult();


private:
    BOOL8           m_ReplyReady;         /**< The smi reply has been received */
    
    UINT32          m_retCode;
    
    SVI_GETXADDR_R   m_data;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRREPLY_HPP_ */
