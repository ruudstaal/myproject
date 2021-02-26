/*
 * M1SviSystem.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: madsen
 */

#include <M1SviSystem.hpp>
#include "svi_e.h"

M1SviSystem::M1SviSystem()
{
}

M1SviSystem::~M1SviSystem()
{
}

SINT32 M1SviSystem::GetVal(SVI_FUNC *pLib, SVI_ADDR Addr, UINT32 *pValue)
{
    return svi_GetVal(pLib, Addr, pValue);
}

SINT32 M1SviSystem::SetVal(SVI_FUNC *pLib, SVI_ADDR Addr, UINT32 Value)
{
    return svi_SetVal(pLib, Addr, Value);
}


SINT32 M1SviSystem::GetValLst(SVI_FUNC *pLib, SVI_ADDR *pAddrLst, UINT32 *pValueLst,
        UINT32 ListLen)
{
    return svi_GetValLst(pLib, pAddrLst, pValueLst, ListLen);
}

SINT32 M1SviSystem::SetValLst(SVI_FUNC *pLib, SVI_ADDR *pAddrLst, UINT32 *pValueLst,
        UINT32 ListLen)
{
    return svi_SetValLst(pLib, pAddrLst, pValueLst, ListLen);
}

SINT32 M1SviSystem::GetBlk(SVI_FUNC *pLib, SVI_ADDR Addr, void *pBuff, UINT32 *pBuffLen)
{
    return svi_GetBlk(pLib, Addr, pBuff, pBuffLen);
}


SINT32 M1SviSystem::SetBlk(SVI_FUNC *pLib, SVI_ADDR Addr, void *pBuff, UINT32 BuffLen)
{
    return svi_SetBlk(pLib, Addr, pBuff, BuffLen);
}

SVI_FUNC* M1SviSystem::GetLib(CHAR *pAppName)
{
    return svi_GetLib(pAppName);
}

SINT32 M1SviSystem::UngetLib(SVI_FUNC *pLib)
{
    return svi_UngetLib(pLib);
}

SINT32 M1SviSystem::GetAddr(SVI_FUNC *pLib, const CHAR *pName, SVI_ADDR *pAddr, UINT32 *pFormat)
{
    return svi_GetAddr(pLib, pName, pAddr, pFormat);
}

SINT32 M1SviSystem::GetPvInf(SVI_FUNC *pLib, UINT32 StartIdx, UINT32 *pNbOfPv, SVI_PVINF *pPvInf)
{
    return svi_GetPvInf(pLib, StartIdx, pNbOfPv, pPvInf);
}

SINT32 M1SviSystem::GetXPvInf(SVI_FUNC *pLib, CHAR *pPath, BOOL32 GetSubPv, UINT32 *pContPoint,
        UINT32 *pNbOfPv, SVI_XPVINF *pXPvInf, UINT32 *pPvInfLen)
{
    return svi_GetXPvInf(pLib, pPath, GetSubPv, pContPoint, pNbOfPv, pXPvInf, pPvInfLen);
}

SVI_XPVINF* M1SviSystem::GetXPvInfNext(SVI_XPVINF *pXPvInf)
{
    return svi_GetXPvInfNext(pXPvInf);
}

SINT32 M1SviSystem::GetServInf(SVI_FUNC *pLib, SVI_SERVINF *pServInf)
{
    return svi_GetServInf(pLib, pServInf);
}

SINT32 M1SviSystem::GetVarInf(SVI_FUNC *pLib, SVI_ADDR Addr, SVI_VARINF *pVarInf)
{
    return svi_GetVarInf(pLib, Addr, pVarInf);
}

SINT32 M1SviSystem::GetNameByAddr(SVI_FUNC *pLib, SVI_ADDR Addr, CHAR *pName)
{
    return svi_GetNameByAddr(pLib, Addr, pName);
}

UINT32 M1SviSystem::Init(CHAR * AppName, UINT32 Format, SINT32 (*fctp_Search)())
{
    return svi_Init(AppName, Format, fctp_Search);
}

UINT32 M1SviSystem::ReInit(UINT32 Handle)
{
    return svi_ReInit(Handle);
}

SINT32 M1SviSystem::DeInit(UINT32 Handle)
{
    return svi_DeInit(Handle);
}

SINT32 M1SviSystem::ApplyRights(UINT32 Handle)
{
    return svi_ApplyRights(Handle);
}

SINT32 M1SviSystem::AddGlobVar(UINT32 Handle, CHAR * Name, UINT32 Format, UINT32 Len,
        void *pAddr, UINT32 Mode, UINT32 UserParam, SVI_FUNC_LOCK fLock, SVI_FUNC_UNLOCK fUnlock)
{
    return svi_AddGlobVar(Handle, Name, Format, Len, pAddr, Mode, UserParam, fLock, fUnlock);
}

SINT32 M1SviSystem::AddVirtVar(UINT32 Handle, CHAR * Name, UINT32 Format, UINT32 Len,
        UINT32 Mode, UINT32 RPar1, UINT32 RPar2, UINT32 WPar1, UINT32 WPar2, SVI_FUNC_READ fRead,
        SVI_FUNC_WRITE fWrite)
{
    return svi_AddVirtVar(Handle, Name, Format, Len, Mode, RPar1, RPar2, WPar1, WPar2, fRead, fWrite);
}

