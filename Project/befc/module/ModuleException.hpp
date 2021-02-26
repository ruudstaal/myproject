/**
 ********************************************************************************
 * @file     ModuleException.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ModuleException
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef MODULEEXCEPTION_HPP_
#define MODULEEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup MOD
 * @{
 */

class ModuleException: public std::exception
{
private:
    std::string msg;

public:
    explicit ModuleException(std::string msg) :
            msg(msg)
    {
    }
    explicit ModuleException(std::stringstream msg) :
            msg(msg.str())
    {
    }
    virtual ~ModuleException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return (msg.c_str());
    }
};
/** @} */

#endif  /**MODULEEXCEPTION_HPP_*/
