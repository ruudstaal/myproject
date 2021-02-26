/**
 ********************************************************************************
 * @file     SmiStream.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SmiStream
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include "SmiStream.hpp"

SmiStream::SmiStream() :
                std::stringstream(binary | in | out)
{
}

SmiStream::SmiStream(SMI_MSG* pMsg) :
                std::stringstream(binary | in | out)
{
    std::stringstream::write(pMsg->Data, pMsg->DataLen);
}

void SmiStream::write(std::string* pValue, int bytes)
{
    std::stringstream::write(pValue->c_str(), bytes);
}

void SmiStream::write(std::string value, int bytes)
{
    std::stringstream::write(value.c_str(), bytes);
}

void SmiStream::write(UINT8* pValue, int bytes)
{
    std::stringstream::write((char*) pValue, bytes);
}

void SmiStream::write(UINT8 value)
{
    std::stringstream::write((char*) &value, sizeof(value));
}

void SmiStream::write(UINT32 value)
{
    std::stringstream::write((char*) &value, sizeof(value));
}

void SmiStream::write(UINT64 value)
{
    std::stringstream::write((char*) &value, sizeof(value));
}

void SmiStream::write(SINT32 value)
{
    std::stringstream::write((char*) &value, sizeof(value));
}

void SmiStream::write(SINT64 value)
{
    std::stringstream::write((char*) &value, sizeof(value));
}

bool SmiStream::readBool()
{
    BOOL8 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value ? true : false;
}

UINT16 SmiStream::readUINT16()
{
    UINT16 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value;
}

UINT32 SmiStream::readUINT32()
{
    UINT32 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value;
}

UINT64 SmiStream::readUINT64()
{
    UINT64 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value;
}

SINT32 SmiStream::readSINT32()
{
    SINT32 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value;
}

SINT64 SmiStream::readSINT64()
{
    SINT64 value;
    std::stringstream::read((char*) &value, sizeof(value));
    return value;
}

std::string SmiStream::readString(int bytes)
{
    std::stringstream ss;

    for (int i = 0; i < bytes; ++i)
    {
        char c = ((char) get());
        if (c == 0)
            break;
        ss << c;

    }

    /** skip unread bytes (-1 is for '\0' because it's read bit not added to stringstream) */
    skipBytes((bytes - ss.tellp() - 1));

    return ss.str();
}

void SmiStream::skipBytes(int bytes)
{

    seekg(bytes, cur);
}

void SmiStream::read(char* dest, int bytes)
{
    std::stringstream::read(dest, bytes);
}

std::vector<CHAR8> SmiStream::readVector(int bytes)
{
    std::vector<CHAR8> l_vector;

    for (int i = 0; i < bytes; ++i)
    {
        char c = ((char) get());
        l_vector.push_back(c);
    }

    skipBytes(bytes);

    return l_vector;
}


void SmiStream::writeZeroBytes(int bytes)
{
    const char zero = 0;

    for (int i = 0; i < bytes; ++i)
        std::stringstream::write(&zero, 1);
}
