/**
 ********************************************************************************
 * @file     Smi_ProcNull.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcNull
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMI_PROCNULL_HPP_
#define SMI_PROCNULL_HPP_

#include "StreamedSmiRequest.hpp"

/**
 * @addtogroup SMI-CALL
 * @{
 */

class Smi_ProcNull: public StreamedSmiRequest
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Smi_ProcNull
     *******************************************************************************/
    Smi_ProcNull();

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    ~Smi_ProcNull();

    /**
     ********************************************************************************
     * @brief      Read the incoming request, and perform necesary functions.
     *
     * @param[in]  pStream          Pointer to SmiStream with incoming data
     *******************************************************************************/
    void readRequest(SmiStream *pStream);

    /**
     ********************************************************************************
     * @brief      Generate the reply message to the SMI request
     *
     * @retval     NULL         No reply for this request
     *******************************************************************************/
    SmiStream* getReply(void);
};
/** @} */

#endif  /**SMI_PROCNULL_HPP_*/
