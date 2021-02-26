/**
********************************************************************************
* @file     ConfigurationException.hpp
* @author   madsen
* @version  $Revision: 000 $ $LastChangedBy: XXXX $
* @date     $LastChangeDate: Nov 5, 2015 1:54:18 PM 11:00:00 $
*
* @brief
*
********************************************************************************
* COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
*******************************************************************************/

#ifndef BEFC_EXCEPTION_CONFIGURATIONEXCEPTION_HPP_
#define BEFC_EXCEPTION_CONFIGURATIONEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>

/**
 * @addtogroup EXP
 * @{
 */

class ConfigurationException: public std::exception
{
private:
    std::string m_msg;

public:
    ConfigurationException(std::string msg) :
            m_msg(msg)
    {
    }
    ConfigurationException(std::stringstream msg) :
            m_msg(msg.str())
    {
    }
    virtual ~ConfigurationException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return m_msg.c_str();
    }
};
/** @} */



#endif /* BEFC_EXCEPTION_CONFIGURATIONEXCEPTION_HPP_ */
