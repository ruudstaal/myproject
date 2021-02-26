/*
 * M1MIOSystem.cpp
 *
 *  Created on: Nov 6, 2017
 *      Author: madsen
 */

#include <M1MIOSystem.hpp>

#include "BasicIoModule.hpp"

M1MIOSystem::M1MIOSystem()
{
}

M1MIOSystem::~M1MIOSystem()
{
}

SINT32 M1MIOSystem::getExtCardInf(UINT32 CardNb, MIO_EXTCDINF * pCardInf)
{
    return mio_GetExtCardInf(CardNb, pCardInf);
}

SINT32 M1MIOSystem::getExtCardInf2(UINT32 CardNb, MIO_EXTCDINF2 * pCardInf)
{
    return mio_GetExtCardInf2(CardNb, pCardInf);
}

SINT32 M1MIOSystem::getValue(VOID * DrvId, UINT32 Chan, SINT32 * pValue)
{
    return mio_GetValue(DrvId, Chan, pValue);
}

SINT32 M1MIOSystem::setValue(VOID * DrvId, UINT32 Chan, SINT32 Value)
{
    return mio_SetValue(DrvId, Chan, Value);
}

SINT32 M1MIOSystem::getValues(VOID * DrvId, SINT32 * pValue)
{
    return mio_GetValues(DrvId, pValue);
}

SINT32 M1MIOSystem::setValues(VOID * DrvId, SINT32 * pValue)
{
    return mio_SetValues(DrvId, pValue);
}

SINT32 M1MIOSystem::getPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount)
{
    return mio_GetPackedValues(DrvId, pValue, StartChan, ChanCount);
}

SINT32 M1MIOSystem::setPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount)
{
    return mio_SetPackedValues(DrvId, pValue, StartChan, ChanCount);
}

SINT32 M1MIOSystem::getError(VOID * DrvId, UINT32 Chan, UINT32 * pError)
{
    return mio_GetError(DrvId, Chan, pError);
}

SINT32 M1MIOSystem::getChanMode(VOID * DrvId, UINT32 Chan, UINT32 * pMode)
{
    return mio_GetChanMode(DrvId, Chan, pMode);
}

SINT32 M1MIOSystem::setChanMode(VOID * DrvId, UINT32 Chan, UINT32 Mode)
{
    return mio_SetChanMode(DrvId, Chan, Mode);
}

SINT32 M1MIOSystem::setSelect(VOID * DrvId, UINT32 Chan, UINT32 Select)
{
    return mio_SetSelect(DrvId, Chan, Select);
}

SINT32 M1MIOSystem::getCardMode(VOID * DrvId, UINT32 * pMode)
{
    return mio_GetCardMode(DrvId, pMode);
}

SINT32 M1MIOSystem::setCardMode(VOID * DrvId, UINT32 Mode)
{
    return mio_SetCardMode(DrvId, Mode);
}

SINT32 M1MIOSystem::attachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event, VOID (*AppIsr)(), UINT32 UserParam)
{
    return mio_AttachEvent(DrvId, SessId, Chan, Event, AppIsr, UserParam);
}

SINT32 M1MIOSystem::detachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event)
{
    return mio_DetachEvent(DrvId, SessId, Chan, Event);
}

SINT32 M1MIOSystem::attachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error, VOID (*AppIsr)(), UINT32 UserParam)
{
    return mio_AttachError(DrvId, SessId, Chan, Error, AppIsr, UserParam);
}

SINT32 M1MIOSystem::detachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error)
{
    return mio_DetachError(DrvId, SessId, Chan, Error);
}

SINT32 M1MIOSystem::getCardInf(const VOID * DrvId, MIO_CARDINF * CardInf)
{
    return mio_GetCardInf(DrvId, CardInf);
}

SINT32 M1MIOSystem::getChanInf(const VOID * DrvId, UINT32 Chan, MIO_CHANINF * ChanInf)
{
    return mio_GetChanInf(DrvId, Chan, ChanInf);
}

SINT32 M1MIOSystem::reset(VOID * DrvId)
{
    return mio_Reset(DrvId);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd){
    return mio_DoCmd(DrvId, Chan, Cmd);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1){
    return mio_DoCmd(DrvId, Chan, Cmd, param1);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2){
    return mio_DoCmd(DrvId, Chan, Cmd, param1, param2);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3){
    return mio_DoCmd(DrvId, Chan, Cmd, param1, param2, param3);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4){
    return mio_DoCmd(DrvId, Chan, Cmd, param1, param2, param3, param4);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5){
    return mio_DoCmd(DrvId, Chan, Cmd, param1, param2, param3, param4, param5);
}

