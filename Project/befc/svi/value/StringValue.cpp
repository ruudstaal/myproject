/**
 ********************************************************************************
 * @file     StringValue.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StringValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <string>
#include "StringValue.hpp"
#include "mcpp.hpp"
#include "svi.h"

StringValue::StringValue(std::string value) :
        SviValue(SVI_F_STRING)
{
    setValue(value);

}

StringValue::~StringValue()
{
}

std::string StringValue::getValue()
{
    return this->value;
}

VOID StringValue::setValue(std::string value)
{
    this->value = value;
}

UINT32 StringValue::getValueAddress()
{
    return (UINT32) &this->value;
}

UINT32 StringValue::getLength()
{
    return this->value.size() + 1;
}

void StringValue::setValue(SviValue *pValue) {
    StringValue *pCasted = dynamic_cast<StringValue*>(pValue);
    if(pCasted != NULL) {
        this->value = pCasted->getValue();
    }
}
