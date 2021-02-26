/**
 ********************************************************************************
 * @file     Uint32Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Uint32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Uint32Value.hpp"
#include <svi_e.h>

Uint32Value::Uint32Value(UINT32 value) :
        SviValue(SVI_F_UINT32), val(value)
{
}

VOID Uint32Value::setValue(UINT32 value)
{
    val = value;
}

UINT32 Uint32Value::getValue()
{
    return val;
}

UINT32 Uint32Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Uint32Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((UINT32*)pValue->getValueAddress());
    }
}

