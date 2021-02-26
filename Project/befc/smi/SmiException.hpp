/**
 ********************************************************************************
 * @file     SmiException.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiException
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMIEXCEPTION_HPP_
#define SMIEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup SMI
 * @{
 */

class SmiException: public std::exception
{
private:
    std::string _Reason;

public:
    explicit SmiException(std::string msg) :
            _Reason(msg)
    {
    }

    explicit SmiException(std::stringstream msg) :
            _Reason(msg.str())
    {
    }

    virtual ~SmiException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return (_Reason.c_str());
    }

};
/** @} */

#endif  /**SMIEXCEPTION_HPP_*/
