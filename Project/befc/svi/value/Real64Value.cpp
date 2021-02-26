/**
 ********************************************************************************
 * @file     Real64Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Real64Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Real64Value.hpp"
#include <svi_e.h>

Real64Value::Real64Value(REAL64 value) :
        SviValue(SVI_F_REAL64), val(value)
{
}

VOID Real64Value::setValue(REAL64 value)
{
    this->val = value;
}

REAL64 Real64Value::getValue()
{
    return this->val;
}

UINT32 Real64Value::getValueAddress()
{
    return (UINT32)&this->val;
}

void Real64Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((REAL64*)pValue->getValueAddress());
    }
}
