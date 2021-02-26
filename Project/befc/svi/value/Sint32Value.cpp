/**
 ********************************************************************************
 * @file     Sint32Value.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of Sint32Value
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "Sint32Value.hpp"
#include <svi_e.h>

Sint32Value::Sint32Value(SINT32 value) :
        SviValue(SVI_F_SINT32), val(value)
{
}

VOID Sint32Value::setValue(SINT32 value)
{
    val = (int) value;
}

SINT32 Sint32Value::getValue()
{
    return val;
}

UINT32 Sint32Value::getValueAddress()
{
    return (UINT32) &this->val;
}

void Sint32Value::setValue(SviValue *pValue) {
    if(pValue->getLength() == getLength()) {
        this->val = *((SINT32*)pValue->getValueAddress());
    }
}
