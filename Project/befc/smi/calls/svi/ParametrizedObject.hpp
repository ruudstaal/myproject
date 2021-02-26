/*
 * ParametrizedObject.hpp
 *
 *  Created on: Mar 7, 2017
 *      Author: madsen
 */

#ifndef BEFC_SMI_CALLS_SVI_PARAMETRIZEDOBJECT_HPP_
#define BEFC_SMI_CALLS_SVI_PARAMETRIZEDOBJECT_HPP_

class ParametrizedObject
{
public:
    ParametrizedObject();
    virtual ~ParametrizedObject(){}

    void setParameter(void *pParameter);
    void* getParameter();


private:

    void *pParam;
};

#endif /* BEFC_SMI_CALLS_SVI_PARAMETRIZEDOBJECT_HPP_ */
