/**
 ********************************************************************************
 * @file     SmiCall.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiCall
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMICALL_HPP_
#define SMICALL_HPP_

#include <string>
#include "mtypes.h"
#include "Smi.h"

/**
 * @addtogroup SMI-CLIENT
 * @{
 */

class SmiCall
{
public:

    SmiCall(UINT32 procedureID, std::string name);

    UINT32 getProcedureId()
    {
        return proc_id;
    }
    std::string getName()
    {
        return name;
    }

    /** Virtual functions*/
    virtual UINT32 getDataSize() = 0;
    virtual UINT8* getData() = 0;
    virtual ~SmiCall()
    {
        ;
    }

private:
    UINT32 proc_id;
    std::string name;

};
/** @} */

#endif  /**SMICALL_HPP_*/
