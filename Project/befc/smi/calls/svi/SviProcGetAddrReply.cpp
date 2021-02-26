/**
 ********************************************************************************
 * @file     SviProcGetAddrReply.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 1:15:25 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include "SviProcGetAddrReply.hpp"
#include "log_e.h"

SviProcGetAddrReply::SviProcGetAddrReply() : ParametrizedObject(),
    m_ReplyReady(FALSE),
    m_retCode(0)
{
    m_data = (SVI_GETADDR_R) { 0 };
}

void SviProcGetAddrReply::readReply(SmiStream *pStream)
{
    m_ReplyReady = TRUE;
    m_retCode = pStream->readSINT32();
    m_data.RetCode = m_retCode;
    if(m_retCode != 0)
    {
        return;
    }
    else
    {
        m_data.Addr.Int.Addr1 = pStream->readUINT32();    /**< SVI address part 1 */
        m_data.Addr.Int.Addr2 = pStream->readUINT32();    /**< SVI address part 2 */
        m_data.Format = pStream->readUINT32();            /**< SVI format */
    }
}

SINT32 SviProcGetAddrReply::getReturnCode()
{
    return(m_retCode);
}

SINT SviProcGetAddrReply::getReplySize()
{
    return(sizeof(SVI_GETADDR_R));
}

SVI_GETADDR_R SviProcGetAddrReply::getResult()
{
    return(m_data);
}

void SviProcGetAddrReply::callFailed(UINT32 reason){
    m_retCode = reason;
}