SINT32 M1MIOSystem::doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5, UINT32 param6)
{
    return mio_DoCmd(DrvId, Chan, Cmd, param1, param2, param3, param4, param5, param6);
}

VOID* M1MIOSystem::getDrv(UINT32 CardNb)
{
    return mio_GetDrv(CardNb);
}

VOID M1MIOSystem::walkCardList(VOID (*UserFunc)(), UINT32 param){
    mio_WalkCardList(UserFunc,param);
}

VOID M1MIOSystem::walkCardList(VOID (*UserFunc)()) {
    mio_WalkCardList(UserFunc);
}

SINT32 M1MIOSystem::hw_ReadIdReg(UINT32 SlotNb, MIO_IDREG * pIdReg)
{
    return 0;
}

SINT32 M1MIOSystem::startEventSession(CHAR * pAppName)
{
    return mio_StartEventSession(pAppName);
}

SINT32 M1MIOSystem::stopEventSession(SINT32 SessId)
{
    return mio_StopEventSession(SessId);
}    // Use return value only on MSys >= 3.30R

SINT32 M1MIOSystem::startErrorSession(CHAR * pAppName)
{
    return mio_StartErrorSession(pAppName);
}

SINT32 M1MIOSystem::stopErrorSession(SINT32 SessId)
{
    return mio_StopErrorSession(SessId);
}    // Use return value only on MSys >= 3.30R

SINT32 M1MIOSystem::startSyncSession(CHAR * pAppName)
{
    return mio_StartSyncSession(pAppName);
}

SINT32 M1MIOSystem::stopSyncSession(SINT32 SessId)
{
    return mio_StopSyncSession(SessId);
}    // Use return value only on MSys >= 3.30R

SINT32 M1MIOSystem::attachSync(SINT32 SessId, UINT32 Type, UINT32 Counter, VOID (*AppIsr)(), UINT32 UserParam)
{
    return mio_AttachSync(SessId, Type, Counter, AppIsr, UserParam);
}

SINT32 M1MIOSystem::detachSync(SINT32 SessId, UINT32 Type, UINT32 Counter, VOID (*AppIsr)(), UINT32 UserParam)
{
    return mio_DetachSync(SessId, Type, Counter, AppIsr, UserParam);
}

SINT32 M1MIOSystem::piCreateHandle(const CHAR * pAppName, MIO_PIHANDLE * pPiHandle,
        SINT32 Priority, VOID (*CallBackFctRead)(UINT32 UserParamRead), UINT32 UserParamRead,
        VOID (*CallBackFctWrite)(UINT32 UserParamWrite), UINT32 UserParamWrite)
{
    return mio_PiCreateHandle(pAppName, pPiHandle, Priority, CallBackFctRead, UserParamRead, CallBackFctWrite, UserParamWrite);
}

VOID M1MIOSystem::piRemoveHandle(MIO_PIHANDLE PiHandle)
{
    mio_PiRemoveHandle(PiHandle);
}

SINT32 M1MIOSystem::piSetPriority(MIO_PIHANDLE PiHandle, SINT32 Priority)
{
    return mio_PiSetPriority(PiHandle, Priority);
}

VOID* M1MIOSystem::piGetDrv(MIO_PIHANDLE PiHandle, SINT32 CardNb, UINT32 ConfigAllChannels, UINT32 flags)
{
    return mio_PiGetDrv(PiHandle, CardNb, ConfigAllChannels, flags);
}

SINT32 M1MIOSystem::piConfigChan(VOID * pPiDrvId, UINT32 chan)
{
    return mio_PiConfigChan(pPiDrvId, chan);
}

SINT32 M1MIOSystem::piUpdateIn(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks)
{
    return mio_PiUpdateIn(PiHandle, timeoutTicks);
}

SINT32 M1MIOSystem::piUpdateOut(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks)
{
    return mio_PiUpdateOut(PiHandle, timeoutTicks);
}

SINT32 M1MIOSystem::findChanRange(MIO_DRV* DrvId, UINT32 chan, MIO_CHAN_RANGE *pChanRange)
{
    return mio_FindChanRange(DrvId, chan, pChanRange);
}
