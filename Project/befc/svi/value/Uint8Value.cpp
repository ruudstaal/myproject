/**
 ********************************************************************************
 * @file     Uint8Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Uint8Value.hpp"
#include <svi_e.h>

Uint8Value::Uint8Value(UINT8 value) :
        SviValue(SVI_F_UINT8), val(value)
{
}

VOID Uint8Value::setValue(UINT8 value)
{
    val = value;
}

UINT8 Uint8Value::getValue()
{
    return val;
}

UINT32 Uint8Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Uint8Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((UINT8*)pValue->getValueAddress());
    }
}
