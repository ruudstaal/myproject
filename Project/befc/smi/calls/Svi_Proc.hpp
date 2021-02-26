/**
 ********************************************************************************
 * @file     Smi_Proc.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_Proc
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVI_PROC_HPP_
#define SVI_PROC_HPP_

#include "SviServer.hpp"
#include "SmiRequest.hpp"

/**
 * @addtogroup SMI-CALL
 * @{
 */

class Svi_Proc: public SmiRequest
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Svi_Proc
     *
     * @param[in]  pSviServer          Pointer to SviServer
     * @param[in]  procNb              Smi proc number
     *******************************************************************************/
    Svi_Proc(SviServer* pSviServer, UINT32 procNb);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    ~Svi_Proc();

    /**
     ********************************************************************************
     * @brief      Read the incoming request, and perform necesary functions.
     *
     * @param[in]  pMsg          Pointer to SMI message
     *******************************************************************************/
    void readRequest(SMI_MSG* pMsg);

    /**
     ********************************************************************************
     * @brief      Generate the reply message to the SMI request
     *
     * @retval     NULL        No reply needed for this message
     *******************************************************************************/
    SmiStream* getReply(void);

protected:
    SviServer* pSviServer;
};
/** @} */

#endif  /**SVI_PROC_HPP_*/
