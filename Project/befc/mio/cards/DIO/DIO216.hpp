/**
 ********************************************************************************
 * @file     DIO216.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of digital input and output module DIO216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef DIO216_HPP_
#define DIO216_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicDigitalModule.hpp"

/**
 * @brief Digital Input/Output Module DIO216
 */
class DIO216: public BasicDigitalModule
{
public:

    /** Channelmodes */
    static const UINT32 MODE_POSEDGE;
    static const UINT32 MODE_NEGEDGE;
    static const UINT32 MODE_BOTHEDGES;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    DIO216();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit DIO216(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~DIO216();

    /*************************************************************
     *
     *    Error and Event Interrupts
     *
     *************************************************************/
    /**
     * Attach to Power Fail Interrupt
     *
     * @param pSession - Error Session from System
     * @param pListener - Object which contains callback method
     *
     * @throws a MIOexception when attaching event to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachPowerFail(ErrorSession *pSession, BasicErrorListener *pListener = NULL);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_DIO216;
    }
};

#endif /** DIO216_HPP_ */
