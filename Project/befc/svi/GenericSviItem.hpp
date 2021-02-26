/*
 * GenericSviItem.hpp
 *
 *  Created on: Feb 20, 2019
 *      Author: madsen
 */

#ifndef BEFC_SVI_GENERICSVIITEM_HPP_
#define BEFC_SVI_GENERICSVIITEM_HPP_

#include "SviException.hpp"
#include "SviItemEventListener.hpp"

template<class T> class GenericSviItem: public AbstractSviItem
{
public:

    /**
     ********************************************************************************
     *
     * @brief      Creates an instance of the GenericSviItem for simple values
     *             (this also includes UINT64, SINT64, REAL64)
     *
     *
     * @param[in]  moduleName  The name of the module
     * @param[in]  varName     The name of the variable (without module prefix)
     *******************************************************************************/
    GenericSviItem<T>(std::string modulename, std::string varname) :
            moduleName(modulename), varName(varname), datatype(0), int_lib(NULL), datalength(0), value(
                    0), numTimeouts(0)
    {
    }

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value as Type specified in constructor
     * @throws a SviException if variable is not readable or not initialized
     *******************************************************************************/
    T getVal()
    {
        validateInitializedAndReadable();
        return value;
    }

    /**
     ********************************************************************************
     * @brief      Sets the value
     *
     * @param[in]  value   The new value
     * @throws a SviException if variable is not writeable or not initialized
     *******************************************************************************/
    void setVal(T value)
    {
        if (isInitialized())
        {
            if (isWriteable())
            {
                this->value = value;
                setDirty(true);
                return;
            }
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << " is not writable";
            throw SviException(ss.str());
        }
        std::stringstream ss;
        ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                << " is not initialized - cannot set values to it";
        throw SviException(ss.str());
    }

    /**
     ********************************************************************************
     * @brief      Overload of the == operator. If modulename and varname is the same,
     *             operator will return true.
     *
     *******************************************************************************/
    bool operator==(const GenericSviItem<T> &other) const
    {
        if (this->moduleName == other.moduleName && this->varName == other.varName)
        {
            return true;
        }
        return false;
    }

    /**
     ********************************************************************************
     * @brief      Overload of the == operator. Uses the equals operator of the template
     *             type
     *
     *******************************************************************************/
    bool operator==(const T &other) const
    {
        return value == other;
    }


    /**
     ********************************************************************************
     * @brief      Overload of the assignment operator.
     *
     *******************************************************************************/
    T& operator=(const T &value)
    {
        setVal(value);
        return this->value;
    }



    /**
     ********************************************************************************
     * @brief      Overload of the * operator.
     *
     *******************************************************************************/
    const T& operator *() const
    {
      return value;
    }

    /**
     ********************************************************************************
     * @brief      Overload of the * operator.
     *
     *******************************************************************************/
    T& operator *()
    {
      return value;
    }

    /**
     ********************************************************************************
     * @brief      Destroys the GenericSviItem
     *******************************************************************************/
    virtual ~GenericSviItem()
    {
    }

    /** Implemented from AbstractSviItem interface **/

    std::string getVarName(VOID)
    {
        return this->varName;
    }

    UINT32 getDatatype(VOID)
    {
        if (isInitialized())
        {
            return this->datatype;
        }
        else
        {
            throw SviException("Datatype is not available before SVI item has been initialized");
        }
    }

    UINT32 getDataLength()
    {
        return this->datalength;
    }

    pLib getLib()
    {
        return int_lib;
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
        return datalength > 4;
    }

    std::string getModuleName(VOID)
    {
        return this->moduleName;
    }

private:
    std::string moduleName;

    std::string varName;

    UINT32 datatype;

    pLib int_lib;

    UINT32 datalength;

    SVI_ADDR valueAddr;

    T value;

    UINT32 numTimeouts;

    /** Private functions**/

    UINT32 getValueAddress()
    {
        return (UINT32) &this->value;
    }

    void initInternal(SVI_ADDR valueAddr, UINT32 format)
    {

        //Seen from server perspective
        setWritable(format & SVI_F_IN);
        setReadable(format & SVI_F_OUT);

        datatype = (format & SVI_F_SUBTYPEMSK);

        if (datatype & SVI_F_BLK)
        {
            setInitialized(false);
            std::stringstream ss;
            ss << "SviItem " << this->moduleName.c_str() << "/" << this->varName.c_str()
                    << "Datatype " << datatype
                    << " is not a simple type - use functions for BLKs on SviGroup";
            throw SviException(ss.str());
        }

        this->datalength = (format >> 16);
        this->valueAddr = valueAddr;
        setInitialized(true);
        setQualityState(SviItemEventListener::GOOD);
    }

    void updateInternalValue(UINT32 value)
    {
        memcpy(&this->value, &value, 4);
    }

    void updateInternalValue(UINT8 *pBuf, UINT32 length)
    {
        if (length != this->datalength)
        {
            log_Wrn("Size of SVI item %s is %i, but read %i from SVI layer",
                    this->getVarName().c_str(), this->datalength, length);
        }

        if (length <= this->datalength)
        {
            memcpy(&this->value, pBuf, length);
        }
        else
        {
            memcpy(&this->value, pBuf, datalength);
        }
    }
};

#endif /* BEFC_SVI_GENERICSVIITEM_HPP_ */
