/**
 ********************************************************************************
 * @file     SviServer.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviServer
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <sysSymTbl.h>

#include <iostream>
#include "SviServer.hpp"
#include "SVI_Proc.hpp"
#include "SmiHandler.hpp"
#include "SviValueExportDescriptor.hpp"
#include "SviVirtualExportDescriptor.hpp"
#include "SviException.hpp"
#include "M1SviSystem.hpp"
#include "atomic/Lockable.hpp"

SINT32 lock(SVI_VAR *pVar, Lockable *pLockable)
{
    if (pLockable->lock() < 0)
    {
        return SVI_E_FAILED; //No proper return code for this
    }
    return 0;
}

SINT32 unlock(SVI_VAR *pVar, Lockable *pLockable)
{
    if (pLockable->unlock() < 0)
    {
        return SVI_E_FAILED;
    }
    return 0;
}


/**
 ********************************************************************************
 * @brief Callback function for the Virtual SVI
 * Read simple datatypes
 *
 * @param[in]  pDesc1 		Parameter 1 for reading
 * @param[in]  pDesc2		Parameter 2 for reading
 * @param[in]  pBuff 		Pointer to the data
 * @param[in]  SvFlag 		See BE reference manual
 * @param[in]  sessionId 	See BE reference manual
 * @retval     SINT32		Returncode for the SVI layer
 *******************************************************************************/
SINT32 virtVar_ReadBasic(SviVirtualExportDescriptor* pDesc1, SviVirtualExportDescriptor* pDesc2,
        UINT32 *pBuff, BOOL8 SvFlag, UINT32 sessionId)
{
    if (pDesc1->isReadable())
    {
        return pDesc1->getVirtualHandler()->handleRead(pDesc1, pBuff, sessionId);
    }
    else
    {
        return SVI_E_READ;
    }
}

/**
 ********************************************************************************
 * @brief Callback function for the Virtual SVI
 * Read block datatypes (arrays, structures)
 *
 * @param[in]  pDesc1       Parameter 1 for reading
 * @param[in]  pDesc2       Parameter 2 for reading
 * @param[in]  pBuff        Pointer to the data
 * @param[in]  pBuffLen     Length of the buffer
 * @param[in]  SvFlag       See BE reference manual
 * @param[in]  sessionId    See BE reference manual
 * @retval     SINT32       Return length of bytes in buffer or SVI_E_*
 *******************************************************************************/
SINT32 virtVar_ReadBlk(SviVirtualExportDescriptor* pDesc1, SviVirtualExportDescriptor* pDesc2,
        UINT8* pBuff, UINT32* pBuffLen, BOOL8 SvFlag, UINT32 sessionId)
{
    if (pDesc1->isReadable())
    {
        if (pDesc1->getDataLength() <= *pBuffLen)
        {
            SINT32 ret = SVI_E_OK;

            ret = pDesc1->getVirtualHandler()->handleBlkRead(pDesc1, pBuff, *pBuffLen, sessionId);
            if(ret > SVI_E_OK)
            {
                *pBuffLen = ret;
                return SVI_E_OK;
            }
            else
            {
                return ret;
            }
        }
        else
        {
            log_Wrn(
                    "Virtual variable read buffer for %s not big enough. Datalength: %d. Buffer size: %d",
                    pDesc1->getVarName().c_str(), pDesc1->getDataLength(), pBuffLen);
            return SVI_E_READ;
        }
    }
    else
    {
        return SVI_E_READ;
    }

}

/**
 ********************************************************************************
 * @brief Callback function for the Virtual SVI
 *	Writing value
 *
 * @param[in]  pDesc1 		Parameter 1 for writing
 * @param[in]  pDesc2		Parameter 2 for writing
 * @param[in]  value 		New value
 * @retval     SINT32		Returncode for the SVI layer
 *******************************************************************************/
