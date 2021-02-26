/**
 ********************************************************************************
 * @file     RS204.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of serial interface module RS204
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef RS204_HPP_
#define RS204_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicIoModule.hpp"
#include "../../common/SerialPort.hpp"

/**
 * @brief Interface Module for Serial Connection RS204
 *
 * Channels: 4 (RS232/RS422/RS485)
 */
class RS204: public BasicIoModule
{

    /**
     * Instances for each Port one
     */
    SerialPort m_Port[4];

public:

    /**
     * Default Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    RS204();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit RS204(UINT32 ui32CardNumber);

    /**
     * default Destructor
     */
    virtual ~RS204();

    /**
     * Get Instance of single Port
     *
     * @returns pointer to instance
     * @returns NULL = failed
     */
    BOOL8 getPort(UINT8 ui8Portnumber, SerialPort **pPort);

    BOOL8 isDigitalModule()
    {
        return false;
    }

    BOOL8 isMixedModule()
    {
        return false;
    }

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
     * @brief Get Type of Module
     * @see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_RS204;
    }

    void setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag = FALSE)
    {
    }

    void initInternal()
    {
    }

private:

    /**
     * @brief Override Method from Baseclass
     *
     * Implementation of abstract Method
     *
     */
    virtual VOID createChannels(VOID);

};

#endif /** RS204_HPP_ */
