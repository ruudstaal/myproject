/*
 * ResProcLogoutReply.hpp
 *
 *  Created on: Apr 13, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CLIENT_RESPROCLOGOUTREPLY_HPP_
#define RES_BEFC_SMI_CLIENT_RESPROCLOGOUTREPLY_HPP_

#include "SmiCallReply.hpp"

class ResProcLogoutReply : public SmiCallReply
{
public:
    ResProcLogoutReply();

   void readReply(SmiStream *pStream);

   void callFailed(UINT32 reason);

   SINT32 getReturnCode();

   int getReplySize();

   ~ResProcLogoutReply();

private:
   SMI_XLOGOUT_R reply;
};

#endif /* RES_BEFC_SMI_CLIENT_RESPROCLOGOUTREPLY_HPP_ */
