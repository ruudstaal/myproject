/**
 ********************************************************************************
 * @file     BETaskState.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BETaskState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** includes */
#include "BETaskState.hpp"
#include "InitializedState.hpp"
#include "task/RunState.hpp"
#include "SuspendedState.hpp"
#include "TerminatingState.hpp"
#include "TerminatedState.hpp"
#include "IllegalStateException.hpp"

BETaskState* const BETaskState::STATE_INITIALIZED = new InitializedState();
BETaskState* const BETaskState::STATE_RUN = new Task::RunState();
BETaskState* const BETaskState::STATE_SUSPENDED = new SuspendedState();
BETaskState* const BETaskState::STATE_TERMINATING = new TerminatingState();
BETaskState* const BETaskState::STATE_TERMINATED = new TerminatedState();

BETaskState::BETaskState(std::string sStateName) :
        name(sStateName)
{
}

void BETaskState::start(BETask *pTask, bool autoSuspend)
{
    throw IllegalStateException(getIllegalStateString("start()"));
}

void BETaskState::stop(BETask *pTask)
{
    throw IllegalStateException(getIllegalStateString("stop()"));
}

void BETaskState::terminate(BETask *pTask)
{
    throw IllegalStateException(getIllegalStateString("terminate()"));
}

std::string BETaskState::getName()
{
    return name;
}

std::string BETaskState::getIllegalStateString(std::string sFunctionName)
{
    std::stringstream stream;
    stream << sFunctionName << " not allowed in " << name;
    return stream.str();
}

