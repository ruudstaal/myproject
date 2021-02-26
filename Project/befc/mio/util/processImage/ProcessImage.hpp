/**
 ********************************************************************************
 * @file     ProcessImage.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProcessImage
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef ProcessImage_HPP_
#define ProcessImage_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>
#include <mio_e.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "ProcessImageCallback.hpp"
#include "../../common/base/BasicIoModule.hpp"
#include "../../configuration/MIOConfiguration.hpp"
#include "M1MIOSystem.hpp"

class BasicIoModule;
class MIOConfiguration;

/**
 * @brief Class for ProcessImage Mode
 *
 * \note Only for use in MH/MC-Cpu!
 *
 */
class ProcessImage
{

private:

    /**
     * optional Callback Interfaces
     */
    ProcessImageCallback *m_pCallBackInputReady;
    ProcessImageCallback *m_pCallBackOutputReady;

    /**
     * optional UserParameter
     */
    UINT32 m_ui32ParameterInput;
    UINT32 m_ui32ParameterOutput;

    /**
     * Parent Softwaremodule
     */
    CHAR m_ModuleName[M_MODNAMELEN_A];

    /**
     * internal handle
     * is used to organize different List
     * of cards in Processimage
     *
     */
    MIO_PIHANDLE m_ProcessImageHandle;

    /**
     * Initalize Instance
     */
    void init();

    /**
     * Initalize variables
     */
    void initvalues();

    /**
     * @brief add a card to Processimage
     *
     * @param ui32CardNumber - Number of Card
     * @param b8AllChannels - TRUE = add all channels
     * 					      FALSE = add not all channels
     *
     * @returns > NULL - pointer to driver data
     * 			  NULL - failed (card not found)
     */
    VOID *add(UINT32 ui32CardNumber, BOOL8 b8AllChannels);

    /**
     * @brief Callback Methods when Update Inputs is ready
     *
     * @param ui32UserParameter - optional parameter
     */
    static VOID updateInReady(UINT32 ui32UserParameter);

    /**
     * @brief Callback Method when Update Outputs is ready
     *
     * @param ui32UserParameter - optional parameter
     */
    static VOID updateOutReady(UINT32 ui32UserParameter);

protected:

    /**
     * Priority of Processimage
     */
    UINT32 m_ui32Priority;

    /**
     * Desired MIOSystem
     */
    MIOSystem *m_pMioSystem;

public:

    /**
     * @brief Default Constructor
     */
    ProcessImage();

    /**
     * @brief Constructor
     */
    explicit ProcessImage(CHAR* pModuleName);


    /**
     * @brief Constructor
     */
    explicit ProcessImage(CHAR* pModuleName, M1MIOSystem *pSystem);

    /**
     * @brief Destructor
     */
    virtual ~ProcessImage();

    /**
     * @brief Is ProcessImage Ready to Use
     *
     * @returns TRUE = Process Image ready
     * @returns FALSE = Process Image not ready
     */
    BOOL8 isReady(void) const
    {
        return m_ProcessImageHandle == NULL ? false : true;
    }
    ;

    /**
     * @brief Trigger Process Image to update Inputs
     */
    VOID updateInput();

    /**
     * @brief Trigger Process Image to update Outputs
     */
    VOID updateOutput();

    /**
     * @brief Set Priority of ProcessImage update
     *
     * @param ui32Priority - Priority of update
     */
    VOID setPriority(UINT32 ui32Priority);

    /**
     * @brief Get Priority of ProcessImage update
     */
    UINT32 getPriority(VOID);

    /**
     * @brief get Callback Handler for Outputs
     *
     * @returns > NULL - pointer to Instance
     * @returns = NULL - no Handler defined
     *
     */
    ProcessImageCallback *getInputCallback()
    {
        return m_pCallBackInputReady;
    }

    /**
     * get Callback Handler for Outputs
     *
     * @returns > NULL - pointer to Instance
     * @returns = NULL - no Handler defined
     *
     */
    ProcessImageCallback *getOutputCallback()
    {
        return m_pCallBackOutputReady;
    }

    /**
     * get Callback Handler for Outputs
     *
     * @returns Value for Parameter
     *
     */
    UINT32 getInputCallbackParamter()
    {
        return m_ui32ParameterInput;
    }

    /**
     * get Parameter for Callback Handler for Outputs
     *
     * @returns Value for Parameter
     *
     */
    UINT32 getOutputCallbackParameter()
    {
        return m_ui32ParameterOutput;
    }

    /**
     * @brief add a card to Processimage
     *
     * @param ui32CardNumber - Number of Card
     *
     * @returns > NULL - pointer to driver data
     * @returns  NULL - failed (card not found)
     */
    VOID *addCard(UINT32 ui32CardNumber);

    /**
     * @brief add a card to Processimage
     *
     * @param pModule - pointer to instance of Module
     *
     * @returns > NULL - pointer to driver data
     * @returns  NULL - failed (card not found)
     */
    VOID *addCard(BasicIoModule *pModule);

    /**
     * @brief add a single channel to Processimage
     *
     * @param ui32CardNumber - Number of Card
     * @param ui32Channel - TRUE = add all channels
     * 					 FALSE = add not all channels
     *
     * @returns > NULL - pointer to driver data
     * @returns   NULL - failed (card not found)
     */
    VOID *addChannel(UINT32 ui32CardNumber, UINT32 ui32Channel);

};

#endif /** ProcessImage_HPP_ */
