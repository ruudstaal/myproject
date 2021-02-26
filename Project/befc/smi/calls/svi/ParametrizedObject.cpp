/*
 * ParametrizedObject.cpp
 *
 *  Created on: Mar 7, 2017
 *      Author: madsen
 */

#include <svi/ParametrizedObject.hpp>
#include "stddef.h"

ParametrizedObject::ParametrizedObject() : pParam(NULL){
}

void ParametrizedObject::setParameter(void *pParameter) {
    this->pParam = pParameter;
}

void* ParametrizedObject::getParameter() {
    return this->pParam;
}

