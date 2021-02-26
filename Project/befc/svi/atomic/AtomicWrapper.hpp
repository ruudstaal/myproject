/*
 * AtomicWrapper.hpp
 *
 *  Created on: Oct 24, 2018
 *      Author: madsen
 */

#ifndef BEFC_SVI_ATOMIC_ATOMICWRAPPER_HPP_
#define BEFC_SVI_ATOMIC_ATOMICWRAPPER_HPP_

#include "mcpp.hpp"
#include "semLib.h"
#include "Lockable.hpp"

class AtomicWrapper : public Lockable
{
public:
    AtomicWrapper();

    /**
     ********************************************************************************
     * @brief      Returns the address to the value.
     *             DO NOT!! write to this address
     *
     * @retval     The address to the value
     *******************************************************************************/
    virtual UINT32* getValueAddress() = 0;

    virtual ~AtomicWrapper();

    static UINT32 getDatatype(const std::type_info& inf);
protected:
    SINT32 lock();

    SINT32 unlock();


private:
    SEM_ID semaLock;

};

#endif /* BEFC_SVI_ATOMIC_ATOMICWRAPPER_HPP_ */
