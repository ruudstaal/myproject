/**
 ********************************************************************************
 * @file     ResProcLoginReply.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 30, 2016 1:48:31 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_RESPROCLOGINREPLY_HPP_
#define BEFC_SMI_CLIENT_RESPROCLOGINREPLY_HPP_

#include <SmiCallReply.hpp>
#include <vector>
#include <smi.h>

class ResProcLoginReply: public SmiCallReply
{
public:
    ResProcLoginReply();
    virtual ~ResProcLoginReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);

    BOOL8  getReplyReady();
    int    getReplySize();
    SINT32 getReturnCode();

    UINT32 getSecurityLevel(){return m_SecurityLevel;};
    UINT8  getGroup(){return m_Group;};
    UINT8  getLevel(){return m_Level;};
    UINT8  getPriority(){return m_Priority;};
    SINT64 getSysPerm(){return m_SysPerm;};
    SINT64 getAppPerm(){return m_AppPerm;};
    UINT32 getAppData(){return m_AppData;};
    std::string getUserData(){return m_UserData;};
    std::vector<CHAR8> getAuthent(){return m_Authent;};

private:
    BOOL8                  m_ReplyReady;        /**< The smi reply has been received */
    SINT32                 m_retCode;           /**< Return Code */
    UINT32                 m_SecurityLevel;     /**< required security level  */
    UINT8                  m_Group;             /**< User group (0-255) */
    UINT8                  m_Level;             /**< User level (0-254) */
    UINT8                  m_Priority;          /**< User priority (0-255) */
    SINT64                 m_SysPerm;           /**< System-permissions of this user */
    SINT64                 m_AppPerm;           /**< Application specific permissions of this user */
    SINT32                 m_AppData;           /**< Application specific data */

    std::string            m_UserData;          /**< User data returned by checker */
    std::vector<CHAR8>     m_Authent;           /**< Authentication */

};

#endif /* BEFC_SMI_CLIENT_RESPROCLOGINREPLY_HPP_ */
