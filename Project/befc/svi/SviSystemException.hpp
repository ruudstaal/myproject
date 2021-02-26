/*
 * SviSystemException.hpp
 *
 *  Created on: May 3, 2019
 *      Author: madsen
 */

#ifndef BEFC_SVI_SVISYSTEMEXCEPTION_HPP_
#define BEFC_SVI_SVISYSTEMEXCEPTION_HPP_

#include "SviException.hpp"

class SviSystemException: public SviException
{
public:

    explicit SviSystemException(std::string msg, UINT32 errorCode) : SviException(msg), errorCode(errorCode)
    {
    }

    explicit SviSystemException(std::stringstream &msg, UINT32 errorCode) : SviException(msg), errorCode(errorCode)
    {
    }

    UINT32 getErrorCode() {
        return errorCode;
    }

    ~SviSystemException() throw (){};

private:

    UINT32 errorCode;


};

#endif /* BEFC_SVI_SVISYSTEMEXCEPTION_HPP_ */
