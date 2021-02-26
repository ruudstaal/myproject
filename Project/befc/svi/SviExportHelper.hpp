/**
 ********************************************************************************
 * @file     SviExportHelper.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviExportHelper
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIEXPORTHELPER_HPP_
#define SVIEXPORTHELPER_HPP_

#include <string>
#include <vector>

#include "VirtualSviHandler.hpp"
#include "../atomic/ArrayWrapper.hpp"
#include "../atomic/ValueWrapper.hpp"
#include "BETask.hpp"
#include "SviException.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SviServer;

class SviExportHelper
{
public:
    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a value
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pVal         The pointer to value
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, UINT32 *pVal);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a value, for a hidden SVI
     *             variable
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pVal         The pointer to value
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportHiddenValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, UINT32 *pVal);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a value with min/max values
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pVal         The pointer to value
     * @param[in]  min          The minimum value
     * @param[in]  max          The maximum value
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, UINT32 *pVal, REAL64 min, REAL64 max);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a value with min/max values,
     *             for a hidden SVI variable
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pVal         The pointer to value
     * @param[in]  min          The minimum value
     * @param[in]  max          The maximum value
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportHiddenValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, UINT32 *pVal, REAL64 min, REAL64 max);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a virtual value
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportVirtualValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, VirtualSviHandler *pHandler);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a virtual value, for a hidden
     *             SVI variable
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportHiddenVirtualValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, VirtualSviHandler *pHandler);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a virtual value
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @param[in]  id           Id for identification of the descriptor
     * @param[in]  pParameter   Additional parameter for the descriptor
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportVirtualValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, VirtualSviHandler *pHandler, UINT32 id, void* pParameter);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a virtual value, for a hidden
     *             SVI variable
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @param[in]  id           Id for identification of the descriptor
     * @param[in]  pParameter   Additional parameter for the descriptor
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportHiddenVirtualValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, VirtualSviHandler *pHandler, UINT32 id, void* pParameter);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a virtual block value (> 4 bytes)
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype (see BeTypes.h)
     * @param[in]  dataLength   Length of the array in bytes
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @param[in]  id           Id for identification of the descriptor
     * @param[in]  pParameter   Additional parameter for the descriptor
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportVirtualArray(std::string name, UINT32 datatype, UINT32 dataLength,
            bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id,
            void* pParameter);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a string. String type is automatically
     *             adjusted in memory size, but a fixed length is needed for SVI.
     *
     * @param[in]  name       The SVI variable name
     * @param[in]  pString    The pointer to the string
     * @param[in]  length     The length of the string
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportString(std::string name, UINT32 *pString, UINT32 length);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a string. String type is automatically
     *             adjusted in memory size, but a fixed length is needed for SVI, for a hidden
     *             SVI variable.
     *
     * @param[in]  name       The SVI variable name
     * @param[in]  pString    The pointer to the string
     * @param[in]  length     The length of the string
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportHiddenString(std::string name, UINT32 *pString, UINT32 length);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for an array of values.
     *             Default values are readable, but not writeable.
     *
     * @param[in]  name             The SVI variable name
     * @param[in]  aArray           The pointer to the array
     * @param[in]  datatype         Datatype of the elements
     * @param[in]  size             Size of the array (use sizeof())
     * @param[in]  exportIndividual If elements should be exported as single SVI variables.
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    std::vector<SviExportDescriptor*> exportArray(std::string name, UINT32 *aArray,
            UINT32 datatype, UINT32 size, bool exportIndividual);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for an array of values
     *
     * @param[in]  name             The SVI variable name
     * @param[in]  aArray           The pointer to the array
     * @param[in]  datatype         Datatype of the elements
     * @param[in]  size             Size of the array (use sizeof())
     * @param[in]  readable         If variable should be readable
     * @param[in]  writeable        If variable should be writeable
     * @param[in]  exportIndividual If elements should be exported as single SVI variables.
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    std::vector<SviExportDescriptor*> exportArray(std::string name, UINT32 *aArray,
            UINT32 datatype, UINT32 size, bool readable, bool writeable, bool exportIndividual);

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a string array
     *
     * @param[in]  name             The SVI variable name
     * @param[in]  aArray           The pointer to the array
     * @param[in]  elementLength    Number of array elements
     * @param[in]  stringLength     Length of strings in array
     * @param[in]  exportIndividual If elements should be exported as single SVI variables.
     * @param[in]  readable         If variable should be readable
     * @param[in]  writeable        If variable should be writeable
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    std::vector<SviExportDescriptor*> exportStringArray(std::string name, UINT32 *aArray,
            UINT32 elementLength, UINT32 stringLength, bool exportIndividual, bool readable,
            bool writeable);


    /**
     * The section below contains the functions needed to make read/write actions, for exported values, atomic.
     *
     * Keep in mind, that only values above 32 bit needs protection. Read/Write actions for <= 32 bit values are
     * handled atomically by the OS.
     *
     * Since M-Base 4.30
     *
     */

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a value
     *
     * @param[in]  name         The SVI variable name
     * @param[in]  datatype     The datatype
     * @param[in]  readable     If variable should be readable
     * @param[in]  writeable    If variable should be writeable
     * @param[in]  pVal         The pointer to value
     * @param[in]  pLockable    Pointer to the handler which locks/unlocks before read/write actions
     *
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    SviExportDescriptor* exportValue(std::string name, UINT32 datatype, bool readable,
            bool writeable, UINT32 *pVal, Lockable *pLockable);


    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for an array of values
     *
     * @param[in]  name             The SVI variable name
     * @param[in]  aArray           The pointer to the array
     * @param[in]  datatype         Datatype of the elements
     * @param[in]  size             Size of the array (use sizeof())
     * @param[in]  readable         If variable should be readable
     * @param[in]  writeable        If variable should be writeable
     * @param[in]  exportIndividual If elements should be exported as single SVI variables.
     * @param[in]  pLockable        Pointer to the handler which locks/unlocks before read/write actions
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    std::vector<SviExportDescriptor*> exportArray(std::string name, UINT32 *aArray, UINT32 datatype,
            UINT32 size, bool readable, bool writeable, bool exportIndividual, Lockable *pLockable);


    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for a simple value. Will be protected by locking
     *             mechanisms to make value threadsafe
     *
     * @param[in]  name             The SVI variable name
     * @param[in]  readable         If variable should be readable
     * @param[in]  writeable        If variable should be writeable
     * @param[in]  pTask            The Task handle where for the export of the variable
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    template<class C> ValueWrapper<C>* exportAtomicValue(std::string name, bool readable, bool writeable, BETask *pTask)
    {
        UINT32 datatype = AtomicWrapper::getDatatype(typeid(C));
        ValueWrapper<C> *pRes = new ValueWrapper<C>(0);
        if(pTask != NULL) {
            pTask->exportToSvi(exportValue(name, datatype, readable, writeable, pRes->getValueAddress(), pRes));
        }
        return pRes;
    }

    /**
     ********************************************************************************
     * @brief      Creates an SviExportDescriptor for an array of values protected by locking
     *             mechanisms to make value threadsafe
     *
     * @param[in]  name                 The SVI variable name
     * @param[in]  size                 Size of the array in bytes.
     * @param[in]  readable             If variable should be readable
     * @param[in]  writeable            If variable should be writeable
     * @param[in]  exportIndividual     If elements in array should be exported as single SVI variables.
     * @param[in]  pTask                The Task handle where for the export of the variable
     * @retval     The SviExportDescriptor
     *******************************************************************************/
    template <class C> ArrayWrapper<C>* exportAtomicArray(std::string name, UINT32 size, bool readable, bool writeable, bool exportIndividual, BETask *pTask) {
        UINT32 datatype = AtomicWrapper::getDatatype(typeid(C));
        UINT32 dataTypeLength = SviExportDescriptor::getDataLength(datatype);
        if((size % dataTypeLength) != 0) {
            throw SviException("Array size declaration and datatype length does not match");
        }

        ArrayWrapper<C> *pRes = new ArrayWrapper<C>(size / dataTypeLength);
            if (pTask != NULL)
            {
                std::vector<SviExportDescriptor*> arr = exportArray(name, pRes->getValueAddress(), datatype, size, readable, writeable, exportIndividual);

                for (std::vector<SviExportDescriptor*>::iterator ite = arr.begin(); ite != arr.end(); ite++)
                {
                    if((*ite)->isArray()){
                        (*ite)->setLockable(pRes);
                    }
                }

                pTask->exportToSvi(arr);
            }
            return pRes;
    }

    SviExportHelper()
    {
    }


};
/** @} */

#endif  /*SVIEXPORTHELPER_HPP_*/
