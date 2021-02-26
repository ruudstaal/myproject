/**
 ********************************************************************************
 * @file     BasicEventListener.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicEventListener
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CBASICEVENTLISTENER_HPP_
#define CBASICEVENTLISTENER_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>


/**********************************************************************
 * project includes
 **********************************************************************/

/**
 * @brief Abstract Interfaceclass for Event-Listener
 */
class BasicEventListener
{

protected:

    /**
     * @brief Constructor
     */
    BasicEventListener(){};

public:

    /**
     *  @brief Destructor
     */
    virtual ~BasicEventListener(){};

    /**
     * @brief Abstract Callback Method \n
     *        Must be implemented by derived class.
     *
     * Is called when attached event occures.
     *
     * @param ModuleNb Number of Module
     * @param Chan Channel with Event (0 = Module)
     * @param Event Description of event MIO_EV_xxx
     *
     * @returns 0  = ok
     * @returns <0 = error
     *
     */
    virtual SINT32 EventOccured(UINT32 ModuleNb, UINT32 Chan, UINT32 Event) = 0;
};

#endif /** CBASICEVENTLISTENER_HPP_ */
