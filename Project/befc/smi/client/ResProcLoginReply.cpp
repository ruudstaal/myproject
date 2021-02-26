/**
 ********************************************************************************
 * @file     ResProcLoginReply.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 30, 2016 1:48:31 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <ResProcLoginReply.hpp>
#include <msys_e.h>

ResProcLoginReply::ResProcLoginReply() :
        m_ReplyReady(0), m_retCode(0), m_SecurityLevel(0), m_Group(0), m_Level(0), m_Priority(0), m_SysPerm(
                0), m_AppPerm(0), m_AppData(0)
{
}

ResProcLoginReply::~ResProcLoginReply()
{
}

void ResProcLoginReply::callFailed(UINT32 reason) {
}

void ResProcLoginReply::readReply(SmiStream *pStream)
{
    UINT32 l_AuthLen, l_Temp;
    m_ReplyReady = TRUE;
    m_retCode = pStream->readSINT32();
    if(m_retCode != 0)
    {
        m_SecurityLevel = 0;     /**< required security level  */
        m_Group = 0;             /**< User group (0-255) */
        m_Level = 0;             /**< User level (0-254) */
        m_Priority = 0;          /**< User priority (0-255) */
        m_SysPerm = 0;           /**< System-permissions of this user */
        m_AppPerm = 0;           /**< Application specific permissions of this user */
        m_AppData = 0;           /**< Application specific data */
        m_UserData.clear();      /**< User data returned by checker */
        m_Authent.clear();       /**< Authentication */

    }
    else
    {
        m_SecurityLevel = pStream->readUINT32();     /**< required security level  */
        pStream->skipBytes(4);

        l_Temp = pStream->readUINT32();
        m_Group = l_Temp & 0xff;             /**< User group (0-255) */
        m_Level = (l_Temp >> 8) & 0xff;      /**< User level (0-254) */
        m_Priority = (l_Temp >> 16) & 0xff;  /**< User priority (0-255) */
        m_SysPerm = pStream->readUINT64();           /**< System-permissions of this user */
        m_AppPerm = pStream->readUINT64();           /**< Application specific permissions of this user */
        m_AppData = pStream->readSINT32();           /**< Application specific data */
        pStream->skipBytes(12);

        l_AuthLen = pStream->readUINT32();
        m_Authent = pStream->readVector(l_AuthLen);     /**< Authentication */
        m_UserData = pStream->readString(128);          /**< User data returned by checker */
    }
}

SINT32 ResProcLoginReply::getReturnCode()
{
    UINT32 ret = m_retCode;
    return(ret);
}

int ResProcLoginReply::getReplySize()
{
    return(sizeof(SMI_XLOGIN_R));
}

BOOL8 ResProcLoginReply::getReplyReady()
{
    BOOL8 l_ReplyReady = m_ReplyReady;
    m_ReplyReady = FALSE; // Reset arrived information for next transmission

    return(l_ReplyReady);
};


