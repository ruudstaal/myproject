/**
 ********************************************************************************
 * @file     Bool8Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Bool8Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Bool8Value.hpp"
#include <svi_e.h>

VOID Bool8Value::setValue(bool value)
{
    this->val = value;
}

bool Bool8Value::getValue()
{
    return this->val;
}

Bool8Value::Bool8Value(BOOL8 value) :
        SviValue(SVI_F_BOOL8)
{
    if (value == 0)
    {
        this->val = false;
    }
    else
    {
        this->val = true;
    }
}

Bool8Value::Bool8Value() :
        SviValue(SVI_F_BOOL8)
{
    this->val = false;
}

UINT32 Bool8Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Bool8Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((BOOL8*)pValue->getValueAddress());
    }
}
