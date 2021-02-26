/**
 ********************************************************************************
 * @file     Smi_ProcRun.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcRun
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMI_PROCRUN_HPP_
#define SMI_PROCRUN_HPP_

#include "StreamedSmiRequest.hpp"

/**
 * @addtogroup SMI-CALL
 * @{
 */

class Smi_ProcRun: public StreamedSmiRequest
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Smi_ProcRun
     *
     * @param[in]  pModule          Pointer to BEModule
     *******************************************************************************/
    explicit Smi_ProcRun(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    ~Smi_ProcRun();

    /**
     ********************************************************************************
     * @brief      Read the incoming request, and perform necesary functions.
     *
     *             Perform run, and set the return code.
     *
     * @param[in]  pStream          Pointer to SmiStream with incoming data
     *******************************************************************************/
    void readRequest(SmiStream *pStream);

    /**
     ********************************************************************************
     * @brief      Generate the reply message to the SMI request
     *
     * @retval     SmiStream        Stream with reply to SMI request
     *******************************************************************************/
    SmiStream* getReply(void);

private:
    BEModule *pModule;
    SINT32 retCode;
};
/** @} */

#endif  /**SMI_PROCRUN_HPP_*/
