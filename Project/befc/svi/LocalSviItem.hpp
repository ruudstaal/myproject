/*
 * LocalSviItem.hpp
 *
 *  Created on: Jan 31, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_LOCALSVIITEM_HPP_
#define BEFC_SVI_LOCALSVIITEM_HPP_

#include <BEFCTypes.hpp>
#include <mcpp.hpp>
#include <mtypes.h>
#include <SviItem.hpp>
#include <SviSystem.hpp>
#include <svi.h>
#include <types/vxTypesOld.h>
#include <ValueFactory.hpp>
#include <string>

class LocalSviItem: public SviItem
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviItem for arrays
     *
     * @param[in]  moduleName  The name of the module
     * @param[in]  varName     The name of the variable (without module prefix)
     * @param[in]  datatype    The datatype of the variable
     * @param[in]  datalength  The length of the data/array
     *******************************************************************************/
    LocalSviItem(std::string moduleName, std::string varName, UINT32 datatype, UINT32 datalength);

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviItem for simple values
     *             (this also includes UINT64, SINT64, REAL64)
     *
     * @param[in]  moduleName  The name of the module
     * @param[in]  varName     The name of the variable (without module prefix)
     * @param[in]  datatype    The datatype of the variable
     *******************************************************************************/
    LocalSviItem(std::string moduleName, std::string varName, UINT32 datatype);

    /**
     ********************************************************************************
     * @brief      Sets the implementation of the SviSystem
     *
     * @param[in]  sviSystem   Pointer to the SviSystem
     *******************************************************************************/
    void setSviSystem(SviSystem* sviSystem)
    {
        if (pSviSystem != NULL)
        {
            SAFE_DELETE(pSviSystem);
        }
        pSviSystem = sviSystem;
    }

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
    SviValue* getValue(); //Gets the actual value

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  pValue   The new value
     *******************************************************************************/
    VOID setValue(SviValue *pValue);

    /**
     ********************************************************************************
     * @brief      Operator overload for comparing SviItems
     *
     * @retval     True if other has same moduleName and varName
     *******************************************************************************/
    bool operator==(const LocalSviItem &other) const;

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
    bool isArrayItem()
    {
        return isArray;
    }

    /**
     ********************************************************************************
     * @brief      Gets the library pointer. Only set for local svi variables.
     *
     * @retval     The library pointer
     *******************************************************************************/
    pLib getLib()
    {
        return int_lib;
    }

    /**
     ********************************************************************************
     * @brief      Destroys the LocalSviItem
     *******************************************************************************/
    ~LocalSviItem();

private:

    std::string moduleName;

    std::string varName;

    UINT32 datatype;

    pLib int_lib;

    SviValue *value;

    bool isArray;

    UINT32 datalength;

    SVI_ADDR valueAddr;

    SviSystem *pSviSystem;

    ValueFactory factory;

    /**
     ********************************************************************************
     * @brief      Initialize the SviItem
     *
     * @param[in]  ValueAddr        The SVI address
     * @param[in]  Format           The format retrieved from SVI
     * @throws     SviException     If the configured SviItem does not match the SVI Layer.
     *******************************************************************************/
    void initialize(SVI_ADDR ValueAddr, UINT32 Format);

    /**
     ********************************************************************************
     * @brief      Helper function to initialize the item after it was created
     *
     * @param[in]  moduleName  The name of the module
     * @param[in]  varName     The name of the variable (without module prefix)
     * @param[in]  datatype    The datatype of the variable
     * @param[in]  lib         The pointer to the module
     *******************************************************************************/
    VOID initInternal(std::string moduleName, std::string varName, UINT32 datatype, pLib lib);

    /**
     ********************************************************************************
     * @brief      Initializes the SviItem
     *
     * @param[in]  force     Forces the update. Otherwise if already initialized, it just returns.
     *******************************************************************************/
    VOID initialize(bool force);

    /**
     ********************************************************************************
     * @brief      Helper function for evaluating result from SVI layer
     *
     * @throws     SviException     If something went wrong in SVI operation
     *******************************************************************************/
    void handleSviResult(SINT32 result);

    /**
     ********************************************************************************
     * @brief      Updates the internal value of the AbstractSviItem. This function is
     *             called for 32 bit values.
     *
     * @param[in]  value     Current value as 32bit unsigned integer
     *******************************************************************************/
    void updateInternalValue(UINT32 value);

    /**
     ********************************************************************************
     * @brief      Updates the internal value of the AbstractSviItem. This function is
     *             called for values larger than >32 bit or BLK / arrays
     *
     * @param[in]  pBuf     Pointer to the source value buffer
     * @param[in]  length   Size of the source buffer in bytes
     *******************************************************************************/
    void updateInternalValue(UINT8* pBuf, UINT32 length);

    /**
     ********************************************************************************
     * @brief      Returns the pointer to the internal value as UINT32
     *
     * @retval     An UINT32 representing the pointer to the internal value of the object
     *******************************************************************************/
    UINT32 getValueAddress();

    /**
     ********************************************************************************
     * @brief      Sets the current value
     *
     * @param[in]  pValue       The pointer to the new value
     * @param[in]  setDirty     Whether or not to set the AbstractSviItem dirty
     *******************************************************************************/
    VOID setValueInternal(SviValue *pValue, bool setDirty);
};
#endif /* BEFC_SVI_LOCALSVIITEM_HPP_ */
