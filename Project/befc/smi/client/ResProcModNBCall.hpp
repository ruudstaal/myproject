/**
 ********************************************************************************
 * @file     ResProcModNBCall.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 1, 2016 1:53:53 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_RESPROCMODNBCALL_HPP_
#define BEFC_SMI_CLIENT_RESPROCMODNBCALL_HPP_

#include <SmiCall.hpp>
#include <string>
#include <res_e.h>
class ResProcModNBCall: public SmiCall
{
public:
    ResProcModNBCall();

    UINT32 getDataSize();
    UINT8* getData();

    void setModuleName(std::string moduleName);

    std::string getModuleName(){return m_data.AppName;}

    virtual ~ResProcModNBCall();
private:
    RES_MODNB_C m_data;
};

#endif /* BEFC_SMI_CLIENT_RESPROCMODNBCALL_HPP_ */
