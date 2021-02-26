/*
 * M1SviSystem.hpp
 *
 *  Created on: Oct 10, 2018
 *      Author: madsen
 */

#ifndef BEFC_SVI_M1SVISYSTEM_HPP_
#define BEFC_SVI_M1SVISYSTEM_HPP_

#include <SviSystem.hpp>

class M1SviSystem: public SviSystem
{
public:
    M1SviSystem();

    SINT32 GetVal(SVI_FUNC *pLib, SVI_ADDR Addr, UINT32 *pValue);

    SINT32 SetVal(SVI_FUNC *pLib, SVI_ADDR Addr, UINT32 Value);

    SINT32 GetValLst(SVI_FUNC *pLib, SVI_ADDR *pAddrLst, UINT32 *pValueLst,
            UINT32 ListLen);

    SINT32 SetValLst(SVI_FUNC *pLib, SVI_ADDR *pAddrLst, UINT32 *pValueLst,
            UINT32 ListLen);

    SINT32 GetBlk(SVI_FUNC *pLib, SVI_ADDR Addr, void *pBuff, UINT32 *pBuffLen);

    SINT32 SetBlk(SVI_FUNC *pLib, SVI_ADDR Addr, void *pBuff, UINT32 BuffLen);

    SVI_FUNC *GetLib(CHAR *pAppName);

    SINT32 UngetLib(SVI_FUNC *pLib);

    SINT32 GetAddr(SVI_FUNC *pLib, const CHAR *pName, SVI_ADDR *pAddr,
            UINT32 *pFormat);

    SINT32 GetPvInf(SVI_FUNC *pLib, UINT32 StartIdx, UINT32 *pNbOfPv,
            SVI_PVINF *pPvInf);

    SINT32 GetXPvInf(SVI_FUNC *pLib, CHAR *pPath, BOOL32 GetSubPv, UINT32 *pContPoint,
            UINT32 *pNbOfPv, SVI_XPVINF *pXPvInf, UINT32 *pPvInfLen);

    SVI_XPVINF *GetXPvInfNext(SVI_XPVINF *pXPvInf);

    SINT32 GetServInf(SVI_FUNC *pLib, SVI_SERVINF *pServInf);

    SINT32 GetVarInf(SVI_FUNC *pLib, SVI_ADDR Addr, SVI_VARINF *pVarInf);

    SINT32 GetNameByAddr(SVI_FUNC *pLib, SVI_ADDR Addr, CHAR *pName);

    UINT32 Init(CHAR * AppName, UINT32 Format, SINT32 (*fctp_Search)());

    UINT32 ReInit(UINT32 Handle);

    SINT32 DeInit(UINT32 Handle);

    SINT32 ApplyRights(UINT32 Handle);

    SINT32 AddGlobVar(UINT32 Handle, CHAR * Name, UINT32 Format, UINT32 Len,
            void *pAddr, UINT32 Mode, UINT32 UserParam, SVI_FUNC_LOCK fLock,
            SVI_FUNC_UNLOCK fUnlock);

    SINT32 AddVirtVar(UINT32 Handle, CHAR * Name, UINT32 Format, UINT32 Len,
            UINT32 Mode, UINT32 RPar1, UINT32 RPar2, UINT32 WPar1, UINT32 WPar2,
            SVI_FUNC_READ fRead, SVI_FUNC_WRITE fWrite);

//    SINT32 fReadValPrototype(UINT32 RPar1, UINT32 RPar2, UINT32 *pValue, BOOL32 SvFlag,
//            UINT32 SessionId);
//
//    SINT32 fWriteValPrototype(UINT32 WPar1, UINT32 WPar2, UINT32 Value);
//
//    SINT32 fReadBlkPrototype(UINT32 RPar1, UINT32 RPar2, UINT8 *pBuff, UINT32 *pBuffLen,
//            BOOL32 SvFlag, UINT32 SessionId);
//
//    SINT32 fWriteBlkPrototype(UINT32 WPar1, UINT32 WPar2, UINT8 *pBuff, UINT32 BuffLen,
//            BOOL32 SvFlag, UINT32 SessionId);

    SINT32 AddMarkers(UINT32 Handle, UINT32 Type, UINT32 Numb, void *pAddr,
            UINT32 NumbOfSetVal, UINT32 Mode, UINT32 UserParam, SVI_FUNC_MARKER_LOCK fLock,
            SVI_FUNC_MARKER_UNLOCK fUnlock);

    SINT32 AddVirtMarkers(UINT32 Handle, UINT32 Type, UINT32 StartL, UINT32 StartH,
            UINT32 NumbL, UINT32 NumbH, UINT32 Mode, UINT32 UserParam, SVI_FUNC_MARKER_READ fRead,
            SVI_FUNC_MARKER_WRITE fWrite);

    void MsgHandler(UINT32 Handle, SMI_MSG *pMsg, SMI_ID *pSmiId);

    void MsgHandler2(UINT32 Handle, SMI_MSG *pMsg, SMI_ID *pSmiId, UINT32 User);

    void SetDataInvalid(UINT32 Handle);

    CHAR *GetClientsName(SINT32 (**pLib)());

    SINT32 SetVarRights(CHAR * AppName, CHAR * Name, UINT8 * ReadLevel,
            UINT8 * WriteLevel, UINT16 ElemCount);

    SINT32 GetVarRights(CHAR * AppName, CHAR * Name, UINT8 * ReadLevel,
            UINT8 * WriteLevel, UINT16 ElemCount);

    SINT32 SetVarRange(CHAR * AppName, CHAR * Name, REAL64 Min, REAL64 Max);

    SINT32 GetVarRange(CHAR * AppName, CHAR * Name, REAL64 * Min, REAL64 * Max);

    SINT32 AtomicCopy(UINT32 Handle, VOID *pDest, VOID *pSource, UINT32 Len);

    SINT32 AtomicRead(SINT32 VarHandle, VOID *pBuff, UINT32 *pBuffLen);

    SINT32 AtomicWrite(SINT32 VarHandle, VOID *pBuff, UINT32 BuffLen);

    SINT32 InsertGetBuffer(UINT32 Id, UINT32 Type, UINT32 BuffLen, UINT8 * Buff,
            UINT32 NbOfElem);

    SINT32 InsertSetBuffer(UINT32 Id, UINT32 Type, UINT32 BuffLen, UINT8 * Buff,
            SVI_ADDR *pAddr, UINT32 Offset, UINT32 NbOfElem);

    ~M1SviSystem();
};

#endif /* BEFC_SVI_M1SVISYSTEM_HPP_ */
