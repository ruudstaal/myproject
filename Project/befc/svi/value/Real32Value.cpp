/**
 ********************************************************************************
 * @file     Real32Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of real32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Real32Value.hpp"
#include <svi_e.h>

Real32Value::Real32Value(REAL32 value) :
        SviValue(SVI_F_REAL32), val(value)
{
}

REAL32 Real32Value::getValue()
{
    return val;
}

VOID Real32Value::setValue(REAL32 value)
{
    this->val = value;
}

UINT32 Real32Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Real32Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((REAL32*)pValue->getValueAddress());
    }
}
