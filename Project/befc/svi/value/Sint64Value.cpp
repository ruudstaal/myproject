/**
 ********************************************************************************
 * @file     Sint64Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Sint64Value.hpp"
#include <svi_e.h>

Sint64Value::Sint64Value(SINT64 value) :
        SviValue(SVI_F_SINT64), val(value)
{
}

VOID Sint64Value::setValue(SINT64 value)
{
    this->val = value;
}

SINT64 Sint64Value::getValue()
{
    return this->val;
}

UINT32 Sint64Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Sint64Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((SINT64*)pValue->getValueAddress());
    }
}
