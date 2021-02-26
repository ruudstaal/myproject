/**
 ********************************************************************************
 * @file     VirtualSviHandler.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of VirtualSviHandler
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef BEFC_SVI_VIRTUALSVIHANDLER_HPP_
#define BEFC_SVI_VIRTUALSVIHANDLER_HPP_

#include "SviVirtualExportDescriptor.hpp"
#include "svi_e.h"
class VirtualSviHandler
{

public:

    /**
     ********************************************************************************
     * @brief Read function for simple values (<= 4 bytes). This function will be
     * called when variable is read. Value should then be written to the pBuffer if
     * allowed - here session ID could be used for validation.
     *
     * @param[in]  pDesc        The descriptor for the exported variable
     * @param[in]  pBuffer      Pointer to the buffer, where data should be written to.
     * @param[in]  sessionID    Session id for the current user
     * @retval     SINT32       Returncode according to SVI_E_*
     *******************************************************************************/
    virtual SINT32 handleRead(SviVirtualExportDescriptor *pDesc, UINT32 *pBuffer, UINT32 sessionID)
    {
        return 0;
    }

    /**
     ********************************************************************************
     * @brief Read function for block values (> 4 bytes). This function will be
     * called when variable is read. Value should then be written to the pBuffer if
     * allowed - here session ID could be used for validation.
     *
     * @param[in]  pDesc        The descriptor for the exported variable
     * @param[in]  pBuffer      Pointer to the buffer, where data should be written to.
     * @param[in]  bufferLength Length of the buffer
     * @param[in]  sessionID    Session id for the current user
     * @retval     SINT32       Returncode according to SVI_E_*
     *******************************************************************************/
    virtual SINT32 handleBlkRead(SviVirtualExportDescriptor *pDesc, VOID *pBuffer,
            UINT32 bufferLength, UINT32 sessionID)
    {
        return 0;
    }

    /**
     ********************************************************************************
     * @brief Write function for all values. This function will be
     * called when variable is written to. The written value can be read from
     * Pbuffer if allowed - here session ID could be used for validation.
     *
     * @param[in]  pDesc        The descriptor for the exported variable
     * @param[in]  pBuffer      Pointer to the buffer, where data should be written to.
     * @param[in]  bufferLength Length of the buffer
     * @param[in]  sessionID    Session id for the current user
     * @retval     SINT32       Returncode according to SVI_E_*
     *******************************************************************************/
    virtual SINT32 handleWrite(SviVirtualExportDescriptor *pDesc, const VOID *pBuffer,
            UINT32 bufferLength, UINT32 sessionID)
    {
        return SVI_E_WRITE;
    }
protected:
    VirtualSviHandler()
    {
    }
    virtual ~VirtualSviHandler()
    {
    }
};

#endif /* BEFC_SVI_VIRTUALSVIHANDLER_HPP_ */
