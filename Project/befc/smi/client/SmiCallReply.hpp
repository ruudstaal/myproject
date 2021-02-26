/**
 ********************************************************************************
 * @file     SmiCallReply.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiCallReply
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMICALLREPLY_HPP_
#define SMICALLREPLY_HPP_

#include "SmiStream.hpp"

/**
 * @addtogroup SMI-CLIENT
 * @{
 */

class SmiCallReply
{
public:
    virtual void readReply(SmiStream *pStream) = 0;
    virtual void callFailed(UINT32 reason) = 0;
    virtual SINT32 getReturnCode() = 0;
    virtual int getReplySize() = 0;
    virtual ~SmiCallReply()
    {
        ;
    }
};
/** @} */

#endif  /**SMICALLREPLY_HPP_*/
