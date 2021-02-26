/*
 * ResProcLogoutCall.hpp
 *
 *  Created on: Apr 13, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CLIENT_RESPROCLOGOUTCALL_HPP_
#define RES_BEFC_SMI_CLIENT_RESPROCLOGOUTCALL_HPP_

#include "SmiCall.hpp"
#include <res_e.h>
#include <vector>

class ResProcLogoutCall : public SmiCall
{
public:
    ResProcLogoutCall();

    UINT32 getDataSize();

    UINT8* getData();

    void setAuthentDataFromVector(std::vector<CHAR8> data);

    void setAuthentData(UINT8 data[128]);

    virtual ~ResProcLogoutCall();

private:

    RES_LOGOUT_C call;
};

#endif /* RES_BEFC_SMI_CLIENT_RESPROCLOGOUTCALL_HPP_ */
