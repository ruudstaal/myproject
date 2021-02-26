/**
 ********************************************************************************
 * @file     Version.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Apr 24, 2013 12:25:58 PM 11:00:00 $
 *
 * @brief    This class handles version numbers from different sources in a
 *           unified way, to provide a common version number interface.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef VERSION_CPP_
#define VERSION_CPP_

#include "Version.hpp"
#include "mcpp.hpp"
#include <sstream>

Version::VersionTypeMap_t Version::m_VersionTypeMap = VersionTypeMap_t();

Version::Version()
{
    m_major = 1;
    m_minor = 0;
    m_revision = 1;
    m_type = ALPHA;

    Version::m_VersionTypeMap["Undefined"] = UNDEFINED;
    Version::m_VersionTypeMap["Alpha"] = ALPHA;
    Version::m_VersionTypeMap["Beta"] = BETA;
    Version::m_VersionTypeMap["Release"] = RELEASE;
}

Version::Version(std::string verString)
{
    std::stringstream ss(verString);
    std::string strVersionType;
    char seperator;
    m_major = 0;
    m_minor = 0;
    m_revision = 0;
    ss >> seperator >> m_major >> seperator >> m_minor >> seperator >> m_revision >> strVersionType;

    if (m_VersionTypeMap.find(strVersionType) != m_VersionTypeMap.end())
    {
        m_type = Version::m_VersionTypeMap[strVersionType];
    }
}

Version::Version(int major, int minor, int revision, VERSION_TYPE type)
{
    m_major = major;
    m_minor = minor;
    m_revision = revision;
    m_type = type;
}

Version::Version(SYS_VERSION sysVers)
{
    m_major = sysVers.Code[0];
    m_minor = sysVers.Code[1];
    m_revision = sysVers.Code[2];
    m_type = (Version::VERSION_TYPE) sysVers.Type;
}

Version::~Version(void)
{

}

UINT32 Version::getMajor(void)
{
    return m_major;
}

UINT32 Version::getMinor(void)
{
    return m_minor;
}

UINT32 Version::getRevision(void)
{
    return m_revision;
}

Version::VERSION_TYPE Version::getType(void)
{
    return m_type;
}

std::string Version::getVerString(void)
{
    std::stringstream ss;

    ss << "Version: V" << getMajor() << "." << getMinor() << "." << getRevision() << " ";
    switch(getType())
    {
            case RELEASE:   ss << "Release";    break;
            case BETA:      ss << "Beta";       break;
            case ALPHA:     ss << "Alpha";      break;
            case UNDEFINED:
            default:        ss << "Undefined";  break;
    }
    return (ss.str());
}

#endif  /**VERSION_CPP_*/
