/*
 * ResProcSysInfoReply.hpp
 *
 *  Created on: Jun 7, 2019
 *      Author: madsen
 */

#ifndef BEFC_SMI_CLIENT_RESPROCSYSINFOREPLY_HPP_
#define BEFC_SMI_CLIENT_RESPROCSYSINFOREPLY_HPP_

#include <SmiCallReply.hpp>
#include "Res.h"

class ResProcSysInfoReply: public SmiCallReply
{
public:
    ResProcSysInfoReply();

    void readReply(SmiStream *pStream);
    void callFailed(UINT32 reason);

    int    getReplySize();
    SINT32 getReturnCode();

    virtual ~ResProcSysInfoReply();

    RES_SYSINFO_R getReply(){return reply;}

private:

    RES_SYSINFO_R reply;
};

#endif /* BEFC_SMI_CLIENT_RESPROCSYSINFOREPLY_HPP_ */
