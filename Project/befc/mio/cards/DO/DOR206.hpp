/**
 ********************************************************************************
 * @file     DOR206.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital output module DOR206
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DOR2XX_HPP_
#define DOR2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Output Module DOR206
 *
 * Channels: 6
 */
class DOR206: public BasicDigitalModule
{
public:

    /**
     * default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DOR206();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DOR206(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DOR206();

    /**
     * Set Switchcounter of Channel to 0
     *
     * @param ui8Channel - selected Channel 1-6
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID ResetSwitchCount(UINT8 ui8Channel);

    /**
     * Read actual Counter of Channel
     *
     * @param ui8Channel - selected Channel 1-6
     * @returns the relay switch count
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    UINT32 getSwitchCount(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DOR2XX;
    }
};

#endif /** DOR2XX_HPP_ */