SINT32 virtVar_WriteBasic(SviVirtualExportDescriptor* pDesc1, SviVirtualExportDescriptor* pDesc2,
        SINT32 value)
{
    /** This is the prototype for simple write. This is not used due to the
     * SVI_HM_UNIFIED_WRITE flag given when configuring the virtual variable.
     * Included if needed at some point.
     */
     if (pDesc1->isWriteable()) {
     return SVI_E_OK;
     }
     return SVI_E_WRITE;
     }

 /**
 ********************************************************************************
 * @brief Callback function for the Virtual SVI
 *	Writing block value.
 *
 * @param[in]  pDesc1 		Parameter 1 for writing
 * @param[in]  pDesc2		Parameter 2 for writing
 * @param[in]  pBuff 		Pointer to the data
 * @param[in]  buffLen 		Length of the buffer
 * @param[in]  SvFlag       Service variable flag
 * @param[in]  SessionId    Session ID for the user, to identify user rights
 * @retval     SINT32		Returncode for the SVI layer
 *******************************************************************************/
SINT32 virtVar_WriteBlk(SviVirtualExportDescriptor* pDesc1,
        SviVirtualExportDescriptor* pDesc2, void* pBuff, UINT32 buffLen, BOOL32 SvFlag, UINT32 SessionId)
{
    try
    {
        return pDesc1->getVirtualHandler()->handleWrite(pDesc1, pBuff, buffLen, SessionId);
    }
    catch (SviException const& e)
    {
        log_Err("Caught exception when handling virtual SVI. %s", e.what());
    }
    return SVI_E_WRITE;

}

SviServer::SviServer(BEModule * pModule) :
   pModule(pModule), pSviSystem(new M1SviSystem())
{
    SYM_TYPE symType;
    SINT32 ret = 0;
    pSviMsgHandler = NULL;
    char handlerName[] = "_svi_MsgHandler2";
    ret = symFindByName(sysSymTbl, handlerName, (char**) &pSviMsgHandler, &symType);
    if (ret == ERROR)
    {
        char handlerName[] = "_svi_MsgHandler";
        warn("svi_MsgHandler2! svi_MsgHandler is used!");
        ret = symFindByName(sysSymTbl, handlerName, (char**) &pSviMsgHandler, &symType);
    }

    /** Initialize svi handler in VxWorks */
    handle = pSviSystem->Init((char*) pModule->getAppName().c_str(), SVI_HT_DEF, NULL);    // Switched to 256K vairables
    if (!handle)
    {
        throw SviException("Could not initialize svi handler");
    }

    /** create the smi procedure list */
    pLocalSmiRequestList = new std::vector<SmiRequest*>();

    /** Add handling of incoming SVI request */
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETSERVINF));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETVAL));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_SETVAL));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETVALLST));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_SETVALLST));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETBLK));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_SETBLK));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETADDR));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETXADDR));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETPVINF));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_GETMULTIBLK));
    pLocalSmiRequestList->push_back(new Svi_Proc(this, SVI_PROC_SETMULTIBLK));

    this->pModule->getSmiHandler()->registerSmiRequest(pLocalSmiRequestList);

    if (pModule->getDebugMode() & APP_DBG_INFO2)
    {
        info("SVI server initialized")
    }
}

SviServer::~SviServer()
{
    /** unregister the svi server smi calls from the application module */
    pModule->getSmiHandler()->unregisterSmiRequest(pLocalSmiRequestList);

    /** delete all svi server smi calls */
    for (std::vector<SmiRequest*>::iterator itSmiRequest = pLocalSmiRequestList->begin();
            itSmiRequest != pLocalSmiRequestList->end(); ++itSmiRequest)
    {
        SAFE_DELETE(*itSmiRequest);
    }

    /** clear the smi procedure list and delete the list */
    pLocalSmiRequestList->clear();
    SAFE_DELETE(pLocalSmiRequestList);

    /** first remove the handle to prevent an exception 14 while accessing after delete */
    SINT32 deinitRes = pSviSystem->DeInit(handle);

    SAFE_DELETE(pSviSystem);

    if(deinitRes < 0 ) {
        error("Could not DeInit SVI");
    }

    /** clear the variable list the variables will be deleted by the task Svi
     *  server variables not yet implemented
     */

    if (pModule->getDebugMode() & APP_DBG_INFO2)
    {
        info("SVI server deleted")
    }


}

void SviServer::handleSmiMessage(SMI_MSG* pMsg)
{
    pSviMsgHandler(handle, pMsg, pModule->getSmiID(),
            pModule->getSmiHandler()->getUserSessionId());
}

