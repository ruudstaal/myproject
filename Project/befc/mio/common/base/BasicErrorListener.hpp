/**
 ********************************************************************************
 * @file     BasicErrorListener.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicErrorListener
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CBASICERRORLISTENER_HPP_
#define CBASICERRORLISTENER_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>


/**********************************************************************
 * project includes
 **********************************************************************/

/**
 * @brief Abstract Interfaceclass for Error-Listener
 */
class BasicErrorListener
{

protected:

    /**
     * @brief Constructor
     */
    BasicErrorListener(){};

public:

     /**
     *  @brief Destructor
     */
    virtual ~BasicErrorListener(){};

    /**
     * @brief Abstract Callback Method
     *
     * called when attached error occures
     *
     * @param ModuleNb Number of Module generating the error
     * @param Chan Channel with error (0 = Module)
     * @param Error Description of Error MIO_E_xxx
     *
     */
    virtual SINT32 ErrorOccured(UINT32 ModuleNb, UINT32 Chan, UINT32 Error) = 0;


};

#endif /** CBASICERRORLISTENER_HPP_ */
