/**
 ********************************************************************************
 * @file     EventSession.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of EventSession
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "EventSession.hpp"
#include "base/BasicEventListener.hpp"
#include <string.h>
#include "M1MIOSystem.hpp"
#include "mcpp.hpp"

UINT32 EventSession::EVT_VALUE = MIO_EV_VALUE; /**< Event on change of value */
UINT32 EventSession::EVT_REFERENCE = MIO_EV_REFERENCE; /**< Event at reference point */
UINT32 EventSession::EVT_RESET = MIO_EV_RESET; /**< Event home done */
UINT32 EventSession::EVT_LATCHSTRB = MIO_EV_LATCHSTRB; /**< Latch into strobe register done */
UINT32 EventSession::EVT_LATCHREF = MIO_EV_LATCHREF; /**< Latch into reference register done */
UINT32 EventSession::EVT_LATCHSTRBOV = MIO_EV_LATCHSTRBOV; /**< Latch strobe overwritten */
UINT32 EventSession::EVT_LATCHREFLOS = MIO_EV_LATCHREFLOS; /**< Latch reference register lost */
UINT32 EventSession::EVT_DATARDY = MIO_EV_DATARDY; /**< New data available */
UINT32 EventSession::EVT_SYSTEM = MIO_EV_SYSTEM; /**< Generic errors */
UINT32 EventSession::EVT_USER = MIO_EV_USER;

/**-----------------------------------------------------------------*/
EventSession::EventSession() :
        m_si32SessionId(-1), m_si32MioError(0)
{
    m_pMioSystem = new M1MIOSystem();
}

/**-----------------------------------------------------------------*/
EventSession::EventSession(CHAR* ApplicationName) :
        m_si32SessionId(-1), m_si32MioError(0)
{
    m_pMioSystem = new M1MIOSystem();


    m_si32SessionId = m_pMioSystem->startEventSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("EventSession: can not Start Eventsession!");
    }
}

/**-----------------------------------------------------------------*/
EventSession::EventSession(CHAR* ApplicationName, MIOSystem *pSystem) :
        m_si32SessionId(-1), m_si32MioError(0)
{
    m_pMioSystem = pSystem;

    m_si32SessionId = m_pMioSystem->startEventSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("EventSession: can not Start Eventsession!");
    }
}


/**-----------------------------------------------------------------*/
EventSession::~EventSession()
{
	int ret;
    if (-1 != m_si32SessionId)
    {
    	ret = m_pMioSystem->stopEventSession(m_si32SessionId);
        if (0 > ret)
        {
            log_Err("Failed to Stop EventSession, Event = %d, SessionId = %d",ret ,m_si32SessionId);
        }
    }
    SAFE_DELETE(m_pMioSystem);
}

/**-----------------------------------------------------------------*/
void EventSession::EventISR(void* DrvId, UINT32 Chan, UINT32 Event, UINT32 Para)
{
    MIO_CARDINF l_CardInfo;

    memset(&l_CardInfo, 0, sizeof(MIO_CARDINF));

    if (NULL != DrvId)
    {
        if (0 > mio_GetCardInf(DrvId, &l_CardInfo))
        {
            log_Err("Unknown Driver ID (NULL)");
        }
    }

    if (0 != Para)
    {
        BasicEventListener *l_pListener = static_cast<BasicEventListener*>((VOID*) Para);

        if (0 > l_pListener->EventOccured(l_CardInfo.CardNb, Chan, Event))
        {
            log_Err("Event Listener returned Error");
        }
    }
    else
    {
        if (0 < Chan)
        {
            log_Info("EventSession::EventISR: Module %d Channel %d reported 0x%x",
                    l_CardInfo.CardNb, Chan, Event);
        }

        if (0 == Chan)
        {
            log_Info("EventSession::EventISR: Module %d reported 0x%x", l_CardInfo.CardNb, Event);
        }
    }
}

