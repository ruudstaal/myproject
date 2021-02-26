/**
 ********************************************************************************
 * @file     Sint16Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint16Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Sint16Value.hpp"
#include <svi_e.h>

Sint16Value::Sint16Value(SINT16 value) :
        SviValue(SVI_F_SINT16), val(value)
{
}

VOID Sint16Value::setValue(SINT16 value)
{
    val = (int) value;
}

SINT16 Sint16Value::getValue()
{
    return val;
}

UINT32 Sint16Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Sint16Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((SINT16*)pValue->getValueAddress());
    }
}
