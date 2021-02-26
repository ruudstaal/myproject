/**
 ********************************************************************************
 * @file     TaskException.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of TaskException
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef TASKEXCEPTION_HPP_
#define TASKEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup TASK
 * @{
 */

class TaskException: public std::exception
{
private:
    std::string sMsg;
public:
    explicit TaskException(std::string msg) :
            sMsg(msg)
    {
    }

    explicit TaskException(std::stringstream msg) :
            sMsg(msg.str())
    {
    }
    virtual ~TaskException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return (sMsg.c_str());
    }
};
/** @} */

#endif  /*TASKEXCEPTION_HPP_*/
