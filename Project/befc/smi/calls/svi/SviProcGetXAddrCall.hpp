/*
 * SviProcGetXAddrCall.hpp
 *
 *  Created on: May 21, 2019
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRCALL_HPP_
#define BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRCALL_HPP_

#include <SmiCall.hpp>

class SviProcGetXAddrCall: public SmiCall
{
public:
    SviProcGetXAddrCall();

    void SetSVIVarName(std::string SVIVarName);

    UINT32 getDataSize();

    UINT8* getData();

    ~SviProcGetXAddrCall();

private:
    CHAR*     m_SVIVarName;
    UINT32    m_VarNameLength;
};

#endif /* BEFC_SMI_CALLS_SVI_SVIPROCGETXADDRCALL_HPP_ */
