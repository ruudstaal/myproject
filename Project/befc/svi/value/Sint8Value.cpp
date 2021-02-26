/**
 ********************************************************************************
 * @file     Sint8Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Sint8Value.hpp"
#include <svi_e.h>

Sint8Value::Sint8Value(SINT8 value) :
        SviValue(SVI_F_SINT8), val(value)
{
}

VOID Sint8Value::setValue(SINT8 value)
{
    val = value;
}

SINT8 Sint8Value::getValue()
{
    return val;
}

UINT32 Sint8Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Sint8Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((SINT8*)pValue->getValueAddress());
    }
}
