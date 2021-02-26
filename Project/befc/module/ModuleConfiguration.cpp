/**
 ********************************************************************************
 * @file     ModuleConfiguration.cpp
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

#include "mcpp.hpp"
#include <prof_e.h>
#include <iostream>
#include <iosfwd>
#include <string>
#include "ModuleConfiguration.hpp"
#include "ModuleException.hpp"
#include <cstring>

ModuleConfiguration::ModuleConfiguration(std::string moduleName) :
        moduleName(moduleName)
{
    if (moduleName.compare("") > 0)
    {
        this->moduleName = moduleName;

        char TypeName[M_MODNAMELEN + 1];

        //Done to avoid warnings (const char to char conversion - pf functions take char arrays, not const char arrays)
        char partition[] = "Partition";
        char modName[this->moduleName.length() + 1]; // = this->moduleName.
        modName[this->moduleName.length()] = '\0';
        strncpy(modName, this->moduleName.c_str(), this->moduleName.length());


        /** We init this instance with the linenumber of the module configuration - makes searching faster */
        this->lineNbr = pf_GetStrg(modName, NULL, partition, NULL, TypeName, sizeof(TypeName), 0, NULL);

        validateResult(this->lineNbr);
        if (this->lineNbr > 0)
        {
            this->lineNbr--; /** Searching will not work from the same line as group. */
        }
    }
    else
    {
        throw ModuleException("Module name for configuration cannot be NULL");
    }
}

ModuleConfiguration::ModuleConfiguration(std::string moduleName, SINT32 lineNumber) :
        moduleName(moduleName), lineNbr(lineNumber)
{
    //No need to do anything.
}


SINT32 ModuleConfiguration::getConfigAsInt(std::string group, std::string keyword)
{
    SINT line;
    SINT32 res;
    line = pf_GetInt(NULL, (char*) group.c_str(), (char*) keyword.c_str(), 0, &res, this->lineNbr,
    NULL);

    validateResult(line);
    return res;
}

SINT32 ModuleConfiguration::getConfigAsInt(std::string group, std::string set, std::string unit,
        std::string keyword)
{
    SINT line;
    SINT32 res;
    line = pf_GetIntExt(NULL, (UINT8*) group.c_str(), (UINT8*) set.c_str(), (UINT8*) unit.c_str(),
            (UINT8*) keyword.c_str(), 0, &res, this->lineNbr, NULL);

    validateResult(line);
    return res;
}

REAL32 ModuleConfiguration::getConfigAsReal(std::string group, std::string keyword)
{
    std::string str = getConfigAsString(group, keyword);
    double d = strtod(str.c_str(), NULL);
    return (float) d;
}

REAL32 ModuleConfiguration::getConfigAsReal(std::string group, std::string set, std::string unit,
        std::string keyword)
{
    std::string str = getConfigAsString(group, set, unit, keyword);
    double d = strtod(str.c_str(), NULL);
    return (float) d;
}

bool ModuleConfiguration::getConfigAsBool(std::string group, std::string keyword)
{
    BOOL8 res;
    SINT line = pf_GetBool(NULL, (char*) group.c_str(), (char*) keyword.c_str(), 0, &res,
            this->lineNbr, NULL);
    validateResult(line); /** Will throw exception if something is wrong. */
    return res;
}

bool ModuleConfiguration::getConfigAsBool(std::string group, std::string set, std::string unit,
        std::string keyword)
{
    BOOL8 res;
    SINT line = pf_GetBoolExt(NULL, (UINT8*) group.c_str(), (UINT8*) set.c_str(),
            (UINT8*) unit.c_str(), (UINT8*) keyword.c_str(), 0, &res, this->lineNbr, NULL);
    validateResult(line); /** Will throw exception if something is wrong. */
    return res;
}

std::string ModuleConfiguration::getConfigAsString(std::string group, std::string keyword)
{
    char buffer[80];
    memset(buffer, 0, sizeof(buffer));

    SINT line = pf_GetStrg(NULL, (char*) group.c_str(), (char*) keyword.c_str(),
    NULL, buffer, sizeof(buffer), this->lineNbr, NULL);

    validateResult(line); /** Will throw exception if something is wrong. */
    return std::string(buffer);
}

std::string ModuleConfiguration::getConfigAsString(std::string group, std::string set,
        std::string unit, std::string keyword)
{
    char buffer[80];
    memset(buffer, 0, sizeof(buffer));

    SINT line = pf_GetStrgExt(NULL, (UINT8*) group.c_str(), (UINT8*) set.c_str(),
            (UINT8*) unit.c_str(), (UINT8*) keyword.c_str(),
            NULL, (UINT8*) buffer, sizeof(buffer), this->lineNbr, NULL);

    validateResult(line); /** Will throw exception if something is wrong. */

    return std::string(buffer);
}

void ModuleConfiguration::validateResult(SINT32 lineNbr)
{
    if (lineNbr < 0)
    {
        std::string error = "";
        switch (lineNbr)
        {
            case PF_E_NOKEY:
                error = "No such key exists";
                break;
            case PF_E_PARM:
                error = "Invalid parameter";
                break;
            case PF_E_FILEBIG:
                error = "Configuration file is too large";
                break;
            case PF_E_FILEEMPTY:
                error = "Configuration file is empty";
                break;
            case PF_E_NOSEC:
                error = "No such section exists";
                break;
            case PF_E_NOGRP:
                error = "No such group exists";
                break;
            case PF_E_ENDFILE:
                error = "End of file was reached";
                break;
            case PF_E_NOSET:
                error = "Set was not found";
                break;
            case PF_E_NOUNIT:
                error = "Unit was not found";
                break;
        }
        throw ModuleException(error);
    }
}
