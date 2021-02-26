/**
 ********************************************************************************
 * @file     DigitalChannel.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DigitalChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CDIGITALCHANNEL_HPP_
#define CDIGITALCHANNEL_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/


/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicChannel.hpp"

/**
 * @brief One Digital Channel of an IO-Module
 */
class DigitalChannel: public BasicChannel
{

public:

    /**
     * @brief Constructor
     */
    DigitalChannel();

    /**
     * @brief Destructor
     */
    virtual ~DigitalChannel();

    /**
    * @brief Write Value to Card
    *
    * @param b8Value value to write
    *
    * @throws a MIOexception when writing to card fails,
    * or a MIOexception if pointer to card is invalid
    */
    VOID setValue(BOOL8 b8Value);

    /**
    * @brief Read Value from Card
    *
    * @return boolean value to channel
    *
    * @throws a MIOexception when reading from card fails,
    * or a MIOexception if pointer to card is invalid
    */
    BOOL8 getValue(VOID);

    BOOL8 isDigitalChannel(){ return true;}
};

#endif /** CDIGITALCHANNEL_HPP_ */
