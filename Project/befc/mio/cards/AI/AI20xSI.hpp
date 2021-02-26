/**
 ********************************************************************************
 * @file     AI20xSI.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AI20xSI
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CAI20XSI_HPP_
#define CAI20XSI_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************
 */
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 16 Bit Analog Input Module AI202/SI, AI204/SI, AI208/SI
 *
 * AI202/SI AI204/SI: \n
 * 0-20mA 16 Bit \n
 *
 * AI208/SI:  \n
 * 0-20mA, 4-20mA, +/-20mA \n
 * 13-16 Bit depends on Filtersettings
 */
class AI20xSI: public BasicAnalogModule
{

public:

    /**
     * @brief Possible Values for Filter
     */
    typedef enum
    {
        FILTER_2553,
        FILTER_1277,
        FILTER_639,
        FILTER_319,
        FILTER_160,
        FILTER_80,
        FILTER_40,
        FILTER_20,
        FILTER_10,
        FILTER_5,
        FILTER_2
    } EFilter_t;

    /**
     * @brief Structure for MinMaxEvent ,MinMaxError
     *
     * @see setMinMaxError, setMinMaxEvent
     */
    typedef struct
    {
        SINT32 si32Min;
        SINT32 si32Max;
    } SMinMax_t;

    /**@{ @name Modes */
    static const UINT32 MODE_20mA; /**< 0-20mA */
    static const UINT32 MODE_4_20mA; /**< 4-20mA */
    static const UINT32 MODE_PM20mA; /**< -20 - +20mA */
    /**@}*/

    /**@{ @name Syncmodes - only for AI208/SI */
    static const UINT32 MODE_POS_EDGE; /**< update Input at positive Edge of Sync    */
    static const UINT32 MODE_NEG_EDGE; /**< update at Negative Edge of Sync    */
    static const UINT32 MODE_BOTH_EDGE; /**< update at both Edges of Sync       */
    static const UINT32 MODE_CONTINUOUS;/**< continuous update of input         */
    /**@}*/

    /**
     * @brief default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AI20xSI();

    /**
     * @brief Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AI20xSI(UINT32 ui32CardNumber);

    /**
     * @brief default Destructor
     */
    virtual ~AI20xSI();

    /**
     * @brief Set Time for Input Filter
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @param eFilter   - Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid,
     * or a MIOexception if parameter is invalid
     */
    VOID setFilter(UINT8 ui8Channel, AI20xSI::EFilter_t eFilter);

    /**
     * @brief Get Actual Time for Input Filter
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @return actual configured Time
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AI20xSI::EFilter_t getFilter(UINT8 ui8Channel);

    /**
     * @brief Set Level for Min/Max Eventinterrupt
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @param psLevel   - Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMinMaxEvent(UINT8 ui8Channel, AI20xSI::SMinMax_t* psLevel);

    /**
     * @brief Get Level for Min/Max Eventinterrupt
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @return limit values of the event interrupt
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AI20xSI::SMinMax_t* getMinMaxEvent(UINT8 ui8Channel);

    /**
     * @brief Set Level for Min/Max Errorinterrupt
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @param psLevel   - Time in us to set, 0 - 356510 us
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMinMaxError(UINT8 ui8Channel, AI20xSI::SMinMax_t* psLevel);

    /**
     * @brief Get Level for Min/Max Errorinterrupt
     *
     * @note only for AI208/SI
     *
     * @param ui8Channel - Selected Channel 1-32
     * @return limit values of the error interrupt
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    AI20xSI::SMinMax_t* getMinMaxError(UINT8 ui8Channel);

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
        return BasicIoModule::TYPE_AI20XSI;
    }

private:
    AI20xSI::SMinMax_t m_MinMaxEventLevel;
    AI20xSI::SMinMax_t m_MinMaxErrorLevel;
};

#endif /** CAI20XSI_HPP_ */
