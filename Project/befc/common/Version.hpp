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
#ifndef VERSION_HPP_
#define VERSION_HPP_

#include <msys.h>
#include <BEFCTypes.hpp>
#include <string>
#include <map>

/**
 * @addtogroup COM
 * @{
 */

/**
 * @brief ContainerClass of Version.
 *
 */class Version
{
public:
    /**
     * Possible Values of Version Type
     */
    typedef enum
    {
        UNDEFINED = 0, ALPHA = 1, BETA = 2, RELEASE = 3
    } VERSION_TYPE;

    /**
     * Type defintion of Map
     * with Type of Version as String and enum Value
     */
    typedef std::map<std::string, VERSION_TYPE> VersionTypeMap_t;

    /**
     ********************************************************************************
     * @brief Constructor of Version. Create the Version V1.00.01 Alpha
     *******************************************************************************/
    Version();

    /**
     ********************************************************************************
     * @brief Constructor of Version. Create the Version V1.00.01 Alpha
     *
     * @param[in]  verString  Version string from project
     *******************************************************************************/
    explicit Version(std::string verString);

    /**
     ********************************************************************************
     * @brief Constructor of Version.
     *
     * @param[in]  major The major number of the version
     * @param[in]  minor The minor number of the version
     * @param[in]  revision The revision number of the version
     * @param[in]  type The type of the version Alpha, Beta or Release
     *******************************************************************************/
    Version(int major, int minor, int revision, VERSION_TYPE type);

    /**
     ********************************************************************************
     * @brief Constructor of Version.
     *
     * @param[in]  sysVers System version struct SYS_VERSION @see msys.h
     *******************************************************************************/
    explicit Version(SYS_VERSION sysVers);

    /**
     ********************************************************************************
     * @brief Destructor of Version.
     *******************************************************************************/
    ~Version();

    /**
     ********************************************************************************
     * @brief   Get the major number of the version.
     *
     * @retval     the major number of the version
     *******************************************************************************/
    UINT32 getMajor(void);

    /**
     ********************************************************************************
     * @brief   Get the minor number of the version.
     *
     * @retval     the minor number of the version
     *******************************************************************************/
    UINT32 getMinor(void);

    /**
     ********************************************************************************
     * @brief   Get the revision number of the version.
     *
     * @retval     the revision number of the version
     *******************************************************************************/
    UINT32 getRevision(void);

    /**
     ********************************************************************************
     * @brief   Get the type of the version.
     *
     * @retval     the type of the version (Alpha, Beta, Release)
     *******************************************************************************/
    VERSION_TYPE getType(void);

    /**
     ********************************************************************************
     * @brief   Get version in a string.
     *
     * @retval     version information as a string
     *******************************************************************************/
    std::string getVerString(void);

private:
    static VersionTypeMap_t m_VersionTypeMap; /**< map with Version types */

    int m_major; /**< Major Version Number */
    int m_minor; /**< Minor Version Number */
    int m_revision; /**< Revision Version Number*/
    VERSION_TYPE m_type; /**< Type of Version */
};
/** @} */

#endif  /** VERSION_HPP_*/
