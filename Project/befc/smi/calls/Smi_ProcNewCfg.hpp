/**
 ********************************************************************************
 * @file     Smi_ProcNewCfg.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcNewCfg
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMI_PROCNEWCFG_HPP_
#define SMI_PROCNEWCFG_HPP_

#include "StreamedSmiRequest.hpp"

/**
 * @addtogroup SMI-CALL
 * @{
 */

class Smi_ProcNewCfg: public StreamedSmiRequest
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Smi_ProcNewCfg
     *
     * @param[in]  pModule          Pointer to BEModule
     *******************************************************************************/
    explicit Smi_ProcNewCfg(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    ~Smi_ProcNewCfg();

    /**
     ********************************************************************************
     * @brief      Read the incoming request, and perform necesary functions.
     *
     *             Read new configuration, and set the return code.
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

#endif  /**SMI_PROCNEWCFG_HPP_*/
