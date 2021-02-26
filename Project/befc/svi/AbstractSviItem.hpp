/*
 * AbstractSviItem.hpp
 *
 *  Created on: Mar 1, 2019
 *      Author: madsen
 */

#ifndef BEFC_SVI_ABSTRACTSVIITEM_HPP_
#define BEFC_SVI_ABSTRACTSVIITEM_HPP_

#include "log_e.h"
#include <string>
#include <svi_e.h>
#include "BEFCTypes.hpp"
#include "SviItemEventListener.hpp"
#include <vector>
#include <sstream>
#include "SviException.hpp"

class AbstractSviItem
{
    friend class SingleItemStrategyImpl;
    friend class ListReadStrategyImpl;
    friend class RemoteSviListReadStrategy;
    friend class RemoteSviWriteHelper;
    friend class RemoteSviReadStrategy;

public:

    static const UINT32 ALLOWED_NUM_TIMEOUTS = 2;

    /**
     ********************************************************************************
     * @brief      Creates an instance of the AbstractSviItem
     *
     *******************************************************************************/
    AbstractSviItem() :
            initialized(false), dirty(false), readable(false), writeable(false), errorCode(
                    SVI_E_OK), failed(false), quality(SviItemEventListener::INIT), numTimeouts(0)
    {
    }

    /**
     ********************************************************************************
     * @brief      Gets the module name
     *
     * @retval     The module name
     *******************************************************************************/
    virtual std::string getModuleName(VOID) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the variable name
     *
     * @retval     The variable name
     *******************************************************************************/
    virtual std::string getVarName(VOID) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the datatype
     *
     * @retval     The datatype of the SviItem
     *******************************************************************************/
    virtual UINT32 getDatatype(VOID) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the datalength
     *
     * @retval     The length of the data
     *******************************************************************************/
    virtual UINT32 getDataLength() = 0;

    /**
     ********************************************************************************
     * @brief      Initialize the SviItem
     *
     * @param[in]  ValueAddr        The SVI address
     * @param[in]  Format           The format retrieved from SVI
     * @throws     SviException     If the configured SviItem does not match the SVI Layer.
     *******************************************************************************/
    virtual void initialize(SVI_ADDR valueAddr, UINT32 format, pLib lib) = 0;

    /**
     ********************************************************************************
     * @brief      Initialize the SviItem by errorcode. If initialization fails, the
     *             item should be initialized accordingly
     *
     * @param[in]  errorCode        The SVI errorcode. In SVI_E_xxx syntax
     *******************************************************************************/
    virtual void initialize(SINT32 errorCode) = 0;

    /**
     ********************************************************************************
     * @brief      Gets the SVI address
     *
     * @retval     The SVI address
     *******************************************************************************/
    virtual SVI_ADDR getSviAddr(VOID) = 0;

    /**
     ********************************************************************************
     * @brief      Whether this item represents an array or not
     *
     * @retval     True if item contains array data, false if not.
     *******************************************************************************/
    virtual bool isArrayItem() = 0;

    /**
     ********************************************************************************
     * @brief      Gets the library pointer. Only set for local svi variables.
     *
     * @retval     The library pointer
     *******************************************************************************/
    virtual pLib getLib() = 0;

    /**
     ********************************************************************************
     * @brief      Returns wether the item is failed or not. Failure can be set during
     *             initialization or during the read/write process. Use getError() to
     *             get an indication of the failure.
     *
     * @retval     A boolean indicating if item is failed or not
     *******************************************************************************/
    bool isFailed()
    {
        return failed;
    }

    /**
     ********************************************************************************
     * @brief      Returns wether the item is dirty or not. Dirty state is normally set
     *             when the AbstractSviGroup should be notified to write the value to
     *             the SVI layer
     *
     * @retval     A boolean indicating if item is dirty or not
     *******************************************************************************/
    bool isDirty()
    {
        return dirty;
    }

    /**
     ********************************************************************************
     * @brief      Returns wether the item is readable or not. After initialiazation
     *             the readable state will be set accordingly to reflect the state of the
     *             SVI variable.
     *
     * @retval     A boolean indicating if item is readable or not
     *******************************************************************************/
    bool isReadable()
    {
        return readable;
    }

