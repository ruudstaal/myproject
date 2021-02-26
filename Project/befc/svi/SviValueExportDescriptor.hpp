/**
 ********************************************************************************
 * @file     SviValueExportDescriptor.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviValueExportDescriptor
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVIVALUEEXPORTDESCRIPTOR_HPP_
#define SVIVALUEEXPORTDESCRIPTOR_HPP_

#include "SviExportDescriptor.hpp"
#include "SviServer.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SviValueExportDescriptor: public SviExportDescriptor
{

public:
    /**
     ********************************************************************************
     * @brief      Creates an instance of SviValueDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *             Use SviVirtualVarDescriptor for virtual SVI.
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pAddr        The pointer to the actual value
     * @throws     SviException If pointer is NULL
     * @retval     N/A
     *******************************************************************************/
    SviValueExportDescriptor(std::string varName, UINT32 datatype, bool readable, bool writeable,
            UINT32 *pAddr);

    /**
     ********************************************************************************
     * @brief      Creates an instance of SviValueDescriptor. This is used for exporting
     *             variables to the SVI layer.
     *             This function is for exporting arrays. Hence the datalength argument
     *
     * @param[in]  varName      Name of the SVI variable
     * @param[in]  datatype     Datatype of the SVI variable
     * @param[in]  dataLength   The size of the array
     * @param[in]  readable     Whether or not SVI variable should be readable
     * @param[in]  writeable    Whether or not SVI variable should be writable
     * @param[in]  pAddr        The pointer to the actual value
     * @throws     SviException If pointer is NULL
     * @retval     N/A
     *******************************************************************************/
    SviValueExportDescriptor(std::string varName, UINT32 datatype, UINT32 dataLength, bool readable,
            bool writeable, UINT32 *pAddr);

    ~SviValueExportDescriptor()
    {

    }

    UINT32* getValueAddress()
    {
        return pAddr;
    }

    void setValueAddress(UINT32 *pAddress)
    {
        this->pAddr = pAddress;
    }

    REAL64 getMinValue()
    {
        return this->min;
    }

    void setMinValue(REAL64 min)
    {
        this->min = min;
        minMaxSet = true;
    }

    bool isMaxMinSet()
    {
        return minMaxSet;
    }

    REAL64 getMaxValue()
    {
        return this->max;
    }

    void setMaxValue(REAL64 max)
    {
        this->max = max;

        minMaxSet = true;
    }

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
        return (mode);
    }

    /**
     ********************************************************************************
     * @brief      This functions does the actual register for the SVI variable.
     *
     * @param[in]  pServer      The pointer to the SviServer which should register the variable
     * @throws     N/A
     * @retval     N/A
     *******************************************************************************/
    void doRegister(SviServer *pServer);

private:
    UINT32 *pAddr;

    REAL64 min;

    REAL64 max;

    bool minMaxSet;

    UINT32 mode;
};
/** @} */

#endif  /*SVIVALUEEXPORTDESCRIPTOR_HPP_*/
