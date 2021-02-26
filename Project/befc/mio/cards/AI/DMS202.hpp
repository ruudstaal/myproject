/**
 ********************************************************************************
 * @file     DMS202.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of strain gauge module DMS202
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DMS202_HPP_
#define DMS202_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Strain Gauge Module DMS202
 *
 * Channels : 2
 *
 *
 */
class DMS202: public BasicAnalogModule
{

public:

    /**
     * Offset Values for both Channels
     */
    typedef enum
    {
        OFFSET_0, // Offset 0
        OFFSET_1, // Offset 1 mV
        OFFSET_2, // Offset 2 mV
        OFFSET_3, // Offset 3 mV
        OFFSET_4, // Offset 4 mV
        OFFSET_5, // Offset 5 mV
        OFFSET_6, // Offset 6 mV
        OFFSET_7, // Offset 7 mV
        OFFSET_8 // Offset 8 mV
    } EOffset_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DMS202();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DMS202(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~DMS202();

    /**
     * set Offset to Measured Signal
     *
     * @param ui8Channel - selected channel (1,2)
     * @param Value  - Offset 1-8 mV
     * @param b8Save - optional, TRUE = Store Value on Module \n
     *                 optional, FALSE = Value is lost after Reboot
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if parameter is invalid
     */
    VOID setOffset(UINT8 ui8Channel, DMS202::EOffset_t Value, BOOL8 b8Save = FALSE);

    /**
     * read actual Peakvalue
     *
     * @param ui8Channel - selected channel (1,2)
     * @param b8Reset    - TRUE = set Value to zero after read
     *                   - FALSE = just read value
     *
     * @return actual peak Value
     */
    SINT32 getPeak(UINT8 ui8Channel, BOOL8 b8Reset = FALSE);

    /**
     * set offset to Zero
     * This method can need a few seconds to execute!
     * Offset Value from setOffset(..) will be deleted
     *
     * @param ui8Channel - selected channel (1,2)
     * @param b8Save - optional, TRUE = Store Value on Module
     *                 optional, FALSE = Value is lost after Reboot
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     */
    VOID setZero(UINT8 ui8Channel, BOOL8 b8Save = FALSE);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DMS202;
    }
};

#endif /** DMS202_HPP_ */
