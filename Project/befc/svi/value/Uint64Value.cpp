/**
 ********************************************************************************
 * @file     Uint64Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Uint64Value.hpp"
#include <svi_e.h>

Uint64Value::Uint64Value(UINT64 value) :
        SviValue(SVI_F_UINT64), val(value)
{
}

VOID Uint64Value::setValue(UINT64 value)
{
    this->val = value;
}

UINT64 Uint64Value::getValue()
{
    return this->val;
}

UINT32 Uint64Value::getValueAddress()
{
    return (UINT32)&this->val;
}

void Uint64Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((UINT64*)pValue->getValueAddress());
    }
}
