/**
 ********************************************************************************
 * @file     SmiRequest.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiRequest
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMIREQUEST_HPP_
#define SMIREQUEST_HPP_

/** Includes */
#include "SmiStream.hpp"

/**
 * @addtogroup SMI
 * @{
 */

class SmiRequest
{
public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Smirequest
     *
     * @param[in]  procId          SMI procedure number
     *******************************************************************************/
    explicit SmiRequest(UINT32 procId);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    virtual ~SmiRequest();

    virtual void readRequest(SMI_MSG* pMsg) = 0;

    virtual SmiStream* getReply(void) = 0;

    /**
     ********************************************************************************
     * @brief      Handle the incoming request
     *
     *             Read the request, generates the reply, and send smi reply.
     *
     * @param[in]  pMsg         Pointer to SMI message
     * @param[in]  pSmiID       Pointer to SMI ID of the SW-module
     *******************************************************************************/
    void handleRequest(SMI_MSG* pMsg, SMI_ID* pSmiID);

    /**
     ********************************************************************************
     * @brief      Get SMI procedure number for the request
     *
     * @retval     SMI procedure number
     *******************************************************************************/
    UINT32 getProcId();

protected:
    UINT32 procId;
};
/** @} */

#endif  /**SMIREQUEST_HPP_*/
