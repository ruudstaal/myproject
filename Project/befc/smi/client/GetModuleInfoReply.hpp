/**
 ********************************************************************************
 * @file     GetModuleInfoReply.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of GetModuleInforeply
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/
#include "mtypes.h"
#include "Smi.h"
#include "SmiCallReply.hpp"

/** Avoid problems with multiple inclusion */
#ifndef GETMODULEINFOREPLY_HPP_
#define GETMODULEINFOREPLY_HPP_

/**
 * @addtogroup SMI-CLIENT
 * @{
 */

class GetModuleInfoReply: public SmiCallReply
{
public:
    GetModuleInfoReply();

    void readReply(SmiStream *pStream);

    void callFailed(UINT32 procID, UINT32 reason);

    SINT32 getReturnCode();

    int getReplySize();

    std::string getDescription(){return desc;}

    UINT32 getVersion(){return verscode;}

    UINT32 getState(){return state;}

    UINT32 getDebug(){return debugMode;}

private:
    SINT32 returncode;
    std::string moduleName;
    std::string desc;
    UINT32 vType;
    UINT32 verscode;
    UINT32 state;
    UINT32 debugMode;
};
/** @} */

#endif  /**GETMODULEINFOREPLY_HPP_*/
