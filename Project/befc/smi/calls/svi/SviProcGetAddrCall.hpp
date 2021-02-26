/**
 ********************************************************************************
 * @file     SviProcGetAddrCall.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 5, 2016 1:05:11 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_SVIPROCGETADDRCALL_HPP_
#define BEFC_SMI_CLIENT_SVIPROCGETADDRCALL_HPP_

#include <SmiCall.hpp>
#define MAXVARLENGTH 100

class SviProcGetAddrCall: public SmiCall
{
public:
    SviProcGetAddrCall();

    void SetSVIVarName(std::string SVIVarName);

    UINT32 getDataSize();

    UINT8* getData();

    ~SviProcGetAddrCall();

private:
    CHAR*     m_SVIVarName;
    UINT32    m_VarNameLength;
};
#endif /* BEFC_SMI_CLIENT_SVIPROCGETADDRCALL_HPP_ */
