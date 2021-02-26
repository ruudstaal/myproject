/**
 ********************************************************************************
 * @file     AI204.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AI204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AI204_HPP_
#define AI204_HPP_

/*********************************************************************
 * system includes
 *********************************************************************/

/*********************************************************************
 * project includes
 *********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 16 Bit Analog Input Module AI201, AI202; AI204
 *
 * +/- 10V
 */
class AI204: public BasicAnalogModule
{

public:

    /**@{ @name Filter */
    static const UINT32 MODE_FILTER_333HZ; /**< 333 Hz */
    static const UINT32 MODE_FILTER_4kHZ; /**< 4 kHz */
    /**@}*/

    /**@{ @name Samplerate */
    static const UINT32 MODE_SAMPLE1; /**< 1-time */
    static const UINT32 MODE_SAMPLE8; /**< 8-time */
    static const UINT32 MODE_SAMPLE16; /**< 16-time */
    static const UINT32 MODE_SAMPLE32; /**< 32-time */
    /**@}*/

    /**@{ @name Modes */
    static const UINT32 MODE_NO_TEMPCOMP; /**< switch off temperature compensation */
    static const UINT32 MODE_SYNC; /**< use IO-Sync */
    /**@}*/

    /**
     * @brief Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AI204();

    /**
     * @brief Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AI204(UINT32 ui32CardNumber);

    /**
     * @brief Destructor
     */
    virtual ~AI204();

    /**
     * @brief read actual Temperatur
     *
     * @return temperatur in 1/10 K
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 readTemperature(UINT8 ui8Channel);

    /**
     * @brief Start compensation of Temperature
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID startCompensation(UINT8 ui8Channel);

protected:

    /**
     * @brief get Type of Module
     *
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AI204;
    }
};

#endif /** AI204_HPP_ */
