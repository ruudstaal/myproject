/*
 * SviProcGetXAddrReply.cpp
 *
 *  Created on: May 21, 2019
 *      Author: madsen
 */

#include <svi/SviProcGetXAddrReply.hpp>

SviProcGetXAddrReply::SviProcGetXAddrReply() : ParametrizedObject(),
    m_ReplyReady(FALSE),
    m_retCode(0)
{
    m_data = (SVI_GETXADDR_R) { 0 };
}

void SviProcGetXAddrReply::readReply(SmiStream *pStream)
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
        m_data.Addr.Int.Addr1 = pStream->readUINT32();              /**< SVI address part 1 */
        m_data.Addr.Int.Addr2 = pStream->readUINT32();              /**< SVI address part 2 */
        m_data.Format = pStream->readUINT16();                      /**< SVI format */
        m_data.ValLen = pStream->readUINT16();                      /**< SVI ValLen in bytes */
        pStream->read((char*)&m_data.Spare, sizeof(m_data.Spare));  /**< SVI Spares */
    }
}

SINT32 SviProcGetXAddrReply::getReturnCode()
{
    return(m_retCode);
}

SINT SviProcGetXAddrReply::getReplySize()
{
    return(sizeof(SVI_GETADDR_R));
}

SVI_GETXADDR_R SviProcGetXAddrReply::getResult()
{
    return(m_data);
}

void SviProcGetXAddrReply::callFailed(UINT32 reason){
    m_retCode = reason;
}
