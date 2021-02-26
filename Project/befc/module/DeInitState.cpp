/**
 ********************************************************************************
 * @file     DeInitState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DeInitState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DeInitState.hpp"
#include "IllegalStateException.hpp"

void DeInitState::doCfgNew(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doCfgNew")));
}

void DeInitState::doDeInit(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doDeInit")));
}
