/**
 ********************************************************************************
 * @file     ResProcModNBReply.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 12:58:01 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_RESPROCMODNBREPLY_HPP_
#define BEFC_SMI_CLIENT_RESPROCMODNBREPLY_HPP_

#include <SmiCallReply.hpp>

class ResProcModNBReply: public SmiCallReply
{
public:
    ResProcModNBReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);

    UINT32 getModuleNbr();
    int    getReplySize();
    SINT32 getReturnCode();

private:
    BOOL8   m_ReplyReady;         /**< The smi reply has been received */
    SINT32  m_retCode;            /**< Return Code */
    UINT32  m_moduleNb;           /**< Module number */
    UINT16  m_portNb;             /**< Port number for UDP */
    UINT16  m_tcpPortNb;          /**< Port number for TCP */
};

#endif /* BEFC_SMI_CLIENT_RESPROCMODNBREPLY_HPP_ */
