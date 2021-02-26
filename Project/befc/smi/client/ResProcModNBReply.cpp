/**
 ********************************************************************************
 * @file     ResProcModNBReply.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 12:58:01 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <ResProcModNBReply.hpp>
#include <res_e.h>

ResProcModNBReply::ResProcModNBReply() :
    m_ReplyReady(0), m_retCode(0), m_moduleNb(0), m_portNb(0), m_tcpPortNb(0)
{
}

void ResProcModNBReply::callFailed(UINT32 reason) {

}

void ResProcModNBReply::readReply(SmiStream *pStream)
{
    m_ReplyReady = TRUE;
    m_retCode = pStream->readSINT32();
    if(m_retCode != 0)
    {
        m_moduleNb = 0;
        m_portNb = 0;
        m_tcpPortNb = 0;
    }
    else
    {
        m_moduleNb = pStream->readUINT32();
        m_portNb = pStream->readUINT32();
        m_tcpPortNb = pStream->readUINT32();
    }
}

SINT32 ResProcModNBReply::getReturnCode()
{
    return(m_retCode);
}

int ResProcModNBReply::getReplySize()
{
    return(sizeof(RES_MODNB_R));
}

UINT32 ResProcModNBReply::getModuleNbr()
{
    return(m_moduleNb);
}
