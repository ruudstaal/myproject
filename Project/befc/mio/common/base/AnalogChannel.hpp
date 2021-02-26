/**
 ********************************************************************************
 * @file     AnalogChannel.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of AnalogChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CANALOGCHANNEL_HPP_
#define CANALOGCHANNEL_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicChannel.hpp"

/**
 * @brief One Analog Channel of an IO-Module
 */
class AnalogChannel: public BasicChannel
{

public:

    /**
     * Constructor
     */
    AnalogChannel();

    /**
     * Destructor
     */
    virtual ~AnalogChannel();

    /**
     * Write Value to Card
     *
     * @param si32Value value to write
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValue(SINT32 si32Value);

    /**
     * Read Value from Card
     *
     * @return Value of the channel
     *
     * @throws an MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getValue(VOID);

    /**
     * Write Value to Card
     *
     * @param ui32Value value to write
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValue(UINT32 ui32Value);

    /**
     * Read Value from Card
     *
     * @return Value of the channel as UINT32
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getValue_UINT32(VOID);

    BOOL8 isDigitalChannel()
    {
        return false;
    }
};

#endif /** CANALOGCHANNEL_HPP_ */
