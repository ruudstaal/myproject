/**
 ********************************************************************************
 * @file     ModuleConfiguration.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    This class is meant for getting parameters from the CRU description
 *           file. It has a optimized search, which makes sure that only the part
 *           of the file, which is relevant for the module is searched.
 *           Please see CRU file description below, to see which input to give to
 *           functions.
 *
 * <CPU_XXX>
 *   [SECTION1]
 *     (Group1)
 *       {Set1}
 *           |Unit1|
 *               Keyword1 = xxxx
 *               Keyword2 = yyyy
 *           |Unit2|
 *               Keyword1 = zzzz
 *       {Set2}
 *           |Unit1|
 *               Keyword1 = xxxx
 *               Keyword2 = yyyy
 *           |Unit2|
 *               Keyword1 = zzzz
 *     (Group2)
 *               Keyword1 = xxxx
 *               Keyword2 = yyyy
 *   [SECTION2]
 *      ...
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef MODULECONFIGURATION_HPP_
#define MODULECONFIGURATION_HPP_

#include <mtypes.h>
#include <msys_e.h>
#include <string>

/**
 * @addtogroup MOD
 * @{
 */

class ModuleConfiguration
{
public:
    /**
     ********************************************************************************
     * @brief      Constructs a ModuleConfiguration object
     *
     * @param[in]  moduleName       The name of the module (case sensitive)
     * @throws     ModuleException  If moduleName is NULL, or moduleName does not exist in mconfig.ini
     *******************************************************************************/
    explicit ModuleConfiguration(std::string moduleName);

    /**
     ********************************************************************************
     * @brief      Constructs a ModuleConfiguration with relation to the line number
     *
     * @param[in]  lineNumber       The linenumber, from where to read the configuration
     * @throws     ModuleException  If..
     *******************************************************************************/
    explicit ModuleConfiguration(std::string moduleName, SINT32 lineNumber);


    /**
     ********************************************************************************
     * @brief      Gets a configuration key as integer.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as integer
     *******************************************************************************/
    SINT32 getConfigAsInt(std::string group, std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as integer.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  set				The name of set when key exist
     * @param[in]  unit				The name of unit when key exist
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as integer
     *******************************************************************************/
    SINT32 getConfigAsInt(std::string group, std::string set, std::string unit,
            std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as decimal number.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as REAL32
     *******************************************************************************/
    REAL32 getConfigAsReal(std::string group, std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as decimal number.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  set              The name of set when key exist
     * @param[in]  unit             The name of unit when key exist
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as REAL32
     *******************************************************************************/
    REAL32 getConfigAsReal(std::string group, std::string set, std::string unit,
            std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as string.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as string
     *******************************************************************************/
    std::string getConfigAsString(std::string group, std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as string.
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  set				The name of set when key exist
     * @param[in]  unit				The name of unit when key exist
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as string
     *******************************************************************************/
    std::string getConfigAsString(std::string group, std::string set, std::string unit,
            std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as boolean
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as boolean
     *******************************************************************************/
    bool getConfigAsBool(std::string group, std::string keyword);

    /**
     ********************************************************************************
     * @brief      Gets a configuration key as boolean
     *
     * @param[in]  group            The name of group where key exists
     * @param[in]  set				The name of set when key exist
     * @param[in]  unit				The name of unit when key exist
     * @param[in]  keyword          The name of the key
     * @throws     ModuleException  If key does not exist in mconfig.ini
     * @retval     The value as boolean
     *******************************************************************************/
    bool getConfigAsBool(std::string group, std::string set, std::string unit, std::string keyword);

    ~ModuleConfiguration()
    {
        ;
    }

private:
    /**
     ********************************************************************************
     * @brief      Helper function to validate result from library
     *
     * @param[in]  lineNbr          Result from profiling function
     * @throws     ModuleException  If lineNbr is below 0
     *******************************************************************************/
    void validateResult(SINT32 lineNbr);
    std::string moduleName; /** The name of the module (case sensitive) */
    SINT32 lineNbr; /** The linenumber where module configuration starts. */
};
/** @} */

#endif  /**MODULECONFIGURATION_HPP_*/
