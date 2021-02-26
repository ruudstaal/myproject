/**
 ********************************************************************************
 * @file     ErrorSession.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ErrorSession
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <log_e.h>

#include "ErrorSession.hpp"
#include "base/BasicErrorListener.hpp"
#include <string.h>
#include "M1MIOSystem.hpp"
#include "mcpp.hpp"

/**-----------------------------------------------------------------*/
ErrorSession::ErrorSession() :
        m_si32SessionId(-1), m_si32MioError(0)
{
    m_pMioSystem = new M1MIOSystem();
}

/**-----------------------------------------------------------------*/
ErrorSession::ErrorSession(CHAR* ApplicationName) :
        m_si32SessionId(-1), m_si32MioError(0)
{
    m_pMioSystem = new M1MIOSystem();

    m_si32SessionId = m_pMioSystem->startErrorSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("ErrorSession: can not Start Errorsession!");
    }
}

ErrorSession::ErrorSession(CHAR* ApplicationName, MIOSystem *pSystem) : m_si32SessionId(-1), m_si32MioError(0){
    m_pMioSystem = pSystem;

    m_si32SessionId = m_pMioSystem->startErrorSession(ApplicationName);

    if (-1 == m_si32SessionId)
    {
        log_Err("ErrorSession: can not Start Errorsession!");
    }
}

/**-----------------------------------------------------------------*/
ErrorSession::~ErrorSession()
{
	int ret;
    if (-1 != m_si32SessionId)
    {
    	ret = m_pMioSystem->stopErrorSession(m_si32SessionId);
        if (0 > ret)
        {
            log_Err("Failed to Stop ErrorSession, Error = %d, SessionId = %d",ret ,m_si32SessionId);
        }
    }

    SAFE_DELETE(m_pMioSystem);
}

/**-----------------------------------------------------------------*/
void ErrorSession::ErrorISR(void* DrvId, UINT32 Chan, UINT32 Error, UINT32 Para)
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
        BasicErrorListener *l_pListener = static_cast<BasicErrorListener*>((VOID*) Para);

        if (0 > l_pListener->ErrorOccured(l_CardInfo.CardNb, Chan, Error))
        {
            log_Err("Event Listener returned Error");
        }
    }
    else
    {
        if (0 < Chan)
        {
            log_Info("ErrorSession::ErrorISR: Module %d Channel %d reported 0x%x",
                    l_CardInfo.CardNb, Chan, Error);
        }

        if (0 == Chan)
        {
            log_Info("ErrorSession::ErrorISR: Module %d reported 0x%x", l_CardInfo.CardNb, Error);
        }
    }
}

