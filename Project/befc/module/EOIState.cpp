/**
 ********************************************************************************
 * @file     EOIState.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of EOIState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "EOIState.hpp"
#include "BeModule.hpp"
#include "mcpp.hpp"

void EOIState::doEOI(BEModule *pModule)
{
    SINT32 Status;
    jmp_buf JumpEnv;

    /** Install panic handler if a panic handler function has been set during initialization */
    if (pModule->getPanicHandler())
    {
        if ((Status = setjmp(JumpEnv)) == 0)
        {
            pModule->setJumpEnv(JumpEnv);
            /** Running this branch after start.
             * Install signal handler for exceptions and panic situations.
             */
            if (sys_PanicSigSet(pModule->getPanicHandler()) == ERROR)
            {
                error(
                        pModule->getAppName().c_str() << ": Panic-Signal-Handler could not be installed!");
            }
        }
    }

    pModule->startTasks();
}

void EOIState::doCfgNew(BEModule *pModule)
{
    throw(IllegalStateException(getIllegalStateString("doCfgNew")));
}

void EOIState::doRun(BEModule *pModule)
{
    /** Resume all pending tasks */
    pModule->startTasks();
}