    /**
     ********************************************************************************
     * @brief      Returns wether the item is writeable or not. After initialiazation
     *             the writable state will be set accordingly to reflect the state of the
     *             SVI variable.
     *
     * @retval     A boolean indicating if item is writable or not
     *******************************************************************************/
    bool isWriteable()
    {
        return writeable;
    }

    /**
     ********************************************************************************
     * @brief      Returns wether the item is initialized or not. When item is initialized,
     *             the state will reflect the properties as the exported svi variable
     *
     * @retval     A boolean indicating if item is initialized or not
     *******************************************************************************/
    bool isInitialized()
    {
        return initialized;
    }

    /**
     ********************************************************************************
     * @brief      If the item fails during initializtion, reading or writing, the
     *             error code will be set. Use the isFailed() to check if the item
     *             is failed or not.
     *
     * @retval     A boolean indicating if item is initialized or not
     *******************************************************************************/
    SINT32 getError()
    {
        return errorCode;
    }

    /**
     ********************************************************************************
     * @brief      Adds a listener to the item, to get notifications about change of
     *             quality state or failed write
     *
     * @param[in]  pListener        The SviItemEventListener to be notified
     *******************************************************************************/
    void addItemEventListener(SviItemEventListener *pListener)
    {
        listeners.push_back(pListener);
    }

    /**
     ********************************************************************************
     * @brief      Resets the item to default and uninitialized state
     *
     *******************************************************************************/
    void reset();

    /**
     ********************************************************************************
     * @brief      Destroys the SviItem
     *******************************************************************************/
    virtual ~AbstractSviItem()
    {
    }

    /**
     ********************************************************************************
     * @brief      Gets the length for at specific datatype, like SVI_F_UINT32
     *
     * @param[in]  datatype         The datatype as SVI_F_XXX
     * @throws     SviException     If input datatype is BLK types or similar.
     *******************************************************************************/
    static UINT32 getDatatypeLength(UINT32 datatype);


protected:

    void notifyFailedWrite(SINT32 reason);

    void setQualityState(SviItemEventListener::DataQuality newQuality);

    void validateInitializedAndReadable();

    void handleErrorCode(SINT32 res);

    void setDirty(bool dirty)
    {
        this->dirty = dirty;
    }

    void setWritable(bool writable)
    {
        this->writeable = writable;
    }

    void setReadable(bool readable)
    {
        this->readable = readable;
    }

    void setError(SINT32 errorCode)
    {
        this->errorCode = errorCode;
    }

    void setInitialized(bool initialized)
    {
        this->initialized = initialized;
    }

    void setFailed(bool failed)
    {
        this->failed = failed;
    }

    void setQuality(SviItemEventListener::DataQuality quality)
    {
        this->quality = quality;
    }

private:

    bool initialized;

    bool dirty;

    bool readable;

    bool writeable;

    SINT32 errorCode;

    bool failed;

    SviItemEventListener::DataQuality quality;

    std::vector<SviItemEventListener*> listeners;

    UINT32 numTimeouts;

    /**
     ********************************************************************************
     * @brief      Updates the internal value of the AbstractSviItem. This function is
     *             called for 32 bit values.
     *
     * @param[in]  value     Current value as 32bit unsigned integer
     *******************************************************************************/
    virtual void updateInternalValue(UINT32 value) = 0;

    /**
     ********************************************************************************
     * @brief      Updates the internal value of the AbstractSviItem. This function is
     *             called for values larger than >32 bit or BLK / arrays
     *
     * @param[in]  pBuf     Pointer to the source value buffer
     * @param[in]  length   Size of the source buffer in bytes
     *******************************************************************************/
    virtual void updateInternalValue(UINT8* pBuf, UINT32 length) = 0;

    /**
     ********************************************************************************
     * @brief      Returns the pointer to the internal value as UINT32
     *
     * @retval     An UINT32 representing the pointer to the internal value of the object
     *******************************************************************************/
    virtual UINT32 getValueAddress() = 0;
};

#endif /* BEFC_SVI_ABSTRACTSVIITEM_HPP_ */
