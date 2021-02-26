/*
 * RemoteSviItem.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: madsen
 */

#include <RemoteSviItem.hpp>
#include "SviExportDescriptor.hpp"
#include "mcpp.hpp"
#include "SviException.hpp"

RemoteSviItem::RemoteSviItem(std::string moduleName, std::string varName, UINT32 datatype) : isArray(false)
{
    initInternal(moduleName, varName, datatype);
}

RemoteSviItem::RemoteSviItem(std::string moduleName, std::string varName, UINT32 datatype, UINT32 datalength) : isArray(true), datalength(datalength)
{
    initInternal(moduleName, varName, datatype);
}

VOID RemoteSviItem::initInternal(std::string moduleName, std::string varName, UINT32 datatype)
{
    this->moduleName = moduleName;
    this->varName = varName;
    this->datatype = datatype;
    this->value = NULL;
    this->numTimeouts = 0;
    if (isArray == false)
    {
        if (SviExportDescriptor::isArrayDatatype(datatype))
        {
            this->isArray = true;
            this->datalength = SviExportDescriptor::getDataLength(datatype);
        }
    }
}

RemoteSviItem::~RemoteSviItem()
{
    SAFE_DELETE(value);
}

std::string RemoteSviItem::getModuleName(VOID){
    return this->moduleName;
}

std::string RemoteSviItem::getVarName(VOID){
    return this->varName;
}

UINT32 RemoteSviItem::getDatatype(VOID){
    return this->datatype;
}

UINT32 RemoteSviItem::getDataLength(){
    return this->datalength;
}

SviValue* RemoteSviItem::getValue(){
    return this->value;
}

VOID RemoteSviItem::setValue(SviValue *pValue){
    setValueInternal(pValue, false);
}

void RemoteSviItem::updateInternalValue(UINT32 value){
    if(this->isArray == false) {
        setValueInternal(valFac.createValue(&value, this->datatype), true);
    }
    else {
        log_Wrn("RemoteSviItem::updateInternalValue (simple value) Called even though type is array. %u", this->datatype);
    }

}

void RemoteSviItem::updateInternalValue(UINT8* pBuf, UINT32 length){
    if(this->isArray) {
        setValueInternal(valFac.createBLKValue(this->datatype, pBuf, length), true);
    }
    else {
        log_Wrn("RemoteSviItem::updateInternalValue (array value) Called even though type is simple. %u", this->datatype);
    }
}

VOID RemoteSviItem::setValueInternal(SviValue *pValue, bool ignoreIfDirty) {
    if(isDirty() && ignoreIfDirty) {
        SAFE_DELETE(pValue);
        return;
    }
    if(this->value == NULL) {
        this->value = pValue;
        setDirty(true);
    }
    else {
        if(this->value->equals(pValue) == false){

            this->value->setValue(pValue);
            setDirty(true);
        }
        SAFE_DELETE(pValue);
    }
}

SviValue* RemoteSviItem::readValue(){
    return value;
}


VOID RemoteSviItem::writeValue(){
    if(value == NULL) {
        //Or throw exception..
        return;
    }
    setDirty(true);
}

void RemoteSviItem::initialize(SVI_ADDR valueAddr, UINT32 format, pLib lib){
    initializeInternal(valueAddr, format);
}

void RemoteSviItem::initialize(SINT32 errorCode){
    setError(errorCode);
    setFailed(true);
}


void RemoteSviItem::initializeInternal(SVI_ADDR valueAddr, UINT32 format)
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
        setFailed(false);

        this->valueAddr = valueAddr;
        this->datalength = SviExportDescriptor::getDataLength(datatype);
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

SVI_ADDR RemoteSviItem::getSviAddr(VOID){
    return this->valueAddr;
}

bool RemoteSviItem::isArrayItem(){
    return isArray;
}
