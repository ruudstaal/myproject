/**
 ********************************************************************************
 * @file     ProcessImage.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProcessImage
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "ProcessImage.hpp"
#include "M1MIOSystem.hpp"
#include <log_e.h>
#include <string.h>

/**-----------------------------------------------------------------*/
ProcessImage::ProcessImage()
{
    initvalues();
}

/**-----------------------------------------------------------------*/
ProcessImage::ProcessImage(CHAR* pModuleName)
{
    m_pMioSystem = NULL;

    initvalues();
    strncpy(m_ModuleName, pModuleName, sizeof(m_ModuleName) - 1);
    init();
}


/**-----------------------------------------------------------------*/
ProcessImage::ProcessImage(CHAR* pModuleName, M1MIOSystem *pSystem)
{
    m_pMioSystem = pSystem;

    initvalues();
    strncpy(m_ModuleName, pModuleName, sizeof(m_ModuleName) - 1);
    init();
}



void ProcessImage::initvalues()
{
    m_ui32Priority = 80;
    m_ProcessImageHandle = NULL;
    m_ui32ParameterInput = 0;
    m_ui32ParameterOutput = 0;
    m_pCallBackInputReady = NULL;
    m_pCallBackOutputReady = NULL;
    memset(m_ModuleName, 0, sizeof(m_ModuleName));

    //Default handling of the MIO system is the 'real' system.
    if (m_pMioSystem == NULL)
    {
        m_pMioSystem = new M1MIOSystem();
    }
}

/**-----------------------------------------------------------------*/
void ProcessImage::init()
{

    SINT32 l_si32RetCode;


    /** create Handle for Processimage Usage */
    l_si32RetCode = m_pMioSystem->piCreateHandle(m_ModuleName, &m_ProcessImageHandle, (SINT32) m_ui32Priority,
    NULL, 0,
    NULL, 0);

    if (l_si32RetCode != 0)
    {
        throw MIOexception("Could not create handle to ProcessImage", -1, l_si32RetCode);
    }
    if (m_ProcessImageHandle == NULL)
    {
        throw MIOexception("Could not create handle to ProcessImage", -1, l_si32RetCode);
    }
}

/**-----------------------------------------------------------------*/
ProcessImage::~ProcessImage()
{
    m_pMioSystem->piRemoveHandle(m_ProcessImageHandle);

    SAFE_DELETE(m_pMioSystem);

}

/**-----------------------------------------------------------------*/
VOID *ProcessImage::addCard(UINT32 ui32CardNumber)
{
    return add(ui32CardNumber, TRUE);
}

/**-----------------------------------------------------------------*/
VOID *ProcessImage::addCard(BasicIoModule *pModule)
{
    VOID* l_pDriverId;

    l_pDriverId = add(pModule->getCardNumber(), TRUE);
    return l_pDriverId;
}

/**-----------------------------------------------------------------*/
VOID *ProcessImage::add(UINT32 ui32CardNumber, BOOL8 b8AllChannels)
{
    VOID * l_pDriver;

    /** add card to System ProcessImage List */
    l_pDriver = m_pMioSystem->piGetDrv(m_ProcessImageHandle, (SINT32) ui32CardNumber, b8AllChannels, MIO_PI_FLAGS_NONE);

    if (NULL == l_pDriver)
    {
        throw MIOexception("ProcessImage did not support card %d", ui32CardNumber, 0);
    }

    return l_pDriver;
}

/**-----------------------------------------------------------------*/
VOID *ProcessImage::addChannel(UINT32 ui32CardNumber, UINT32 ui32Channel)
{

    VOID * l_pDriver;

    l_pDriver = add(ui32CardNumber, FALSE);

    if (l_pDriver != NULL)
    {
        if (0 > m_pMioSystem->piConfigChan(l_pDriver, (SINT32) ui32Channel))
        {
            return NULL;
        }
    }

    return l_pDriver;
}

/**-----------------------------------------------------------------*/
VOID ProcessImage::updateInput()
{
    if (m_ProcessImageHandle == NULL)
    {
        log_Wrn("ProcessImage::m_ProcessImageHandle was NULL in UpdateInput");
    }

    SINT32 l_si32Retcode = m_pMioSystem->piUpdateIn(m_ProcessImageHandle, 100);

    if (l_si32Retcode < 0)
    {
        throw MIOexception("Process Image failed to update input", -1, l_si32Retcode);
    }
}

/**-----------------------------------------------------------------*/
VOID ProcessImage::updateOutput()
{

    SINT32 l_si32Retcode = m_pMioSystem->piUpdateOut(m_ProcessImageHandle, 100);
    if (l_si32Retcode < 0)
    {
        log_Wrn("ProcessImage::updateOutput:: failed to write output.- Returncode %i",
                l_si32Retcode);
        throw MIOexception("Process Image failed to write output", -1, l_si32Retcode);
    }
}

/**-----------------------------------------------------------------*/
VOID ProcessImage::setPriority(UINT32 ui32Priority)
{
    m_ui32Priority = ui32Priority;

    if (0 > m_pMioSystem->piSetPriority(m_ProcessImageHandle, (SINT32) m_ui32Priority))
    {
        log_Err("ProcessImage::setPriority Failed");
    }
}

/**-----------------------------------------------------------------*/
UINT32 ProcessImage::getPriority(void)
{
    return m_ui32Priority;
}

/**********************************************************************
 *
 *
 * 					    STATIC METHODS
 *
 *
 **********************************************************************/

/**-----------------------------------------------------------------*/
VOID ProcessImage::updateInReady(UINT32 ui32UserParameter)
{
    ProcessImage *l_pMioHandler = NULL;
    ProcessImageCallback *l_pCallBack = NULL;

    l_pMioHandler = reinterpret_cast<ProcessImage*>(ui32UserParameter);

    if (l_pMioHandler == NULL)
    {
        return;
    }

    l_pCallBack = l_pMioHandler->getInputCallback();

    if (l_pCallBack != NULL)
    {
        l_pCallBack->updateReady(l_pMioHandler->getInputCallbackParamter());
    }
}

/**-----------------------------------------------------------------*/
VOID ProcessImage::updateOutReady(UINT32 ui32UserParameter)
{

    ProcessImage *l_pMioHandler = NULL;
    ProcessImageCallback *l_pCallBack = NULL;

    l_pMioHandler = reinterpret_cast<ProcessImage*>(ui32UserParameter);

    if (l_pMioHandler == NULL)
    {
        return;
    }

    l_pCallBack = l_pMioHandler->getOutputCallback();

    if (l_pCallBack != NULL)
    {
        l_pCallBack->updateReady(l_pMioHandler->getOutputCallbackParameter());
    }

}

