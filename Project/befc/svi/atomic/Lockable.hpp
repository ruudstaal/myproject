/*
 * Lockable.hpp
 *
 *  Created on: Oct 22, 2018
 *      Author: madsen
 */

#ifndef BEFC_SVI_ATOMIC_LOCKABLE_HPP_
#define BEFC_SVI_ATOMIC_LOCKABLE_HPP_

#include "mcpp.hpp"

/**
 * Interface class for providing a handler which can lock and unlock to avoid race conditions
 * in a multithreaded system
 *
 * lock function should provide thread safe functionality which means, that only first thread is
 * allowed to lock (the object) and return from the function. Afterwards, all other threads should
 * wait in the lock function, until thread 1 unlocks it by calling the unlock function
 *
 * Semaphors is one way of doing this.
 *
 */
class Lockable
{
public:
    Lockable(){}

    virtual SINT32 lock() = 0;

    virtual SINT32 unlock() = 0;

    virtual ~Lockable(){}
};

#endif /* BEFC_SVI_ATOMIC_LOCKABLE_HPP_ */
