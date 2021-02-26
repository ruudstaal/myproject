/**
 ********************************************************************************
 * @file     SmiReplyWrapper.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiReplyWrapper
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMICALLWRAPPER_HPP_
#define SMICALLWRAPPER_HPP_
#include "mcpp.hpp"

/**
 * @addtogroup SMI
 * @{
 */

class SmiReplyWrapper
{
public:
    SmiReplyWrapper(SmiCallReply *pReply, UINT32 timeout)
    {
        this->timeout = timeout;
        this->pReply = pReply;
    }

    void setTimeout(UINT32 timeout)
    {
        this->timeout = timeout;
    }
    UINT32 getTimeout()
    {
        return this->timeout;
    }
    SmiCallReply* getCallReply()
    {
        return this->pReply;
    }
    ~SmiReplyWrapper()
    {
        ;
    }
private:
    UINT32 timeout;
    SmiCallReply *pReply;

};
/** @} */

#endif  /**SMICALLWRAPPER_HPP_*/
