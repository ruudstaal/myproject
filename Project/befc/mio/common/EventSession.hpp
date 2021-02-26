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

#ifndef EVENTSESSION_HPP_
#define EVENTSESSION_HPP_

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
 * @brief Class creates an Eventsession for a SW-module
 */
class EventSession
{
    friend class BasicIoModule;

public:
    /**
     * Mapping from MIO-Events
     */
    static UINT32 EVT_VALUE; /***< Event on change of value */
    static UINT32 EVT_REFERENCE; /***< Event at reference point */
    static UINT32 EVT_RESET; /***< Event home done */
    static UINT32 EVT_LATCHSTRB; /***< Latch into strobe register done */
    static UINT32 EVT_LATCHREF; /***< Latch into reference register done */
    static UINT32 EVT_LATCHSTRBOV; /***< Latch strobe overwritten */
    static UINT32 EVT_LATCHREFLOS; /***< Latch reference register lost */
    static UINT32 EVT_DATARDY; /***< New data available */
    static UINT32 EVT_SYSTEM; /***< Generic errors */
    static UINT32 EVT_USER; /***< Driver specific error */

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
    EventSession();

    /**
     * @brief Constructor
     */
    explicit EventSession(CHAR* ApplicationName);

    /**
     * @brief Constructor
     */
    explicit EventSession(CHAR* ApplicationName, MIOSystem *pSystem);

    /**
     * @brief Default Destructor
     */
    virtual ~EventSession();

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

    /**
     * @brief Callback method if Error occurs
     */
    static VOID EventISR(VOID *DrvId, UINT32 Chan, UINT32 Event, UINT32 Para);

    /**
     * Desired MIOSystem
     */
    MIOSystem *m_pMioSystem;

};

#endif /** EVENTSESSION_HPP_ */
