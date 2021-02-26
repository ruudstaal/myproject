/**
 ********************************************************************************
 * @file     ProcessImageCallback.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProcessImageCallback
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef PROCESSIMAGECALLBACK_HPP_
#define PROCESSIMAGECALLBACK_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include "BeTypes.h"

/**********************************************************************
 * project includes
 **********************************************************************/

/**
 * @brief Abstract Interface Class for Callback Handler
 *
 * Application must create a Derived class which \n
 * implements updateReady(...)
 */
class ProcessImageCallback
{

public:

    /**
     * Default Constructor
     */
    ProcessImageCallback()
    {
    }
    ;

    /**
     * Default Destructor
     */
    virtual ~ProcessImageCallback()
    {
    }
    ;

    /**
     * Interface Method must be implemented
     * by derived class!
     */
    virtual void updateReady(UINT32 ui32UserParameter) = 0;
};

#endif /** PROCESSIMAGECALLBACK_HPP_ */
