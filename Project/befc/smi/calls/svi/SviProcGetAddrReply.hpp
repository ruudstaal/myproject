/**
 ********************************************************************************
 * @file     SviProcGetAddrReply.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 1:15:25 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_SVIPROCGETADDRREPLY_HPP_
#define BEFC_SMI_CLIENT_SVIPROCGETADDRREPLY_HPP_

#include <SmiCallReply.hpp>
#include "ParametrizedObject.hpp"

class SviProcGetAddrReply: public SmiCallReply, public ParametrizedObject
{
public:
    SviProcGetAddrReply();

    ~SviProcGetAddrReply(){};

    void readReply(SmiStream *pStream);

    void callFailed(UINT32 reason);

    SINT   getReplySize();
    SINT32 getReturnCode();
    SVI_GETADDR_R   getResult();


private:
    BOOL8           m_ReplyReady;         /**< The smi reply has been received */
    UINT32          m_retCode;
    SVI_GETADDR_R   m_data;
};
#endif /* BEFC_SMI_CLIENT_SVIPROCGETADDRREPLY_HPP_ */
