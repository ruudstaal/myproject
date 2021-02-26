/**
 ********************************************************************************
 * @file     StreamedSmiRequest.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StreamedSmiRequest
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef STREAMEDSMIREQUEST_HPP_
#define STREAMEDSMIREQUEST_HPP_

/** Includes */
#include "SmiStream.hpp"
#include "SmiRequest.hpp"

/**
 * @addtogroup SMI
 * @{
 */

class StreamedSmiRequest: public SmiRequest
{
public:
    /**
     ********************************************************************************
     * @brief      Create an instance of StreamedSmiRequest
     *
     * @param[in]  procId          SMI procedure ID
     *******************************************************************************/
    explicit StreamedSmiRequest(UINT32 procId);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    virtual ~StreamedSmiRequest();

    /**
     ********************************************************************************
     * @brief      Forward SMI message to readRequest with SmiStream as input
     *
     * @param[in]  pMsg         Pointer to SMI message
     *******************************************************************************/
    void readRequest(SMI_MSG* pMsg);

    virtual void readRequest(SmiStream *pStream) = 0;
};
/** @} */

#endif  /**STREAMEDSMIREQUEST_HPP_*/
