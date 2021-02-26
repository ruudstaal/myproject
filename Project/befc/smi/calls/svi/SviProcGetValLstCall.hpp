/*
 * SviProcGetValLstCall.hpp
 *
 *  Created on: Mar 19, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTCALL_HPP_
#define RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTCALL_HPP_

#include "ParametrizedObject.hpp"
#include <SmiCall.hpp>
#include <vector>

typedef struct
{
    UINT32      ListLen;        /**< Number of SVI addresses */
    SVI_ADDR    addr[100];        /**< List of SVI addresses */
}GETVALLST_C;

class SviProcGetValLstCall: public SmiCall, public ParametrizedObject
{
public:

    static const UINT32 GETVALLST_MAXITEMSINCALL = 64;

    SviProcGetValLstCall();

    UINT32 getDataSize();

    UINT8* getData();

    virtual ~SviProcGetValLstCall();

    void setAddresses(SVI_ADDR *pList, UINT32 size);

private:

    GETVALLST_C call;

};

#endif /* RES_BEFC_SMI_CALLS_SVI_SVIPROCGETVALLSTCALL_HPP_ */
