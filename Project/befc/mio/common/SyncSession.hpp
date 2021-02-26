/**
 ********************************************************************************
 * @file     SyncSession.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SyncSession
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef SYNCSESSION_HPP_
#define SYNCSESSION_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>
#include <mio_e.h>
#include <log_e.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "MIOSystem.hpp"
/**
 * @brief Class creates an Sync session for a SW-module
 */
class SyncSession
{
private:
	/**
	 * Session ID
	 */
	SINT32 m_si32SessionId;

	/**
	 * stored error id if function fails
	 */
	SINT32 m_si32MioError;

public:
    /**
     * @brief Default Constructor
     */
    SyncSession();

	/**
	 * @brief Constructor
	 */
    explicit SyncSession(CHAR* ApplicationName);

    /**
     * @brief Constructor
     */
    explicit SyncSession(CHAR* ApplicationName, MIOSystem *pSystem);

    /**
	 * @brief Constructor
	 */
	explicit SyncSession(CHAR* ApplicationName, UINT32 SyncCounter, UINT32 SyncType);

	/**
	 * @brief Default Destructor
	 */
	virtual ~SyncSession();

	/**
	 * @brief Wait sync signal
	 */
	void WaitForSync(void);

	/**
	 * @brief Wait sync signal,
     * @param TimeOut	The timeout in ticks
     *
     * @returns OK = Task woken up by sync interrupt
     * @returns ERROR = When timeout did occur before sync interrupt
	 */
	STATUS WaitForSync(SINT32 TimeOut);

	/**
	 * @brief Flush sync signal, used to wakeup task during shutdown
	 */
	void FlushSync(void);

protected:

	/**
     * @brief Read Session ID
     *
     * @returns > 0 Session ID
     * @returns -1 No Session Started
     */
    SINT32 getSessionId(VOID) const
    {
        return m_si32SessionId;
    }

private:
    SEM_ID m_SyncSig;   		/** Signal Sync-ISR -> Sync task */
    UINT32 m_SyncType;			/** Sync type: */
    UINT32 m_SyncCounter;		/** Sync counter */

    MIOSystem *m_pMioSystem;    /** Desired MIOSystem */
};

#endif /** SYNCSESSION_HPP_ */
