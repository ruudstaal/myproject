/**
 ********************************************************************************
 * @file     Uint16Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ArrayValue
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Uint16Value.hpp"
#include <svi_e.h>

Uint16Value::Uint16Value(UINT16 value) :
        SviValue(SVI_F_UINT16), val(value)
{
}

VOID Uint16Value::setValue(UINT16 value)
{
    val = value;
}

UINT16 Uint16Value::getValue()
{
    return val;
}

UINT32 Uint16Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Uint16Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((UINT16*)pValue->getValueAddress());
    }
}
