/**
 ********************************************************************************
 * @file     Smi_ProcStop.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Smi_ProcStop
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMI_PROCSTOP_HPP_
#define SMI_PROCSTOP_HPP_

#include <smi_e.h>
#include "StreamedSmiRequest.hpp"

/**
 * @addtogroup SMI-CALL
 * @{
 */

class Smi_ProcStop: public StreamedSmiRequest
{

public:
    /**
     ********************************************************************************
     * @brief      Create an instance of Smi_ProcStop
     *
     * @param[in]  pModule          Pointer to BEModule
     *******************************************************************************/
    explicit Smi_ProcStop(BEModule *pModule);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the smi request.
     *******************************************************************************/
    ~Smi_ProcStop();

    /**
     ********************************************************************************
     * @brief      Read the incoming request, and perform necesary functions.
     *
     *             Perform suspend of application tasks, and set the return code.
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

#endif  /**SMI_PROCSTOP_HPP_*/
