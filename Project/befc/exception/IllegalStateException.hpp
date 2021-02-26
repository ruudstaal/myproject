/**
 ********************************************************************************
 * @file     IllegalStateException.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Mar 19, 2013 12:36:00 PM 11:00:00 $
 *
 * @brief    Illegal state exception class, used in case of illegal state
 *           changes in @see BEModule and @see BETask.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef ILLEGALSTATEEXCEPTION_HPP_
#define ILLEGALSTATEEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup EXP
 * @{
 */

class IllegalStateException: public std::exception
{
private:
    std::string m_msg;

public:
    IllegalStateException(std::string msg) :
            m_msg(msg)
    {
    }
    IllegalStateException(std::stringstream msg) :
            m_msg(msg.str())
    {
    }
    virtual ~IllegalStateException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return m_msg.c_str();
    }
};
/** @} */

#endif  /** ILLEGALSTATEEXCEPTION_HPP_*/
