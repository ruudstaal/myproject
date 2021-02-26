/**
 ********************************************************************************
 * @file     SmiCall.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiCall
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SmiCall.hpp"

SmiCall::SmiCall(UINT32 procedureID, std::string name) :
        proc_id(procedureID), name(name)
{
}
