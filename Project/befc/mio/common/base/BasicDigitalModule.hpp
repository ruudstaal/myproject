/**
 ********************************************************************************
 * @file     BasicDigitalModule.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicDigitalModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CBASICDIGITALMODULE_HPP_
#define CBASICDIGITALMODULE_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicIoModule.hpp"
#include "DigitalChannel.hpp"

/**
 * @brief Base Class of any Digital Module
 */
class BasicDigitalModule: public BasicIoModule
{
    friend class IOStrategy;
    friend class ProcessImageIOStrategy;
    friend class StdIOStrategy;

protected:

    /**
     * @brief default Constructor
     */
    BasicDigitalModule();

    /**
     * @brief Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     */
    explicit BasicDigitalModule(UINT32 ui32CardNumber);

    /**
     * @brief Write Values module
     *
     * Writes all Channels of a Card, psiValues must
     * contain data for all channels!! Module is NOT marked
     * as dirty by calling this function.
     *
     * @param *pb32Value Pointer to value
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValues(SINT32 *pb32Value);

    /**
     * @brief Sets value for channel
     *
     * @param ui32Channel selected Channel
     * @param b8Value value to write
     *
     */
    VOID setValueInternal(UINT32 ui32Channel, BOOL8 b8Value);

    void setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag = FALSE);

    void initInternal();

public:

    /**
     * @brief default Destructor
     */
    virtual ~BasicDigitalModule();

    /**
     * @brief Sets value for channel, and marks the
     * module as "dirty" for upcoming write.
     *
     * @param ui32Channel selected Channel
     * @param b8Value value to write
     *
     */
    VOID setValue(UINT32 ui32Channel, BOOL8 b8Value);

    /**
     * @brief Read Value from Card
     *
     * @param ui32Channel selected Channel
     * @return value of the channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     * or if the pointer to channel class is invalid
     */
    BOOL8 getValue(UINT32 ui32Channel);

    /**
     * @brief Write Values to Card
     *
     * Writes all Channels of a Card, psiValues must
     * contain data for all channels!!
     *
     * @param *pb8Value values to write
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValues(BOOL8 *pb8Value);

    /**
     * @brief Read Values from Card
     *
     * @return the current values as BOOL8 array
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    BOOL8* getValues();

    /**
     * @brief Get one single Channel as Instance
     *
     * @param ui32Channel - Channelnumber (1....x)
     *
     * @returns NULL - Channel not valid
     *          > NULL - Pointer to Instance
     */
    DigitalChannel* getDigitalChannel(UINT32 ui32Channel);

    /**
     * @brief Activate Interruptchannel and attach Listener
     *
     * @param pSession - pointer to Eventsession
     * @param ui32Channel - selected Channel
     * @param pListener - pointer to Listener
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID attachInterrupt(EventSession* pSession, UINT32 ui32Channel, BasicEventListener* pListener =
            NULL);

    BOOL8 isDigitalModule()
    {
        return true;
    }

    BOOL8 isMixedModule()
    {
        return false;
    }

private:

    /**
     * @brief Override Method from Baseclass
     *
     * create Instances of DigitalChannel
     *
     */
    virtual VOID createChannels(VOID);

    BOOL8 *m_pValues;

};

#endif /** CBASICDIGITALMODULE_HPP_ */