void SviServer::registerSviExportDescriptors(std::vector<SviExportDescriptor*>* pList)
{
    std::vector<SviExportDescriptor*>::iterator ite;
    try
    {
        for (ite = pList->begin(); ite != pList->end(); ++ite)
        {
            (*ite)->doRegister(this);
        }
    }
    catch (SviException const& e)
    {
        error("Caught SVI exception: " << e.what());
    }
}

void SviServer::registerVirtualSvi(SviVirtualExportDescriptor *pDesc)
{

    /** First read/write parameter is the descriptor itself */
    UINT32 rdPar1 = (UINT32) pDesc;
    UINT32 wrPar1 = (UINT32) pDesc;

    /** Second read/write parameter not used */
    UINT32 rdPar2 = (UINT32) pDesc;
    UINT32 wrPar2 = (UINT32) pDesc;

    /** create the function pointer */
    SINT32 ret;


    ret = pSviSystem->AddVirtVar(handle, (char*) pDesc->getVarName().c_str(),
                SviExportDescriptor::getFormat(pDesc), pDesc->getDataLength(),
                SVI_HM_UNIFIED_WRITE | pDesc->getMode(), rdPar1, rdPar2, wrPar1, wrPar2,
                pDesc->isArray() ? (SVI_FUNC_READ)&virtVar_ReadBlk : (SVI_FUNC_READ)&virtVar_ReadBasic,
                (SVI_FUNC_WRITE)&virtVar_WriteBlk);

    if (ret == SVI_E_OK)
    {
        return;
    }
    std::cout << "throwing svi exception" << std::endl;
    throw SviException("Could not export Virtual SVI Descriptor");
}

void SviServer::registerValueSvi(SviValueExportDescriptor *pDesc)
{

    SINT32 ret = 0;

    if(pDesc->getLockable() != NULL){

        /** Add the global var with lock/unlock handling */
          ret = pSviSystem->AddGlobVar(this->handle, (char*) pDesc->getVarName().c_str(),
                  SviExportDescriptor::getFormat(pDesc), pDesc->getDataLength(), pDesc->getValueAddress(),
                  pDesc->getMode(), (UINT32)pDesc->getLockable(), (SVI_FUNC_LOCK)&lock, (SVI_FUNC_UNLOCK)&unlock);
    }
    else{
        /** Add the global var WITHOUT lock/unlock handling*/
        ret = pSviSystem->AddGlobVar(this->handle, (char*) pDesc->getVarName().c_str(),
                SviExportDescriptor::getFormat(pDesc), pDesc->getDataLength(), pDesc->getValueAddress(),
                pDesc->getMode(), 0, NULL, NULL);
    }

    if (pDesc->isArray() == false)
    {
        if (pDesc->isMaxMinSet())
        {
            SINT32 rangeRet = pSviSystem->SetVarRange((char*) this->pModule->getAppName().c_str(),
                    (char*) pDesc->getVarName().c_str(), pDesc->getMinValue(),
                    pDesc->getMaxValue());
            if (rangeRet != SVI_E_OK)
            {
                throw SviException("Could not set min/max values for SVI Descriptor");
            }
        }
    }

    if (ret == SVI_E_OK)
    {
        return;
    }
    throw SviException("Could not export SVI Descriptor");
}

void SviServer::registerValueSvi(SviValueExportDescriptor *pDesc, Lockable *pLockable)
{
    if(pLockable == NULL) {
        throw SviException("Lockable object cannot be null");
    }

    SINT32 ret = 0;

    /** Add the global var */
    ret = pSviSystem->AddGlobVar(this->handle, (char*) pDesc->getVarName().c_str(),
            SviExportDescriptor::getFormat(pDesc), pDesc->getDataLength(), pDesc->getValueAddress(),
            pDesc->getMode(), (UINT32)pLockable, (SVI_FUNC_LOCK)&lock, (SVI_FUNC_UNLOCK)&unlock);

    if (pDesc->isArray() == false)
    {
        if (pDesc->isMaxMinSet())
        {
            SINT32 rangeRet = pSviSystem->SetVarRange((char*) this->pModule->getAppName().c_str(),
                    (char*) pDesc->getVarName().c_str(), pDesc->getMinValue(),
                    pDesc->getMaxValue());
            if (rangeRet != SVI_E_OK)
            {
                throw SviException("Could not set min/max values for SVI Descriptor");
            }
        }
    }

    if (ret == SVI_E_OK)
    {
        return;
    }
    throw SviException("Could not export SVI Descriptor");
}



