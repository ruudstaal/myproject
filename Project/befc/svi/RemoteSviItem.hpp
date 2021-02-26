/*
 * RemoteSviItem.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_REMOTESVIITEM_HPP_
#define BEFC_SVI_REMOTESVIITEM_HPP_

#include <vector>
#include <BEFCTypes.hpp>
#include <mtypes.h>
#include <svi.h>
#include <SviItem.hpp>
#include <types/vxTypesOld.h>
#include <string>
#include "RemoteSviItemEventListener.hpp"
#include "ValueFactory.hpp"

class RemoteSviItem: public SviItem
{
public:

    friend class RemoteSviGroup;
    friend class RemoteSviWriteHelper;
    friend class RemoteSviReadStrategy;
    friend class RemoteSviListReadStrategy;

    static const UINT32 ALLOWED_NUM_TIMEOUTS = 5;

    /**
     ********************************************************************************
     * @brief      Creates a new instance of the RemoteSviItem to simple values < 32 bits,
     *             although including SVI_F_REAL64, SVI_F_UINT64 and SVI_F_SINT64
     *
     * @param[in]  moduleName        The name of the module, where the svi is exposed. Ex. "RES"
     * @param[in]  varName           The name of the variable. Ex. "Time/Time_ms"
     * @param[in]  datatype          The datatype of the variable. Ex. SVI_F_UINT32
     *******************************************************************************/
    RemoteSviItem(std::string moduleName, std::string varName, UINT32 datatype);

    /**
     ********************************************************************************
     * @brief      Creates a new instance of the RemoteSviItem to simple values > 32 bits.
     *             This includes arrays.
     *
     * @param[in]  moduleName        The name of the module, where the svi is exposed. Ex. "RES"
     * @param[in]  varName           The name of the variable. Ex. "Time/Time_ms"
     * @param[in]  datatype          The datatype of the variable. Ex. SVI_F_UINT32
     * @param[in]  datalength        The length of the array
     *******************************************************************************/
    RemoteSviItem(std::string moduleName, std::string varName, UINT32 datatype, UINT32 datalength);

    /**
     ********************************************************************************
     * @brief      Reads the value from SVI and updates the object
     *
     * @retval     The current SviValue
     *******************************************************************************/
    SviValue* readValue();

    /**
     ********************************************************************************
     * @brief      Write the current value to SVI
     *
     * @throws     SviException     If something goes wrong while writing
     *******************************************************************************/
    VOID writeValue();

    /**
     ********************************************************************************
     * @brief      Gets the module name
     *
     * @retval     The module name
     *******************************************************************************/
    std::string getModuleName(VOID);

    /**
     ********************************************************************************
     * @brief      Gets the variable name
     *
     * @retval     The variable name
     *******************************************************************************/
    std::string getVarName(VOID);

    /**
     ********************************************************************************
     * @brief      Gets the datatype
     *
     * @retval     The datatype of the SviItem
     *******************************************************************************/
    UINT32 getDatatype(VOID);

    /**
     ********************************************************************************
     * @brief      Gets the datalength
     *
     * @retval     The length of the data
     *******************************************************************************/
    UINT32 getDataLength();

    /**
     ********************************************************************************
     * @brief      Gets the current value
     *
     * @retval     The current value as SviValue type
     *******************************************************************************/
    SviValue* getValue();

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  pValue   The new value
     *******************************************************************************/
    VOID setValue(SviValue *pValue);

    /**
     ********************************************************************************
     * @brief      Gets the library pointer. Only set for local svi variables.
     *
     * @retval     The library pointer
     *******************************************************************************/
    pLib getLib()
    {
        return NULL;
    }

    /** Functions called by the group when initializing */

    /**
     ********************************************************************************
     * @brief      Initialize the SviItem
     *
     * @param[in]  ValueAddr        The SVI address
     * @param[in]  Format           The format retrieved from SVI
     * @throws     SviException     If the configured SviItem does not match the SVI Layer.
     *******************************************************************************/
    void initialize(SVI_ADDR valueAddr, UINT32 format, pLib lib);

    /**
     ********************************************************************************
     * @brief      Initialize the SviItem by errorcode. If initialization fails, the
     *             item should be initialized accordingly
     *
     * @param[in]  errorCode        The SVI errorcode. In SVI_E_xxx syntax
     *******************************************************************************/
    void initialize(SINT32 errorCode);

    /**
     ********************************************************************************
     * @brief      Gets the SVI address
     *
     * @retval     The SVI address
     *******************************************************************************/
    SVI_ADDR getSviAddr(VOID);

    /**
     ********************************************************************************
     * @brief      Whether this item represents an array or not
     *
     * @retval     True if item contains array data, false if not.
     *******************************************************************************/
    bool isArrayItem();

    /**
     ********************************************************************************
     * @brief      Destructs the RemoteSviItem
     *******************************************************************************/
    ~RemoteSviItem();

private:

    std::string moduleName;

    std::string varName;

    UINT32 datatype;

    SviValue *value;

    bool isArray;

    UINT32 datalength;

    SVI_ADDR valueAddr;

    UINT32 numTimeouts;

    ValueFactory valFac;

    void updateInternalValue(UINT32 value);

    void updateInternalValue(UINT8* pBuf, UINT32 length);

    UINT32 getValueAddress()
    {
        return value->getValueAddress();
    }

    VOID initInternal(std::string moduleName, std::string varName, UINT32 datatype);

    VOID initializeInternal(SVI_ADDR valueAddr, UINT32 format);

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  pValue       The pointer to the new value
     * @param[in]  setDirty     Whether or not to set the AbstractSviItem dirty
     *******************************************************************************/
    VOID setValueInternal(SviValue *pValue, bool ignoreIfDirty);
};

#endif /* BEFC_SVI_REMOTESVIITEM_HPP_ */
