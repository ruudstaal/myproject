/*
 * LocalSviItem.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: madsen
 */


#include <LocalSviItem.hpp>
#include <M1SviSystem.hpp>
#include <SviException.hpp>
#include <SviExportDescriptor.hpp>
#include <SviValue.hpp>
#include <sstream>

LocalSviItem::LocalSviItem(std::string moduleName, std::string varName, UINT32 datatype, UINT32 datalength) : isArray(true), datalength(datalength)
{
    initInternal(moduleName, varName, datatype, NULL);
}

LocalSviItem::LocalSviItem(std::string moduleName, std::string varName, UINT32 datatype) : isArray(false)
{
    initInternal(moduleName, varName, datatype, NULL);
}

VOID LocalSviItem::initInternal(std::string moduleName, std::string varName, UINT32 datatype, pLib lib)
{
    this->moduleName = moduleName;
    this->varName = varName;
    this->datatype = datatype;
    this->int_lib = lib;
    this->value = NULL;

    if (isArray == false)
    {
        this->datalength = SviExportDescriptor::getDataLength(datatype);
        /** Most users expect that 64 bit datatypes are simple values. But they should be treated as arrays */
        if (SviExportDescriptor::isArrayDatatype(datatype))
        {
            this->isArray = true;
        }
    }

    pSviSystem = new M1SviSystem();
}


LocalSviItem::~LocalSviItem()
{
    SAFE_DELETE(value);
    SAFE_DELETE(pSviSystem);
}

std::string LocalSviItem::getModuleName(void)
{
    return moduleName;
}

std::string LocalSviItem::getVarName(void)
{
    return varName;
}

void LocalSviItem::initialize(bool force)
{
    if (int_lib == NULL)
    {
        std::stringstream ss;
        ss << "SviItem with name " << varName << "is not intialized. Please call initialize(..) first" << std::endl;
        throw SviException(ss.str());
    }


    if (isInitialized() && !force)
    {
        return;
    }

    SVI_ADDR valueAddr;
    UINT32 datatype;
    SINT32 res;
    try
    {
        res = pSviSystem->GetAddr(int_lib, (CHAR*) this->varName.c_str(), &valueAddr, &datatype);
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "SystemException while getting address for " << varName << std::endl;
        throw SviException(ss.str());
    }

    std::stringstream ss;
    switch (res)
    {
        case SVI_E_OK:
            initialize(valueAddr, datatype);
            break;
        case SVI_E_UNDEF:
        case SVI_E_ADDR:
        case SVI_E_OLDADDR:
        case SVI_E_FAILED:
        default:
            ss << "Error getting item address for " << varName << ". Result was " << res << std::endl;
            throw SviException(ss.str());
    }
}

void LocalSviItem::initialize(SVI_ADDR valueAddr, UINT32 format, pLib lib)
{
    this->int_lib = lib;
    initialize(valueAddr, format);
}

void LocalSviItem::initialize(SINT32 errorCode)
{
    setError(errorCode);
}

void LocalSviItem::initialize(SVI_ADDR valueAddr, UINT32 format)
{
    bool valid = false;

    if (isArray)
    {
        valid = true;
    }
    else
    {
        valid = this->datatype == (format & SVI_F_SUBTYPEMSK);
    }

    //Seen from server perspective
    setWritable(format & SVI_F_IN);
    setReadable(format & SVI_F_OUT);

    /** mask format to get datatype, and additional information about IN/OUT */
    if (valid)
    {
        setInitialized(true);
        this->valueAddr = valueAddr;
    }
    else
    {
        setInitialized(false);
        std::stringstream ss;
        ss << "Initialize datatype does not match configured " << this->datatype << " != "
                << (format & SVI_F_SUBTYPEMSK) << " for : " << this->getModuleName() << "/"
                << this->getVarName() << std::endl;
        throw SviException(ss.str());
    }
}

SVI_ADDR LocalSviItem::getSviAddr(void)
{
    return valueAddr;
}

UINT32 LocalSviItem::getDatatype(VOID)
{
    return this->datatype;
}

UINT32 LocalSviItem::getDataLength()
{
    return this->datalength;
}

SviValue* LocalSviItem::getValue()
{
    return this->value;
}


VOID LocalSviItem::setValue(SviValue *pValue)
{
    setValueInternal(pValue, true);
}


void LocalSviItem::handleSviResult(SINT32 result)
{
    std::string error = "";
    switch (result)
    {
        case SVI_E_OK:
            return;
        case SVI_E_UNDEF:
            error = "SVI server no longer exists";
            break;
        case SVI_E_ADDR:
            error = "Address is invalid";
            break;
        case SVI_E_FAILED:
            error = "The native write function failed";
            break;
        case SVI_E_WRITE:
            error = "Native Write failed";
            break;
        case SVI_E_OLDADDR:
            error = "Address is no longer valid";
            break;
        case SVI_E_VARINUSE:
            error = "Svi_GetVal: Variable is currently used by another task";
            break;
    }
    throw SviException(error);
}

VOID LocalSviItem::setValueInternal(SviValue *pValue, bool setDirtyFlag) {
    SAFE_DELETE(this->value);
    this->value = pValue;
    if(setDirtyFlag) {
        setDirty(true);
    }
}

void LocalSviItem::updateInternalValue(UINT32 value) {
    this->setValueInternal(factory.createValue(&value, this), false);
}

void LocalSviItem::updateInternalValue(UINT8* pBuf, UINT32 length) {
    this->setValueInternal(factory.createBLKValue(this, pBuf, length), false);
}

UINT32 LocalSviItem::getValueAddress() {
    if(this->value != NULL) {
        return this->value->getValueAddress();
    }
    return 0;
}

bool LocalSviItem::operator==(const LocalSviItem &other) const
{
    if (this->moduleName == other.moduleName && this->varName == other.varName)
    {
        return true;
    }
    return false;
}
