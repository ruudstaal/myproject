/**
 ********************************************************************************
 * @file     ErrorSession.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ErrorSession
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef ERRORSESSION_HPP_
#define ERRORSESSION_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>
#include <mio_e.h>

/**********************************************************************
 * project includes
 **********************************************************************/

#include "MIOSystem.hpp"

/**
 * @brief Class creates an Errorsession for a SW-module
 */
class ErrorSession
{
    friend class BasicIoModule;

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
     * @brief Constructor
     */
    ErrorSession();

    /**
     * @brief Constructor
     */
    explicit ErrorSession(CHAR* ApplicationName);

    /**
     * @brief Constructor
     */
    explicit ErrorSession(CHAR* ApplicationName, MIOSystem *pSystem);

    /**
     * @brief Default Destructor
     */
    virtual ~ErrorSession();

protected:

    /**
     * @brief Read Session ID
     *
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
    static VOID ErrorISR(VOID *DrvId, UINT32 Chan, UINT32 Error, UINT32 Para);

    /**
     * Desired MIOSystem
     */
    MIOSystem *m_pMioSystem;

};

#endif /** ERRORSESSION_HPP_ */
