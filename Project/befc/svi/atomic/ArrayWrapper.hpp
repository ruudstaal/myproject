/*
 * ArrayWrapper.hpp
 *
 *  Created on: Oct 29, 2018
 *      Author: madsen
 */

#ifndef BEFC_SVI_ATOMIC_ARRAYWRAPPER_HPP_
#define BEFC_SVI_ATOMIC_ARRAYWRAPPER_HPP_

#include "mcpp.hpp"
#include "AtomicWrapper.hpp"
#include "SviExportDescriptor.hpp"
#include "SviException.hpp"

/**
 * Template class for wrapping arrays and making it threadsafe. All read/write operations
 * to the array will lock object for other operations.
 *
 * Example use:
 *
 *  ArrayWrapper<UINT64> arrVal(10);
 *
 */
template <class C> class ArrayWrapper : public AtomicWrapper
{
public:
    ArrayWrapper(UINT32 entries) : entries(entries){
        datatype = getDatatype(typeid(C));
        this->datatypeLength = SviExportDescriptor::getDataLength(datatype);
        this->arrLength = datatypeLength * entries;
        pArr = new C[arrLength];
        memset(pArr, 0, arrLength);
    };

    /**
     ********************************************************************************
     * @brief      Sets a value at a specific index in the array
     *
     * @param[in]  index        Index in the array to be set
     * @param[in]  val          The value to set
     *******************************************************************************/
    void setValue(UINT32 index, C val)
    {
        if (index > entries - 1)
        {
            std::stringstream ss;
            ss << "Cannot write to index " << index << ", number of entries is " << entries;
            throw SviException(ss.str());
        }

        lock();
        pArr[index] = val;
        unlock();
    }


    /**
     ********************************************************************************
     * @brief      Gets a value from a specific index
     *
     * @retval     The value
     *******************************************************************************/
    C getValue(UINT32 index)
    {
        if (index > entries - 1)
        {
            std::stringstream ss;
            ss << "Cannot get value at index " << index << ", number of entries is " << entries;
            throw SviException(ss.str());
        }
        lock();
        C res = pArr[index];
        unlock();
        return res;
    }

    /**
     ********************************************************************************
     * @brief      Copy entries from source.
     * @param[in]  pSource          The source buffer
     * @param[in]  numOfEntries     Number entries to copy
     *******************************************************************************/
    void setEntries(C *pSource, UINT32 numOfEntries)
    {
        UINT32 toCopy = numOfEntries * datatypeLength;
        if (toCopy > this->arrLength)
        {
            toCopy = this->arrLength;
        }

        lock();
        memcpy(pArr, pSource, toCopy);
        unlock();
    }

    /**
     ********************************************************************************
     * @brief      Get the length of the array
     * @retval     Length of the array
     *******************************************************************************/
    UINT32 getLength()
    {
        return arrLength;
    }

    /**
     ********************************************************************************
     * @brief      Copy number of entries to destination buffer
     * @param[in]  pDest            Destination buffer
     * @param[in]  numOfEntries     Number of entries to copy (not bytes)
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    void getEntries(C *pDest, UINT32 numOfEntries)
    {
        UINT32 toCopy = numOfEntries * datatypeLength;
        if (numOfEntries > this->entries)
        {
            toCopy = this->arrLength;
        }

        lock();
        memcpy(pDest, pArr, toCopy);
        unlock();
    }

    UINT32* getValueAddress() {
        return (UINT32*)pArr;
    }

    C& operator[](int index)
    {
        return pArr[index];
    }

    virtual ~ArrayWrapper(){};

private:

    UINT32 datatype;

    UINT32 entries;

    UINT32 datatypeLength;

    UINT32 arrLength;

    C *pArr;
};

#endif /* BEFC_SVI_ATOMIC_ARRAYWRAPPER_HPP_ */
