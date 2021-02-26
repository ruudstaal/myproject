/**
 ********************************************************************************
 * @file     SviVirtualExportDescriptor.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviVirtualExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIVIRTUALEXPORTDESCRIPTOR_HPP_
#define SVIVIRTUALEXPORTDESCRIPTOR_HPP_

#include "svi_e.h"
#include "SviExportDescriptor.hpp"

class VirtualSviHandler;

/**
 * @addtogroup SVI
 * @{
 */

class SviVirtualExportDescriptor: public SviExportDescriptor
{
public:

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviVirtualDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pHandler     The handler of the Virtual variable
     *******************************************************************************/
    SviVirtualExportDescriptor(std::string varName, UINT32 datatype, bool readable, bool writeable,
            VirtualSviHandler *pHandler);

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviVirtualDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @param[in]  id           Additional ID if needed, when read/write functions are called.
     * @param[in]  pParameter   Additional parameter if needed, when read/write functions are called
     *******************************************************************************/
    SviVirtualExportDescriptor(std::string varName, UINT32 datatype, bool readable, bool writeable,
            VirtualSviHandler *pHandler, UINT32 id, void *pParameter);

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviVirtualDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *             This function is for exporting arrays - Hence the dataLength argument
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  dataLength   The size of the array in bytes
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @throws     SviException If pointer is NULL
     *******************************************************************************/
    SviVirtualExportDescriptor(std::string varName, UINT32 datatype, UINT32 dataLength,
            bool readable, bool writeable, VirtualSviHandler *pHandler);

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviVirtualDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  dataLength   The size of the array in bytes
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pHandler     The handler of the Virtual variable
     * @param[in]  id           Additional ID if needed, when read/write functions are called.
     * @param[in]  pParameter   Additional parameter if needed, when read/write functions are called
     *******************************************************************************/
    SviVirtualExportDescriptor(std::string varName, UINT32 datatype, UINT32 dataLength,
            bool readable, bool writeable, VirtualSviHandler *pHandler, UINT32 id,
            void *pParameter);

    /**
     ********************************************************************************
     * @brief      Sets the hidden property of an SVI export
     *
     *******************************************************************************/
    void setHidden(void)
    {
        mode |= SVI_HM_NOPVINF;
    }

    /**
     ********************************************************************************
     * @brief      Gets the mode for the SVI export
     *
     * @retval     The mode for the SVI export
     *******************************************************************************/
    UINT32 getMode()
    {
        return(mode);
    }

    /**
     ********************************************************************************
     * @brief      This functions does the actual register for the SVI variable.
     * @param[in]  pServer      The pointer to the SviServer which should register the variable
     *******************************************************************************/
    void doRegister(SviServer *pServer);

    /**
     ********************************************************************************
     * @brief      Gets the virtual handler for the descriptor.
     * @retval     VirtualSviHandler*   Pointer to the handler
     *******************************************************************************/
    VirtualSviHandler* getVirtualHandler()
    {
        return pHandler;
    }

    /**
     ********************************************************************************
     * @brief      Gets the id for the descriptor
     * @retval     UINT32   The id
     *******************************************************************************/
    UINT32 getId()
    {
        return this->id;
    }

    /**
     ********************************************************************************
     * @brief      Sets the id for the descriptor
     * @param[in]  id   The id
     *******************************************************************************/
    void setId(UINT32 id)
    {
        this->id = id;
    }

    /**
     ********************************************************************************
     * @brief      Gets the parameter of the descriptor
     * @retval     VOID*    A pointer to the parameter
     *******************************************************************************/
    void* getParameter()
    {
        return this->pParameter;
    }

    /**
     ********************************************************************************
     * @brief      Sets a parameter on the descriptor
     * @param[in]  pParameter   The pointer to the parameter, which should be included
     *******************************************************************************/
    void setParameter(void *pParameter)
    {
        this->pParameter = pParameter;
    }

    /**
     ********************************************************************************
     * @brief      Destructs this SviVirtualExportDescriptor
     *******************************************************************************/
    ~SviVirtualExportDescriptor();
private:
    VirtualSviHandler *pHandler;
    void *pParameter;
    UINT32 id;
    UINT32 mode;

};
/** @} */

#endif  /*SVIVIRTUALEXPORTDESCRIPTOR_HPP_*/
