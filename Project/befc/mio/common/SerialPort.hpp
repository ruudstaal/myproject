/**
 ********************************************************************************
 * @file     SerialPort.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SerialPort
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CSERIALPORT_HPP_
#define CSERIALPORT_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "base/BasicEventListener.hpp"

/**
 * @brief Functionality for one serial Port
 *
 */
class SerialPort
{
    /** port number */
    UINT32 m_ui32Port;
    /** card number */
    UINT32 m_ui32Card;
    /**
     * String to request port
     * "/tyCo/card/port"
     */
    CHAR8 m_ch8Port[25];
    /** internal handle */
    int m_iHandle;

    BasicEventListener *m_pListener;

    /** init value for handle */
    static const int INVALID;

public:

    /**
     * @brief default Constructor
     */
    SerialPort();

    /**
     * @brief default Destructor
     */
    virtual ~SerialPort();

    /**
     * @brief Set Cardnumber
     *
     * Cardnumber is needed to adress the correct Port
     *
     * @param ui32CardNumber 0 = CPU \n
     *                       > 0 = Card with ComPort
     *
     */
    VOID setCard(UINT32 ui32CardNumber);

    /**
     * @brief Set Portnumber
     *
     * @param ui32PortNumber Portnumber of selected Card
     *
     */
    VOID setPortNumber(UINT32 ui32PortNumber);

    /**
     * @brief Open Port for communication
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 openPort(VOID);

    /**
     * @brief Close Port
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 closePort(VOID);

    /**
     * @brief Delete Buffer
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 flush(VOID);

    /**
     * @brief Write Value to Port
     *
     * if ui32Size is 0 strlen is used to calculate \n
     * the size of data.
     *
     * @param pch8Data - pointer to Data
     * @param ui32Size - size of Data
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 setValue(CHAR8 *pch8Data, UINT32 ui32Size = 0);

    /**
     * @brief Read Data from Port
     *
     * @param pch8Data  - pointer to Data
     * @param pui32Size - size of Data, returns Size
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 getValue(CHAR8 *pch8Data, UINT32 *pui32Size);

    /**
     * @brief Read how many Bytes are in Buffer
     *
     * @param pui32Bytes - pointer to variable
     *
     * @returns TRUE = success
     * @returns FALSE = failed
     */
    BOOL8 getReceivedBytes(UINT32 *pui32Bytes);

    /**
     * @brief Request if Port is open
     *
     * @returns TRUE  = open
     * @returns FALSE = closed
     */
    BOOL8 isOpen(VOID);

    /************************************************************
     *
     *    Error and Event Interrupts
     *
     ************************************************************/
    /**
     * @brief attach Hookfunction to Serialport and
     *        inform application about incoming data
     *
     * Calls EventOccured of pListener with incoming data
     * as Eventparameter.
     *
     * @param pListener - Listener Object
     *
     * @see BasicEventListener::EventOccured
     *
     * @returns TRUE  = success
     * @returns FALSE =  failed
     *
     */
    BOOL8 attachListener(BasicEventListener *pListener);

private:

    /**
     * @brief Callback Method of Object to access member variables
     *
     * @param ui32Sign - incoming Data
     *                   should be passed to Application
     *                   using the given Listener
     */
    STATUS receivedData(UINT32 ui32Sign);

    /**
     * @brief Static Callback for use as Hook
     *
     * @param ui32Userpara - User Parameter
     *                       contains pointer to SerialPort
     * @param ui32Sign - incoming Data
     *
     * method calls receivedData(...)
     */
    static STATUS callback(UINT32 ui32Userpara, UINT32 ui32Sign);
};

inline BOOL8 SerialPort::isOpen()
{
    return (m_iHandle != INVALID) ? TRUE : FALSE;
}

#endif /** SERIALPORT_HPP_ */
