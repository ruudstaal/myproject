/**
 ********************************************************************************
 * @file     SyncSession.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SyncSession
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SyncSession.hpp"
#include <string.h>
#include "M1MIOSystem.hpp"
#include "mcpp.hpp"

/**-----------------------------------------------------------------*/
SyncSession::SyncSession() :
        m_si32SessionId(-1), m_si32MioError(0), m_SyncSig(0), m_SyncType(MIO_SYNC_IN),
        m_SyncCounter(1)
{
    m_pMioSystem = new M1MIOSystem();
}

/**-----------------------------------------------------------------*/
SyncSession::SyncSession(CHAR* ApplicationName) :
        m_si32SessionId(-1), m_si32MioError(0), m_SyncSig(0), m_SyncType(MIO_SYNC_IN),
        m_SyncCounter(1)
{
    m_pMioSystem = new M1MIOSystem();
    /** Start sync session */

    m_si32SessionId = m_pMioSystem->startSyncSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("SyncSession: can not Start Sync session!");
    }

    /** Initialize signal for communication between ISR and IST (interrupt service task). */
    m_SyncSig = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (!m_SyncSig)
    {
        log_Err("SyncSession: can not create semaphore for Sync session!");
    }

    if (m_pMioSystem->attachSync(m_si32SessionId, m_SyncType, m_SyncCounter, (void (*)())semGive, (UINT32)m_SyncSig))
    {
        log_Err("SyncSession: can not attach to Sync session!");
    }
}

/**-----------------------------------------------------------------*/
SyncSession::SyncSession(CHAR* ApplicationName, MIOSystem *pSystem) :
        m_si32SessionId(-1), m_si32MioError(0), m_SyncSig(0), m_SyncType(MIO_SYNC_IN),
        m_SyncCounter(1)
{
    m_pMioSystem = pSystem;

    /** Start sync session */
    m_si32SessionId = m_pMioSystem->startSyncSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("SyncSession: can not Start Sync session!");
    }

    /** Initialize signal for communication between ISR and IST (interrupt service task). */
    m_SyncSig = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (!m_SyncSig)
    {
        log_Err("SyncSession: can not create semaphore for Sync session!");
    }

    if (m_pMioSystem->attachSync(m_si32SessionId, m_SyncType, m_SyncCounter, (void (*)())semGive, (UINT32)m_SyncSig))
    {
        log_Err("SyncSession: can not attach to Sync session!");
    }
}


/**-----------------------------------------------------------------*/
SyncSession::SyncSession(CHAR* ApplicationName, UINT32 SyncCounter, UINT32 SyncType) :
        m_si32SessionId(-1), m_si32MioError(0), m_SyncSig(0), m_SyncType(SyncType), m_SyncCounter(
                SyncCounter)
{
    m_pMioSystem = new M1MIOSystem();
    /** Start sync session */
    m_si32SessionId = m_pMioSystem->startSyncSession(ApplicationName);
    if (-1 == m_si32SessionId)
    {
        log_Err("SyncSession: can not Start Sync session!");
    }

    /** Initialize signal for communication between ISR and IST (interrupt service task). */
    m_SyncSig = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (!m_SyncSig)
    {
        log_Err("SyncSession: can not create semaphore for Sync session!");
    }

    if (m_pMioSystem->attachSync(m_si32SessionId, m_SyncType, m_SyncCounter, (void (*)())semGive, (UINT32)m_SyncSig))
    {
        log_Err("SyncSession: can not attach to Sync session!");
    }
}

/**-----------------------------------------------------------------*/
SyncSession::~SyncSession()
{
    SINT32 ret;

    /** Stop sync session */
    if (-1 != m_si32SessionId)
    {
        ret = m_pMioSystem->stopSyncSession(m_si32SessionId);
        if (0 > ret)
        {
            log_Err("Failed to Stop SyncSession %d", ret);
        }
    }
    /** Delete semaphore */
    if (m_SyncSig)
    {
        semDelete(m_SyncSig);
    }
}

void SyncSession::WaitForSync(void)
{
    semTake(m_SyncSig, WAIT_FOREVER);
}

STATUS SyncSession::WaitForSync(SINT32 TimeOut)
{
    return semTake(m_SyncSig, TimeOut);
}

void SyncSession::FlushSync(void)
{
	if (m_SyncSig)
	{
		semFlush(m_SyncSig);
	}
}
