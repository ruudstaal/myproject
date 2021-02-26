/**
 ********************************************************************************
 * @file     BETaskState.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BETaskState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BETASKSTATE_HPP_
#define BETASKSTATE_HPP_

#include <string>

/**
 * @addtogroup TASK
 * @{
 */

class BETask;

class BETaskState
{

public:
    static BETaskState* const STATE_INITIALIZED;
    static BETaskState* const STATE_RUN;
    static BETaskState* const STATE_SUSPENDED;
    static BETaskState* const STATE_TERMINATING;
    static BETaskState* const STATE_TERMINATED;

public:
    /**
     ********************************************************************************
     * @brief      Create an instance BETaskState
     *
     * @param[in]  sStateName        Name of the state
     *******************************************************************************/
    explicit BETaskState(std::string sStateName);

    virtual ~BETaskState()
    {
    }
    ;

    /**
     ********************************************************************************
     * @brief      Default behaviour for start state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pTask			   Pointer to the task
     * @param[in]  autoSuspend         Auto suspend flag (true = start task suspended,
     *                                 false = start tasks running).
     * @throws     IllegalStateException
     *******************************************************************************/
    virtual void start(BETask *pTask, bool autoSuspend);

    /**
     ********************************************************************************
     * @brief      Default behaviour for stop state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pTask			   Pointer to the task
     * @throws     IllegalStateException
     *******************************************************************************/
    virtual void stop(BETask *pTask);

    /**
     ********************************************************************************
     * @brief      Default behaviour for terminate state
     *
     *             Throws illegal state exception
     *
     * @param[in]  pTask			   Pointer to the task
     * @throws     IllegalStateException
     *******************************************************************************/
    virtual void terminate(BETask *pTask);

    /**
     ********************************************************************************
     * @brief      Get name of state
     *
     * @retval     Name of state
     *******************************************************************************/
    std::string getName();

    /**
     ********************************************************************************
     * @brief      Helper function to get exception string for IllegalStateException
     *
     * @param[in]  sFunctionName            Name of the calling function
     * @retval     String with message for IllegalState Exception
     *******************************************************************************/
    std::string getIllegalStateString(std::string sFunctionName);

protected:

private:
    BETaskState()
    {
    }
    ;

    std::string name;
};
/** @} */

#endif  /*BETASKSTATE_HPP_*/
