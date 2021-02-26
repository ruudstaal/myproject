/**
 ********************************************************************************
 * @file     InitState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of InitState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "InitState.hpp"
#include "IllegalStateException.hpp"

void InitState::doCfgNew(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doCfgNew")));
}

void InitState::doReset(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doReset")));
}

void InitState::doDeInit(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doDeInit")));
}
