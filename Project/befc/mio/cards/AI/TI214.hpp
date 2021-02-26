/**
 ********************************************************************************
 * @file     TI214.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog temperature module TI214
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef TI214_HPP_
#define TI214_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 *@brief 16 Bit Temperature Input Module TI214
 */
class TI214: public BasicAnalogModule
{
public:

    /**
     * Value for averaging Filter
     */
    typedef enum
    {
        eFilter_16, /**< 16 Values */
        eFilter_64 /**< 64 Values */
    } EFilter_t;

    /** Modes for Thermocouple */
    static const UINT32 MODE_TC_J;
    static const UINT32 MODE_TC_K;
    static const UINT32 MODE_TC_N;
    static const UINT32 MODE_TC_S;

    /** Modes for PTxxx */
    static const UINT32 MODE_PT100;
    static const UINT32 MODE_PT100_2;
    static const UINT32 MODE_PT100_3;
    static const UINT32 MODE_PT1000_2;
    static const UINT32 MODE_PT1000_3;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    TI214();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit TI214(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~TI214();

    /**
     * Set Value for calculating average value
     *
     * @param ui8Channel  - selected Channel
     * @param Filter - Value 16 or 64
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setAverageFilter(UINT8 ui8Channel, TI214::EFilter_t Filter);

    /**
     * get Value for calculating average value
     *
     * @param ui8Channel  - selected Channel
     * @return the average filter value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    TI214::EFilter_t getAverageFilter(UINT8 ui8Channel);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_TI214;
    }
};

#endif /** TI214_HPP_ */
