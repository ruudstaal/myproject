/**
 ********************************************************************************
 * @file     GetModuleInfoCall.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of GetModuleInfoCall
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef GETMODULEINFOCALL_HPP_
#define GETMODULEINFOCALL_HPP_

#include "SmiCall.hpp"

/**
 * @addtogroup SMI-CLIENT
 * @{
 */

class GetModuleInfoCall: public SmiCall
{
public:
    explicit GetModuleInfoCall(UINT8 *pName);
    UINT32 getDataSize();

    UINT8* getData();

private:
    UINT8 *pName;
    GetModuleInfoCall();

};
/** @} */

#endif  /**GETMODULEINFOCALL_HPP_*/
