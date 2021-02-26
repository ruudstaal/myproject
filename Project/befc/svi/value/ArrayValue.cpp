/**
 ********************************************************************************
 * @file     ArrayValue.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ArrayValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <string>
#include "ArrayValue.hpp"
#include "mcpp.hpp"

ArrayValue::ArrayValue(UINT8 *pArray, UINT32 datatype, UINT32 arrayLength) :
        SviValue(datatype), length(arrayLength)
{
    this->pValue = new UINT8[arrayLength];
    setValue(pArray);
}

ArrayValue::~ArrayValue()
{
    SAFE_DELETE(this->pValue);
}

VOID ArrayValue::setValue(UINT8 *pArray)
{
    memcpy(this->pValue, pArray, this->length);
}

UINT8* ArrayValue::getValue()
{
    return this->pValue;
}

UINT32 ArrayValue::getValueAddress()
{
    return (UINT32) this->pValue;
}

UINT32 ArrayValue::getLength()
{
    return this->length;
}

void ArrayValue::setValue(SviValue *pValue) {
    if(pValue->getLength() == this->length) {
        memcpy(this->pValue, (UINT8*)pValue->getValueAddress(), this->length);
    }
}
