/*
 * ValueWrapper.hpp
 *
 *  Created on: Nov 2, 2018
 *      Author: madsen
 */

#ifndef BEFC_SVI_ATOMIC_VALUEWRAPPER_HPP_
#define BEFC_SVI_ATOMIC_VALUEWRAPPER_HPP_

#include <atomic/AtomicWrapper.hpp>

/**
 * Template class for wrapping values > 32bit and making it threadsafe. All read/write operations
 * to the value will lock object for other operations.
 *
 * Example use:
 *
 *  ValueWrapper<UINT64> val(100);
 *
 */
template <class T> class ValueWrapper: public AtomicWrapper
{
public:

    ValueWrapper<T>(T val)
    {
        this->value = val;
    }

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value
     *******************************************************************************/
    T getValue()
    {
        lock();
        T res = value;
        unlock();
        return res;
    }

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     *******************************************************************************/
    void setValue(T value)
    {
        lock();
        this->value = value;
        unlock();
    }

    UINT32* getValueAddress()
    {
        return (UINT32*) &value;
    }

    ValueWrapper<T>& operator=(T const & value)
    {
        setValue(value);
        return *this;
    }

    operator T() {return value;}

    ~ValueWrapper(){};

private:

    T value;
};

#endif /* BEFC_SVI_ATOMIC_VALUEWRAPPER_HPP_ */
