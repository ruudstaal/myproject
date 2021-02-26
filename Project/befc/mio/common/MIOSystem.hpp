/*
 * MIOSystem.hpp
 *
 *  Created on: Nov 6, 2017
 *      Author: madsen
 */

#ifndef RES_BEFC_MIO_COMMON_MIOSYSTEM_HPP_
#define RES_BEFC_MIO_COMMON_MIOSYSTEM_HPP_

#include "mio_e.h"

class MIOSystem
{
public:
    MIOSystem(){};

    virtual SINT32 getExtCardInf(UINT32 CardNb, MIO_EXTCDINF * pCardInf){return 0;}

    virtual SINT32 getExtCardInf2(UINT32 CardNb, MIO_EXTCDINF2 * pCardInf){return 0;}

    virtual SINT32 getValue(VOID * DrvId, UINT32 Chan, SINT32 * pValue){return 0;}

    virtual SINT32 setValue(VOID * DrvId, UINT32 Chan, SINT32 Value){return 0;}

    virtual SINT32 getValues(VOID * DrvId, SINT32 * pValue){return 0;}

    virtual SINT32 setValues(VOID * DrvId, SINT32 * pValue){return 0;}

    virtual SINT32 getPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount){return 0;}

    virtual SINT32 setPackedValues(VOID * DrvId, SINT32 * pValue, UINT32 StartChan, UINT32 ChanCount){return 0;}

    virtual SINT32 getError(VOID * DrvId, UINT32 Chan, UINT32 * pError){return 0;}

    virtual SINT32 getChanMode(VOID * DrvId, UINT32 Chan, UINT32 * pMode){return 0;}

    virtual SINT32 setChanMode(VOID * DrvId, UINT32 Chan, UINT32 Mode){return 0;}

    virtual SINT32 setSelect(VOID * DrvId, UINT32 Chan, UINT32 Select){return 0;}

    virtual SINT32 getCardMode(VOID * DrvId, UINT32 * pMode){return 0;}

    virtual SINT32 setCardMode(VOID * DrvId, UINT32 Mode){return 0;}

    virtual SINT32 attachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event, VOID (*AppIsr)(),
            UINT32 UserParam){return 0;}

    virtual SINT32 detachEvent(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Event){return 0;}

    virtual SINT32 attachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error, VOID (*AppIsr)(),
            UINT32 UserParam){return 0;}

    virtual SINT32 detachError(VOID * DrvId, SINT32 SessId, UINT32 Chan, UINT32 Error){return 0;}

    virtual SINT32 getCardInf(const VOID * DrvId, MIO_CARDINF * CardInf){return 0;}

    virtual SINT32 getChanInf(const VOID * DrvId, UINT32 Chan, MIO_CHANINF * ChanInf){return 0;}

    virtual SINT32 reset(VOID * DrvId){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5){return 0;}

    virtual SINT32 doCmd(VOID * DrvId, UINT32 Chan, UINT32 Cmd, UINT32 param1, UINT32 param2, UINT32 param3, UINT32 param4, UINT32 param5, UINT32 param6){return 0;}

    virtual VOID* getDrv(UINT32 CardNb){return 0;}

    virtual VOID walkCardList(VOID (*UserFunc)()){};

    virtual VOID walkCardList(VOID (*UserFunc)(), UINT32 param){};

    virtual SINT32 hw_ReadIdReg(UINT32 SlotNb, MIO_IDREG * pIdReg){return 0;}

    virtual SINT32 startEventSession(CHAR * pAppName){return 0;}

    virtual SINT32 stopEventSession(SINT32 SessId){return 0;}    // Use return value only on MSys >= 3.30R

    virtual SINT32 startErrorSession(CHAR * pAppName){return 0;}

    virtual SINT32 stopErrorSession(SINT32 SessId){return 0;}// Use return value only on MSys >= 3.30R

    virtual SINT32 startSyncSession(CHAR * pAppName){return 0;};

    virtual SINT32 stopSyncSession(SINT32 SessId){return 0;}// Use return value only on MSys >= 3.30R

    virtual SINT32 attachSync(SINT32 SessId, UINT32 Type, UINT32 Counter, VOID(*AppIsr) (), UINT32 UserParam){return 0;}

    virtual SINT32 detachSync(SINT32 SessId, UINT32 Type, UINT32 Counter, VOID(*AppIsr) (), UINT32 UserParam){return 0;}

    virtual SINT32 piCreateHandle(const CHAR * pAppName, MIO_PIHANDLE * pPiHandle, SINT32 Priority, VOID(*CallBackFctRead) (UINT32 UserParamRead),
            UINT32 UserParamRead,
            VOID(*CallBackFctWrite) (UINT32 UserParamWrite),
            UINT32 UserParamWrite){return 0;}

    virtual VOID piRemoveHandle(MIO_PIHANDLE PiHandle){}

    virtual SINT32 piSetPriority(MIO_PIHANDLE PiHandle, SINT32 Priority){return 0;}

    virtual VOID* piGetDrv(MIO_PIHANDLE PiHandle, SINT32 CardNb, UINT32 ConfigAllChannels, UINT32 flags){return NULL;}

    virtual SINT32 piConfigChan(VOID * pPiDrvId, UINT32 chan){return 0;}

    virtual SINT32 piUpdateIn(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks){return 0;}

    virtual SINT32 piUpdateOut(MIO_PIHANDLE PiHandle, SINT32 timeoutTicks){return 0;}

    virtual SINT32 findChanRange(MIO_DRV* DrvId, UINT32 chan, MIO_CHAN_RANGE *pChanRange){return 0;}

    virtual ~MIOSystem(){};
};

#endif /* RES_BEFC_MIO_COMMON_MIOSYSTEM_HPP_ */
