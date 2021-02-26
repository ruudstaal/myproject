/*
 * SmiHandlerErrorListener.hpp
 *
 *  Created on: Apr 12, 2018
 *      Author: madsen
 */

#ifndef RES_BEFC_SMI_SMIHANDLERERRORLISTENER_HPP_
#define RES_BEFC_SMI_SMIHANDLERERRORLISTENER_HPP_

#include "SmiHandler.hpp"

class SmiHandlerErrorListener
{
public:
    SmiHandlerErrorListener(){};

    virtual void systemFailureRecieved(SINT32 failure, SmiHandler *pInstance) = 0;

    virtual ~SmiHandlerErrorListener(){};
};

#endif /* RES_BEFC_SMI_SMIHANDLERERRORLISTENER_HPP_ */
