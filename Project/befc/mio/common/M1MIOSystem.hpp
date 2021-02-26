/*
 * M1MIOSystem.hpp
 *
 *  Created on: Nov 6, 2017
 *      Author: madsen
 */

#ifndef RES_BEFC_MIO_COMMON_M1MIOSYSTEM_HPP_
#define RES_BEFC_MIO_COMMON_M1MIOSYSTEM_HPP_

#include <MIOSystem.hpp>
#include "mio.h"
#include "mio_e.h"

class M1MIOSystem: public MIOSystem
{
public:

    M1MIOSystem();

    SINT32 getExtCardInf(UINT32 CardNb, MIO_EXTCDINF * pCardInf);

    SINT32 getExtCardInf2(UINT32 CardNb, MIO_EXTCDINF2 * pCardInf);

    SINT32 getValue(VOID * DrvId, UINT32 Chan, SINT32 * pValue);

    SINT32 setValue(VOID * DrvId, UINT32 Chan, SINT32 Value);

    SINT32 getValues(VOID * DrvId, SINT32 * pValue);

    SINT32 setValues(VOID * DrvId, SINT32 * pValue);

    SINT32 getPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount);

    SINT32 setPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount);

    SINT32 getError(VOID * DrvId, UINT32 Chan, UINT32 * pError);

    SINT32 getChanMode(VOID * DrvId, UINT32 Chan, UINT32 * pMode);

    SINT32 setChanMode(VOID * DrvId, UINT32 Chan, UINT32 Mode);

    SINT32 setSelect(VOID * DrvId, UINT32 Chan, UINT32 Select);

    SINT32 getCardMode(VOID * DrvId, UINT32 * pMode);

    SINT32 setCardMode(VOID * DrvId, UINT32 Mode);

    SINT32 attachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event, VOID (*AppIsr)(),
            UINT32 UserParam);

    SINT32 detachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event);

    SINT32 attachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error, VOID (*AppIsr)(),
            UINT32 UserParam);

    SINT32 detachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error);

    SINT32 getCardInf(const VOID * DrvId, MIO_CARDINF * CardInf);

    SINT32 getChanInf(const VOID * DrvId, UINT32 Chan, MIO_CHANINF * ChanInf);

    SINT32 reset(VOID * DrvId);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5);

    SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5, UINT32 param6);

    VOID* getDrv(UINT32 CardNb);

    VOID walkCardList(VOID (*UserFunc)());

    VOID walkCardList(VOID (*UserFunc)(), UINT32 param);

    SINT32 hw_ReadIdReg(UINT32 SlotNb, MIO_IDREG * pIdReg);

    SINT32 startEventSession(CHAR * pAppName);

    SINT32 stopEventSession(SINT32 SessId);    // Use return value only on MSys >= 3.30R

    SINT32 startErrorSession(CHAR * pAppName);

    SINT32 stopErrorSession(SINT32 SessId);// Use return value only on MSys >= 3.30R

    SINT32 startSyncSession(CHAR * pAppName);

    SINT32 stopSyncSession(SINT32 SessId);// Use return value only on MSys >= 3.30R

    SINT32 attachSync(SINT32 SessId, UINT32 Type, UINT32 Counter,
            VOID(*AppIsr) (), UINT32 UserParam);

    SINT32 detachSync(SINT32 SessId, UINT32 Type, UINT32 Counter,
            VOID(*AppIsr) (), UINT32 UserParam);

    SINT32 piCreateHandle(const CHAR * pAppName, MIO_PIHANDLE * pPiHandle,
            SINT32 Priority, VOID(*CallBackFctRead) (UINT32 UserParamRead),
            UINT32 UserParamRead,
            VOID(*CallBackFctWrite) (UINT32 UserParamWrite),
            UINT32 UserParamWrite);

    VOID piRemoveHandle(MIO_PIHANDLE PiHandle);

    SINT32 piSetPriority(MIO_PIHANDLE PiHandle, SINT32 Priority);

    VOID* piGetDrv(MIO_PIHANDLE PiHandle, SINT32 CardNb, UINT32 ConfigAllChannels, UINT32 flags);

    SINT32 piConfigChan(VOID * pPiDrvId, UINT32 chan);

    SINT32 piUpdateIn(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks);

    SINT32 piUpdateOut(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks);

    SINT32 findChanRange(MIO_DRV* DrvId, UINT32 chan, MIO_CHAN_RANGE *pChanRange);

    ~M1MIOSystem();
};

#endif /* RES_BEFC_MIO_COMMON_M1MIOSYSTEM_HPP_ */
