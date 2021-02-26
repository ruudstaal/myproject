/**
 ********************************************************************************
 * @file     CfgState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of CfgState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "CfgState.hpp"
#include "IllegalStateException.hpp"

void CfgState::doCfgNew(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doCfgNew")));
}
