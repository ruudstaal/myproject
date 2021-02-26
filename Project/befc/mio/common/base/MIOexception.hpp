/**
 ********************************************************************************
 * @file     MIOexception.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of MIOexception
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MIOEXCEPTION_HPP_
#define MIOEXCEPTION_HPP_

#include <exception>
#include <string>
#include <sstream>
#include "mcpp.hpp"

class MIOexception: public std::exception
{
private:
    std::string msg;
    SINT32 m_ErrorCode;
    UINT32 m_CardNumber;
    UINT32 m_ChannelNumber;
    UINT32 m_Parameter;
    UINT32 m_doCommmand;

public:
    /** Thrown to report MIO errors where card number is known. */
    MIOexception(std::string msg, UINT32 ui32CardNumber, SINT32 si32ErrorCode,
            UINT32 ui32Parameter = 0);

    /** Thrown to report MIO errors where card number is known. */
    MIOexception(std::stringstream msg, UINT32 ui32CardNumber, SINT32 si32ErrorCode,
            UINT32 ui32Parameter = 0);

    /** Thrown to report MIO errors where card number and channel number is known. */
    MIOexception(std::string msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
            SINT32 si32ErrorCode, UINT32 ui32Parameter = 0);

    /** Thrown to report MIO errors where card number and channel number is known. */
    MIOexception(std::stringstream msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
            SINT32 si32ErrorCode, UINT32 ui32Parameter = 0);

    /** Thrown to report MIO doCommand errors where card number and channel number is known. */
    MIOexception(std::string msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
            UINT32 ui32doCommmand, SINT32 si32ErrorCode, UINT32 ui32Parameter = 0);

    /** Thrown to report MIO doCommand errors where card number and channel number is known. */
    MIOexception(std::stringstream msg, UINT32 ui32CardNumber, UINT32 ui32ChannelNumber,
            UINT32 ui32doCommmand, SINT32 si32ErrorCode, UINT32 ui32Parameter = 0);

    /** Report deconstructor */
    virtual ~MIOexception() throw ()
    {
    }

    /** Return error message */
    virtual const char* what() const throw ()
    {
        return (msg.c_str());
    }

    /** Return card number */
    virtual const UINT32 CardNumber() const throw ()
    {
        return (m_CardNumber);
    }

    /** Return channel number */
    virtual const UINT32 ChannelNumber() const throw ()
    {
        return (m_ChannelNumber);
    }

    /** Return doCommand number */
    virtual const UINT32 doCommmand() const throw ()
    {
        return (m_doCommmand);
    }

    /** Return MIO error code */
    virtual const SINT32 ErrorCode() const throw ()
    {
        return (m_ErrorCode);
    }

    /** Return Parameter value */
    virtual const UINT32 Parameter() const throw ()
    {
        return (m_Parameter);
    }
};

#endif /** MIOEXCEPTION_HPP_ */