//SINT32 M1SviSystem::fReadValPrototype(UINT32 RPar1, UINT32 RPar2, UINT32 *pValue, BOOL32 SvFlag,
//        UINT32 SessionId)
//{
//    return svi_fReadValPrototype(RPar1, RPar2, pValue, SvFlag, SessionId);
//}
//
//SINT32 M1SviSystem::fWriteValPrototype(UINT32 WPar1, UINT32 WPar2, UINT32 Value)
//{
//    return svi_fWriteValPrototype(WPar1, WPar2, Value);
//}
//
//SINT32 M1SviSystem::fReadBlkPrototype(UINT32 RPar1, UINT32 RPar2, UINT8 *pBuff,
//        UINT32 *pBuffLen, BOOL32 SvFlag, UINT32 SessionId)
//{
//    return svi_fReadBlkPrototype(RPar1, RPar2, pBuff, pBuffLen, SvFlag, SessionId);
//}
//
//SINT32 M1SviSystem::fWriteBlkPrototype(UINT32 WPar1, UINT32 WPar2, UINT8 *pBuff, UINT32 BuffLen,
//        BOOL32 SvFlag, UINT32 SessionId)
//{
//    return svi_fWriteBlkPrototype(WPar1, WPar2, pBuff, BuffLen, SvFlag, SessionId);
//}

SINT32 M1SviSystem::AddMarkers(UINT32 Handle, UINT32 Type, UINT32 Numb, void *pAddr,
        UINT32 NumbOfSetVal, UINT32 Mode, UINT32 UserParam, SVI_FUNC_MARKER_LOCK fLock,
        SVI_FUNC_MARKER_UNLOCK fUnlock)
{
    return svi_AddMarkers(Handle, Type, Numb, pAddr, NumbOfSetVal, Mode, UserParam, fLock, fUnlock);
}

SINT32 M1SviSystem::AddVirtMarkers(UINT32 Handle, UINT32 Type, UINT32 StartL, UINT32 StartH,
        UINT32 NumbL, UINT32 NumbH, UINT32 Mode, UINT32 UserParam, SVI_FUNC_MARKER_READ fRead,
        SVI_FUNC_MARKER_WRITE fWrite)
{
    return svi_AddVirtMarkers(Handle, Type, StartL, StartH, NumbL, NumbH, Mode, UserParam, fRead, fWrite);
}

void M1SviSystem::MsgHandler(UINT32 Handle, SMI_MSG *pMsg, SMI_ID *pSmiId)
{
    svi_MsgHandler(Handle, pMsg, pSmiId);
}


void M1SviSystem::MsgHandler2(UINT32 Handle, SMI_MSG *pMsg, SMI_ID *pSmiId, UINT32 User)
{
    svi_MsgHandler2(Handle, pMsg, pSmiId, User);
}


void M1SviSystem::SetDataInvalid(UINT32 Handle)
{
    svi_SetDataInvalid(Handle);
}


CHAR* M1SviSystem::GetClientsName(SINT32 (**pLib)())
{
    return svi_GetClientsName(pLib);
}

SINT32 M1SviSystem::SetVarRights(CHAR * AppName, CHAR * Name, UINT8 * ReadLevel,
        UINT8 * WriteLevel, UINT16 ElemCount)
{
    return svi_SetVarRights(AppName, Name, ReadLevel, WriteLevel, ElemCount);
}

SINT32 M1SviSystem::GetVarRights(CHAR * AppName, CHAR * Name, UINT8 * ReadLevel,
        UINT8 * WriteLevel, UINT16 ElemCount)
{
    return svi_GetVarRights(AppName, Name, ReadLevel, WriteLevel, ElemCount);
}

SINT32 M1SviSystem::SetVarRange(CHAR * AppName, CHAR * Name, REAL64 Min, REAL64 Max)
{
    return svi_SetVarRange(AppName, Name, Min, Max);
}

SINT32 M1SviSystem::GetVarRange(CHAR * AppName, CHAR * Name, REAL64 * Min, REAL64 * Max)
{
    return svi_GetVarRange(AppName, Name, Min, Max);
}

SINT32 M1SviSystem::AtomicCopy(UINT32 Handle, VOID *pDest, VOID *pSource, UINT32 Len)
{
    return svi_AtomicCopy(Handle, pDest, pSource, Len);
}

SINT32 M1SviSystem::AtomicRead(SINT32 VarHandle, VOID *pBuff, UINT32 *pBuffLen)
{
    return svi_AtomicRead(VarHandle, pBuff, pBuffLen);
}

SINT32 M1SviSystem::AtomicWrite(SINT32 VarHandle, VOID *pBuff, UINT32 BuffLen)
{
    return svi_AtomicWrite(VarHandle, pBuff, BuffLen);
}

SINT32 M1SviSystem::InsertGetBuffer(UINT32 Id, UINT32 Type, UINT32 BuffLen, UINT8 * Buff,
        UINT32 NbOfElem)
{
    return svi_InsertGetBuffer(Id, Type, BuffLen, Buff, NbOfElem);
}

SINT32 M1SviSystem::InsertSetBuffer(UINT32 Id, UINT32 Type, UINT32 BuffLen, UINT8 * Buff,
        SVI_ADDR *pAddr, UINT32 Offset, UINT32 NbOfElem)
{
    return svi_InsertSetBuffer(Id, Type, BuffLen, Buff, pAddr, Offset, NbOfElem);
}
