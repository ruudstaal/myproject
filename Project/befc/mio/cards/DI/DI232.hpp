/**
 ********************************************************************************
 * @file     DI232.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input module DI232
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DI232_HPP_
#define DI232_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input Module DI232
 */
class DI232: public BasicDigitalModule
{
public:

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DI232();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DI232(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DI232();

    /**
     * Set Time for Input Filter
     *
     * @param ui8Channel - Selected Channel 1-32
     * @param ui32Time   - Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setFilter(UINT8 ui8Channel, UINT32 ui32Time);

    /**
     * Get Actual Time for Input Filter
     *
     * @param ui8Channel - Selected Channel 1-32
     * @return Time in us, 0 - 356510 us
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getFilter(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DI232;
    }
};

#endif /** DI232_HPP_ */
