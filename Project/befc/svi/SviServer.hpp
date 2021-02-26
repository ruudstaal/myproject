/**
 ********************************************************************************
 * @file     SviServer.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviServer
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef SVISERVER_HPP_
#define SVISERVER_HPP_

#include <svi_e.h>

#include <vector>

#include "BEModule.hpp"
#include "SmiRequest.hpp"
#include "SviExportHelper.hpp"

/**
 * @addtogroup SVI
 * @{
 */

class SviValueExportDescriptor;
class SviExportDescriptor;
class SviVirtualExportDescriptor;
class SviSystem;
class Lockable;

class SviServer
{
public:
    /**
     ********************************************************************************
     * @brief Constructor of SviServer.
     *
     * @param[in]  pModule Pointer to the application module
     *******************************************************************************/
    explicit SviServer(BEModule* pModule);

    /**
     ********************************************************************************
     * @brief Destructor of SviServer.
     *******************************************************************************/
    ~SviServer();

    void handleSmiMessage(SMI_MSG* pMsg);

    /**
     ********************************************************************************
     * @brief This makes the actual export to the SVI layer
     *
     * @param[in]  pList 	A pointer to a SviExportDescriptor list
     *******************************************************************************/
    void registerSviExportDescriptors(std::vector<SviExportDescriptor*>* pList);

private:
    BEModule* pModule;
    UINT32 handle;
    FUNCPTR pSviMsgHandler; /** Function svi_MsgHandler2 or svi_MsgHandler */
    std::vector<SmiRequest*>* pLocalSmiRequestList;

    SviSystem *pSviSystem;

    /**
     ********************************************************************************
     * @brief for calling the system software for registering SVI variables.
     * This  functions registers virtual SVI variables
     *
     * @param[in]  pDesc    Pointer to the SviVirtualExportDescriptor
     * @throws     SviException If system fails to register the SVI variable
     *******************************************************************************/
    void registerVirtualSvi(SviVirtualExportDescriptor *pDesc);

    /**
     ********************************************************************************
     * @brief for calling the system software for registering SVI variables.
     * This  functions registers "normal" SVI variables
     *
     * @param[in]  pDesc    Pointer to the SviValueExportDescriptor
     * @throws     SviException If system fails to register the SVI variable
     *******************************************************************************/
    void registerValueSvi(SviValueExportDescriptor *pDesc);

    /**
     ********************************************************************************
     * @brief for calling the system software for registering SVI variables.
     * This  functions registers "normal" SVI variables
     *
     * @param[in]  pDesc        Pointer to the SviValueExportDescriptor
     * @param[in]  pLockable    Pointer to the Lockable to handle the thread protection
     * @throws     SviException If system fails to register the SVI variable
     *******************************************************************************/
    void registerValueSvi(SviValueExportDescriptor *pDesc, Lockable *pLockable);


    friend class SviValueExportDescriptor;
    friend class SviVirtualExportDescriptor;
    friend class SviExportHelper;

    SviServer(const SviServer& that); /** no copy */
    SviServer& operator=(SviServer const&); /** no assign */
};
/** @} */

#endif  /*SVISERVER_HPP_*/
