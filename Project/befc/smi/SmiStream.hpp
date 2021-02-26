/**
 ********************************************************************************
 * @file     SmiStream.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiStream
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SMI_STREAM_HPP_
#define SMI_STREAM_HPP_

#include <mtypes.h>
#include <smi_e.h>
#include <vector>

#include <sstream>
#include <string>

/**
 * @addtogroup SMI
 * @{
 */

class SmiStream: public std::stringstream
{

public:
    /**
     ********************************************************************************
     * @brief      Default constructor
     *******************************************************************************/
    SmiStream();

    /**
     ********************************************************************************
     * @brief      Create an instance of SmiStream, where stream is initialized with
     *             SMI message
     *
     * @param[in]  pMsg         Pointer to SMI message
     *******************************************************************************/
    explicit SmiStream(SMI_MSG* pMsg);

    /**
     ********************************************************************************
     * @brief      Writes the content of the pointer
     *
     * @param[in]  pValue           Pointer to value to be written
     * @param[in]  bytes            Number of bytes to be written
     *******************************************************************************/
    void write(UINT8* pValue, int bytes);

    /**
     ********************************************************************************
     * @brief      Writes a UINT8
     *
     * @param[in]  value           value to be written
     *******************************************************************************/
    void write(UINT8 value);

    /**
     ********************************************************************************
     * @brief      Writes a UINT32
     *
     * @param[in]  value           value to be written
     *******************************************************************************/
    void write(UINT32 value);

    /**
     ********************************************************************************
     * @brief      Writes a UINT64
     *
     * @param[in]  value           value to be written
     *******************************************************************************/
    void write(UINT64 value);

    /**
     ********************************************************************************
     * @brief      Writes a SINT32
     *
     * @param[in]  value           value to be written
     *******************************************************************************/
    void write(SINT32 value);

    /**
     ********************************************************************************
     * @brief      Writes a SINT64
     *
     * @param[in]  value           value to be written
     *******************************************************************************/
    void write(SINT64 value);

    /**
     ********************************************************************************
     * @brief      Writes a string of n bytes
     *
     * @param[in]  value            String to be written
     * @param[in]  bytes            Number of bytes to be written
     *******************************************************************************/
    void write(std::string value, int bytes);

    /**
     ********************************************************************************
     * @brief      Writes a string of n bytes
     *
     * @param[in]  pValue           pointer to the string to be written
     * @param[in]  bytes            Number of bytes to be written
     *******************************************************************************/
    void write(std::string* pValue, int bytes);

    /**
     ********************************************************************************
     * @brief      Read bool
     *
     * @retval     read value
     *******************************************************************************/
    bool readBool();

    /**
     ********************************************************************************
     * @brief      Read UINT16
     *
     * @retval     read value
     *******************************************************************************/
    UINT16 readUINT16();

    /**
     ********************************************************************************
     * @brief      Read UINT32
     *
     * @retval     read value
     *******************************************************************************/
    UINT32 readUINT32();

    /**
     ********************************************************************************
     * @brief      Read UINT64
     *
     * @retval     read value
     *******************************************************************************/
    UINT64 readUINT64();

    /**
     ********************************************************************************
     * @brief      Read SINT32
     *
     * @retval     read value
     *******************************************************************************/
    SINT32 readSINT32();

    /**
     ********************************************************************************
     * @brief      Read SINT64
     *
     * @retval     read value
     *******************************************************************************/
    SINT64 readSINT64();

    /**
     ********************************************************************************
     * @brief      Read string
     *
     * @retval     read value
     *******************************************************************************/
    std::string readString(int bytes);

    /**
     ********************************************************************************
     * @brief      Skip bytes in stream
     *
     * @param[in]  bytes            Bytes to skip
     *******************************************************************************/
    void skipBytes(int bytes);

    /**
     ********************************************************************************
     * @brief      Write zero(s) to stream
     *
     * @param[in]  bytes            Number of zeros to write
     *******************************************************************************/
    void writeZeroBytes(int bytes);

    /**
     ********************************************************************************
     * @brief      Read a number of bytes inserted into a vector
     *
     * @param[in]  bytes            Number of bytes to read
     *******************************************************************************/
    std::vector<CHAR8> readVector(int bytes);

    /**
     ********************************************************************************
     * @brief      Read a number of bytes, which are copied to the destinaton pointer
     *
     * @param[in]  bytes            Number of bytes to read
     *******************************************************************************/
    void read(char* dest, int bytes);
};
/** @} */

#endif  /**SMI_STREAM_HPP_*/
