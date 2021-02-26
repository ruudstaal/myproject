/**
 ********************************************************************************
 * @file     BasicChannel.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef BASICCHANNEL_HPP_
#define BASICCHANNEL_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicIoModule.hpp"



/**********************************************************************
 * forward declaration
 **********************************************************************/
class BasicIoModule;

/**
 * @brief Baseclass of a Channel of an IO-Module
 */
class BasicChannel
{

protected:
	/** channel number */
    UINT32              			m_ui32Channel;
    /** related IO-Module */
    BasicIoModule					*m_pModule;
    /** errors from mio-functions are stored here */
    SINT32              			m_si32Error;

public:

    typedef MIO_CHANINF SInfo_t;

    /**
     * @brief Constructor
     */
    BasicChannel();

    /**
     * @brief Destructor
     */
    virtual ~BasicChannel();

    virtual BOOL8 isDigitalChannel() = 0;

    /**
     * @brief Set Number of Channel
     *
     * @param ui32Channel - Channel of IO Module
     */
    VOID setChannelNumber(UINT32 ui32Channel);

    /**
     * @brief get Number of Channel
     *
     * @returns Channel of IO Module
     */
    UINT32 getChannelNumber(VOID);

    /**
     * @brief set Pointer to Module
     *
     * @param pModule - Pointer to DriverId
     */
    VOID setParentModule(BasicIoModule* pModule);

    /**
     * @brief get last error of MIO Interface
     *
     * @returns 0 - OK
     *          < 0 - MIO-Error see MIO_E_XXX
     */
    SINT32 getMioError(VOID);

     /**
     * @brief Set Mode of Channel
     *
     * @param ui32Value - Value to Set
     *
     * @throws a MIOexception when setting channel mode fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setMode(UINT32 ui32Value);

    /**
     * @brief Get Mode of Channel
     *
     * @return Channel mode
     *
     * @throws a MIOexception when getting channel mode fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @return channel mode.
     *
     */
    UINT32 getMode(VOID);

    /**
     * @brief Get Infostructure of Channel
     *
     * @return pointer to channel info
     *
     * @throws a MIOexception when getting channel info fails,
     * or a MIOexception if pointer to card is invalid
     *
     * @return Pointer to Channel info structure.
     */
    virtual BasicChannel::SInfo_t* getInfo(VOID);

    /**
     * @brief Activate/Deactivate Channel
     *
     * @param b8Active - TRUE = activate
     *                   FALSE = deactivate
     *
     * @throws a MIOexception when setting active information to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setActive(BOOL8 b8Active);

    /**
    * @brief Read format of value from Channel
    *        This call only apply to UFB channels
    *
    * @return format value of channel
    *
    * @throws a MIOexception when reading from card fails,
    * or a MIOexception if pointer to card is invalid
    *
    * @return channel format
    */
    UINT32 getFormat();

protected:

    /**
    * @brief Write Value to Card
    *
    * @param si32Value value to write
    *
    * @throws a MIOexception when writing to card fails,
    * or a MIOexception if pointer to card is invalid
    */
    VOID setBasicValue(SINT32 si32Value);

    /**
    * @brief Read Value from Channel
    *
    * @return Value of channel
    *
    * @throws a MIOexception when reading from card fails,
    * or a MIOexception if pointer to card is invalid
    *
    * @return channel value
    */
    SINT32 getBasicValue();

private:
    BasicChannel::SInfo_t m_SInfo;
    SINT32 m_si32GetValue;
    MIO_CHAN_RANGE chanRange;

};

#endif /** BASICCHANNEL_HPP_ */
