/*
 * GenericSviBlkItem.hpp
 *
 *  Created on: Mar 26, 2019
 *      Author: madsen
 */

#ifndef BEFC_SVI_SVIBLKITEM_HPP_
#define BEFC_SVI_SVIBLKITEM_HPP_

#include <AbstractSviItem.hpp>
#include "log_e.h"
#include <sstream>
#include "SviException.hpp"
#include "mcpp.hpp"
#include <string>


/**
 ********************************************************************************
 * @brief              Template class for reading BLK values from the SVI layer.
 *                     Usage for an SVI array of REAL32. Length will be determined
 *                     during initialization from the SVI layer. Item should be added
 *                     to the AbstractSviGroup interface for initialization and updates.
 *
 *   SviBlkItem<REAL32> *pItem = new SviBlkItem<REAL32>("MyModule", "SomeReal32Array");
 *
 *******************************************************************************/
template<class C> class SviBlkItem: public AbstractSviItem
{
public:

    /**
     ********************************************************************************
     *
     * @brief      Creates an instance of the SviBlkItem for array values. This is also
     *             used for SVI_F_STRING and other SVI_F_BLK types
     *
     * @param[in]  moduleName  The name of the module
     * @param[in]  varName     The name of the variable (without module prefix)
     *******************************************************************************/
    SviBlkItem(std::string modulename, std::string varname) :
            moduleName(modulename), varName(varname), pArr(NULL), arrLength(0), int_lib(NULL), datatype(
                    0), entryCount(0)
    {
    }

    /**
     ********************************************************************************
     * @brief      Gets the value as string.
     *
     * @retval     The bytes converted to a std::string
     * @throws     a SviException if type recieved from SVI layer is not a SVI_F_STRING
     *             or if svi variable is not readable.
     *******************************************************************************/
    std::string getValAsString()
    {
        validateInitializedAndReadable();

        if(datatype == SVI_F_STRING){
            return std::string(reinterpret_cast<char const*>(this->pArr));
        }

        std::stringstream ss;
        ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                << ": getValAsString called, but item is not of type SVI_F_STRING. Type was :  "
                << std::hex << datatype;
        throw SviException(ss.str());
    }

    /**
     ********************************************************************************
     * @brief               Sets the value as string.
     * @param[in]  size     Size of the source char array
     *
     * @throws              a SviException if input value size is larger than size received
     *                      from SVI layer or item is not writeable
     *******************************************************************************/
    void setValAsString(std::string value)
    {
        if (isWriteable() == false)
        {
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << ": is not writeable - cannot write to it";

            throw SviException(ss.str());

        }

        if (value.length() <= arrLength)
        {
            memset(pArr, 0, this->arrLength); //In case string is shorter
            memcpy(this->pArr, value.c_str(), value.length());
            setDirty(true);
        }
        else
        {
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << ": Cannot set value as std::string since size to set is bigger than SVI variable size. "
                    << arrLength << ":" << value.length();
            throw SviException(ss.str());
        }
    }

    /**
     ********************************************************************************
     * @brief                  Sets the value as char array
     *
     * @param[in]  pCharArray  Pointer to the source char array
     * @param[in]  size        Size of the source char array
     *
     * @throws                 a SviException if input value size is larger than size
     *                         recieved from SVI layer or item is not writeable
     *******************************************************************************/
    void setValAsCharArray(char *pCharArray, UINT32 size)
    {
        if (isWriteable() == false)
        {
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << ": is not writeable - cannot write to it";

            throw SviException(ss.str());

        }

        if (size <= arrLength)
        {
            memcpy(this->pArr, pCharArray, size);
            setDirty(true);
        }
        else
        {
            std::stringstream ss;
            if (isInitialized())
            {
                ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                        << ": Cannot set value as Char array since size to set is bigger than SVI variable size. "
                        << arrLength << ":" << size;
            }
            else
            {
                ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                        << ": is not initialized - settings values are not allowed yet";
            }
            throw SviException(ss.str());
        }
    }

    /**
     ********************************************************************************
     * @brief                    Copies the value to a destination buffer
     *
     * @param[in]  pDestination  Pointer to the destination buffer
     * @param[in]  size          Number of bytes to copy to destination buffer
     *
     * @throws                   a SviException if item is not readable
     *******************************************************************************/
    void getVal(C *pDestination, UINT32 size)
    {
        validateInitializedAndReadable();

        if (size <= arrLength)
        {
            memcpy(pDestination, this->pArr, size);
        }
        else
        {
            memcpy(pDestination, this->pArr, arrLength);
        }
    }

    /**
     ********************************************************************************
     * @brief                  Sets the value with input pointer
     *
     * @param[in]  pCharArray  Pointer to the source char array
     * @param[in]  size        Size of the source char array
     *
     * @throws                 a SviException if input value size is larger than size
     *                         recieved from SVI layer or item is not writeable
     *******************************************************************************/
    void setVal(C *pSource, UINT32 size)
    {
        if (size <= arrLength)
        {
            memcpy(this->pArr, pSource, size);
        }
        else
        {
            memcpy(this->pArr, pSource, arrLength);
        }
    }

    /**
     ********************************************************************************
     * @brief                  Sets the value at specific index in array
     *
     * @param[in]  index       Index to write value to (0-based)
     * @param[in]  val         Value to write to index in array
     *
     * @throws                 a SviException if index is larger than size of array
     *                         recieved from SVI.
     *******************************************************************************/
    void setVal(UINT32 index, C val)
    {
        if (index >= entryCount)
        {
            std::stringstream ss;
            ss << "Cannot write to index " << index << ", number of entries is " << entryCount;
            throw SviException(ss.str());
        }

        pArr[index] = val;
    }

    /**
     ********************************************************************************
     * @brief               Gets the value from a specific index in the array
     *
     * @param[in]  index    The index in the array to get the value from
     * @retval              The value at the specified index
     *
     * @throws              a SviException if item is not readable or index is outside
     *                      array size.
     *******************************************************************************/
    C getVal(UINT32 index)
    {
        validateInitializedAndReadable();

        if (index >= entryCount)

        {
            std::stringstream ss;
            ss << "Cannot get value at index " << index << ", number of entries is " << entryCount;
            throw SviException(ss.str());
        }

        C res = pArr[index];
        return res;
    }

    C& operator[](int index)
    {
        if (index >= entryCount)
        {
            std::stringstream ss;
            ss << "Cannot access index " << index << " in array, number of entries is " << entryCount;
            throw SviException(ss.str());
        }

        return pArr[index];
    }

    std::string getModuleName(VOID)
    {
        return this->moduleName;
    }

    std::string getVarName(VOID)
    {
        return this->varName;
    }

    UINT32 getDatatype(VOID)
    {
        return this->datatype;
    }

    UINT32 getDataLength()
    {
        return this->arrLength;
    }

    const UINT32 getEntryCount()
    {
        return this->entryCount;
    }

    void initialize(SINT32 errorCode)
    {
        setError(errorCode);
        if (errorCode != SVI_E_OK)
        {
            setFailed(true);
        }
    }

    void initialize(SVI_ADDR valueAddr, UINT32 format, pLib lib)
    {
        this->int_lib = lib;
        initInternal(valueAddr, format);
    }

    SVI_ADDR getSviAddr(VOID)
    {
        return this->valueAddr;
    }

    bool isArrayItem()
    {
        return true;
    }

    pLib getLib()
    {
        return this->int_lib;
    }

private:

    std::string moduleName;

    std::string varName;

    C *pArr;

    UINT32 arrLength;

    pLib int_lib;

    UINT32 datatype;

    SVI_ADDR valueAddr;

    UINT32 entryCount;

    void initInternal(SVI_ADDR valueAddr, UINT32 format)
    {
        setWritable(format & SVI_F_IN);
        setReadable(format & SVI_F_OUT);

        datatype = (format & SVI_F_TYPEMSK);

        if ((format & SVI_F_BLK) || datatype == SVI_F_STRING)
        {
            this->arrLength = (format >> 16);

            entryCount = 0;
            if((arrLength % sizeof(C)) != 0) {
                log_Err("Datatype size does not match array length, modulus is wrong");
                initialize(SVI_E_DLEN);
                return;
            }
            else {
                entryCount = arrLength / sizeof(C);
            }

            SAFE_DELETE(this->pArr);

            this->pArr = new C[entryCount];
            memset(pArr, 0, this->arrLength);
            this->valueAddr = valueAddr;
            setInitialized(true);
        }
        else
        {
            setInitialized(false);
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << "Datatype " << datatype
                    << " is not a an BLK type such as SVI_F_STRING or SVI_F_BLK";
            throw SviException(ss.str());
        }
    }

    void updateInternalValue(UINT32 value)
    {
        memcpy(pArr, &value, 4);
    }

    void updateInternalValue(UINT8 *pBuf, UINT32 length)
    {
        memset(pArr, 0, this->arrLength); //In case string is shorter

        if (length <= this->arrLength)
        {
            memcpy(pArr, pBuf, length);
        }
        else
        {
            memcpy(pArr, pBuf, arrLength);
        }
    }

    UINT32 getValueAddress()
    {
        return (UINT32) this->pArr;
    }

    ~SviBlkItem()
    {
        SAFE_DELETE(pArr);
    }

};

#endif /* BEFC_SVI_SVIBLKITEM_HPP_ */
