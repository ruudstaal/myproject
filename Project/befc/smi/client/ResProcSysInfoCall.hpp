/*
 * ResProcSysInfoCall.hpp
 *
 *  Created on: Jun 7, 2019
 *      Author: madsen
 */

#ifndef BEFC_SMI_CLIENT_RESPROCSYSINFOCALL_HPP_
#define BEFC_SMI_CLIENT_RESPROCSYSINFOCALL_HPP_

#include <SmiCall.hpp>
#include "Res.h"

class ResProcSysInfoCall: public SmiCall
{
public:
    ResProcSysInfoCall();

    UINT32 getDataSize();
    UINT8* getData();
    ~ResProcSysInfoCall();

private:
    RES_SYSINFO_C data;
};

#endif /* BEFC_SMI_CLIENT_RESPROCSYSINFOCALL_HPP_ */
