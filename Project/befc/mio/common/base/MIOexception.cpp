/**
 ********************************************************************************
 * @file     MIOexception.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of MIOexception
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "MIOexception.hpp"

/** Thrown to report MIO errors where card number is known. */
MIOexception::MIOexception(std::string msg, UINT32 ui32CardNumber, SINT32 si32ErrorCode,
        UINT32 ui32Parameter) :
        msg(msg), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(-1), m_Parameter(
                ui32Parameter), m_doCommmand(-1)
{
}

/** Thrown to report MIO errors where card number is known. */
MIOexception::MIOexception(std::stringstream msg, UINT32 ui32CardNumber, SINT32 si32ErrorCode,
        UINT32 ui32Parameter) :
        msg(msg.str()), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(
                -1), m_Parameter(ui32Parameter), m_doCommmand(-1)
{
}

/** Thrown to report MIO errors where card number and channel number is known. */
MIOexception::MIOexception(std::string msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
        SINT32 si32ErrorCode, UINT32 ui32Parameter) :
        msg(msg), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(
                ui32ChannelNumber), m_Parameter(ui32Parameter), m_doCommmand(-1)
{
}

/** Thrown to report MIO errors where card number and channel number is known. */
MIOexception::MIOexception(std::stringstream msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
        SINT32 si32ErrorCode, UINT32 ui32Parameter) :
        msg(msg.str()), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(
                ui32ChannelNumber), m_Parameter(ui32Parameter), m_doCommmand(-1)
{
}

/** Thrown to report MIO doCommand errors where card number and channel number is known. */
MIOexception::MIOexception(std::string msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
        UINT32 ui32doCommmand, SINT32 si32ErrorCode, UINT32 ui32Parameter) :
        msg(msg), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(
                ui32ChannelNumber), m_Parameter(ui32Parameter), m_doCommmand(ui32doCommmand)
{
}

/** Thrown to report MIO doCommand errors where card number and channel number is known. */
MIOexception::MIOexception(std::stringstream msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
        UINT32 ui32doCommmand, SINT32 si32ErrorCode, UINT32 ui32Parameter) :
        msg(msg.str()), m_ErrorCode(si32ErrorCode), m_CardNumber(ui32CardNumber), m_ChannelNumber(
                ui32ChannelNumber), m_Parameter(ui32Parameter), m_doCommmand(ui32doCommmand)
{
}
