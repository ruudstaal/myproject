/**
 ********************************************************************************
 * @file     DIO232.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DIO232_HPP_
#define DIO232_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/


/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input/Output Module DIO232
 */
class DIO232: public BasicDigitalModule
{
public:

    /** Channelmodes */
    static const UINT32 MODE_POSEDGE;
    static const UINT32 MODE_NEGEDGE;
    static const UINT32 MODE_BOTHEDGES;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DIO232();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DIO232(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DIO232();

    /**
     * Set Time for Inputfilter
     *
     * @param ui8Channel - selected channel 1-32
     * @param ui32Time - Time from 0 to 356510us
     *                   steps in 5.44us!
     *
	 * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilterTime(UINT8 ui8Channel, UINT32 ui32Time);

    /**
     * Read Time for Inputfilter
     *
     * @param ui8Channel - selected channel 1-32
     * @return Time from 0 to 356510us
     *         steps in 5.44us!
     *
	 * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFilterTime(UINT8 ui8Channel);

protected:

    /**
    * get Type of Module
    * see BasicIoModule::TYPE_xxxxx
    *
    * @returns > 0 - Type
    */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DIO232;
    }

};

#endif /** DIO232_HPP_ */
