/**
 ********************************************************************************
 * @file     AI20xSI.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module AI20xSI
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AI20xSI.hpp"

const UINT32 AI20xSI::MODE_20mA = MIO_M_20MA; /**< 4-20mA */
const UINT32 AI20xSI::MODE_4_20mA = MIO_M_04_20MA; /**< -20 - +20mA */
const UINT32 AI20xSI::MODE_PM20mA = MIO_M_PM20MA; /**< Syncmodes - only for AI208/SI */
const UINT32 AI20xSI::MODE_POS_EDGE = MIO_M_POSEDGE; /**< update Input at positive Edge of Sync */
const UINT32 AI20xSI::MODE_NEG_EDGE = MIO_M_NEGEDGE; /**< update at Negative Edge of Sync */
const UINT32 AI20xSI::MODE_BOTH_EDGE = MIO_M_BOTHEDGES; /**< update at both Edges of Sync */
const UINT32 AI20xSI::MODE_CONTINUOUS = MIO_M_CONTINUOUS; /**< continuous update of input */

/**----------------------------------------------------------------- */
AI20xSI::AI20xSI() :
        BasicAnalogModule()
{
    /**  Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AI20xSI::AI20xSI(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();
}

/**----------------------------------------------------------------- */
AI20xSI::~AI20xSI()
{
}

/**----------------------------------------------------------------- */
VOID AI20xSI::setFilter(UINT8 ui8Channel, AI20xSI::EFilter_t eFilter)
{
    UINT32 l_ui32Channel = 0;
    UINT32 l_ui32Filter = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    switch (eFilter)
    {
        case (FILTER_2553):
            l_ui32Filter = 0x0;
            break;
        case (FILTER_1277):
            l_ui32Filter = 0x1;
            break;
        case (FILTER_639):
            l_ui32Filter = 0x2;
            break;
        case (FILTER_319):
            l_ui32Filter = 0x3;
            break;
        case (FILTER_160):
            l_ui32Filter = 0x4;
            break;
        case (FILTER_80):
            l_ui32Filter = 0x5;
            break;
        case (FILTER_40):
            l_ui32Filter = 0x6;
            break;
        case (FILTER_20):
            l_ui32Filter = 0x7;
            break;
        case (FILTER_10):
            l_ui32Filter = 0x8;
            break;
        case (FILTER_5):
            l_ui32Filter = 0x9;
            break;
        case (FILTER_2):
            l_ui32Filter = 0xa;
            break;
        default:
            throw MIOexception("AI20xSI::setFilter: invalid parameter ", m_ui32CardNumber,
                    (UINT32) ui8Channel, MIO_ER_BADPARM);
    }

    BasicIoModule::doCommmand(MIO_CMD_SETFILTER, l_ui32Channel, (SINT32) l_ui32Filter);

}

/**----------------------------------------------------------------- */
AI20xSI::EFilter_t AI20xSI::getFilter(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;
    AI20xSI::EFilter_t l_eFilter;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETFILTER, l_ui32Channel, (SINT32) &l_eFilter);

    return l_eFilter;
}

/**----------------------------------------------------------------- */
VOID AI20xSI::setMinMaxEvent(UINT8 ui8Channel, AI20xSI::SMinMax_t* psLevel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETMINMAXEVENT, l_ui32Channel, (SINT32) psLevel);
}

/**----------------------------------------------------------------- */
AI20xSI::SMinMax_t* AI20xSI::getMinMaxEvent(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETMINMAXEVENT, l_ui32Channel, (SINT32) &m_MinMaxEventLevel);
    return &m_MinMaxEventLevel;
}

/**----------------------------------------------------------------- */
VOID AI20xSI::setMinMaxError(UINT8 ui8Channel, AI20xSI::SMinMax_t* psLevel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_SETMINMAXERROR, l_ui32Channel, (SINT32) psLevel);
}

/**----------------------------------------------------------------- */
AI20xSI::SMinMax_t* AI20xSI::getMinMaxError(UINT8 ui8Channel)
{
    UINT32 l_ui32Channel = 0;

    l_ui32Channel = (UINT32) ui8Channel;

    BasicIoModule::doCommmand(MIO_CMD_GETMINMAXERROR, l_ui32Channel, (SINT32) &m_MinMaxErrorLevel);
    return &m_MinMaxErrorLevel;
}
