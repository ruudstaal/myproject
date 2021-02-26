/**
 ********************************************************************************
 * @file     SviException.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviException
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIEXCEPTION_HPP_
#define SVIEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup SVI
 * @{
 */

class SviException: public std::exception
{
private:
    std::string _Reason;

public:
    explicit SviException(std::string msg) :
            _Reason(msg)
    {
    }

    explicit SviException(std::stringstream &msg) :
            _Reason(msg.str())
    {
    }

    virtual ~SviException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return _Reason.c_str();
    }

};
/** @} */

#endif  /*SVIEXCEPTION_HPP_*/
