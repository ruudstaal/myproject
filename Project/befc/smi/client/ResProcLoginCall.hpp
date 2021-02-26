/**
 ********************************************************************************
 * @file     ResProcLoginCall.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 30, 2016 1:41:55 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_RESPROCLOGINCALL_HPP_
#define BEFC_SMI_CLIENT_RESPROCLOGINCALL_HPP_

#include <SmiCall.hpp>
#include <res_e.h>

class ResProcLoginCall: public SmiCall
{
public:
    ResProcLoginCall(std::string Username, std::string Password, UINT32 UserParm, UINT32 LoginSessId, std::string toolName);
    virtual ~ResProcLoginCall(){};

    UINT8* getData();
    UINT32 getDataSize();

private:
    RES_LOGIN2_C m_data;
};

#endif /* BEFC_SMI_CLIENT_RESPROCLOGINCALL_HPP_ */
