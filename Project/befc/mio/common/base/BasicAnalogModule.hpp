/**
 ********************************************************************************
 * @file     BasicAnalogModule.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicAnalogModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CBASICANALOGMODULE_HPP_
#define CBASICANALOGMODULE_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicIoModule.hpp"
#include "AnalogChannel.hpp"

/**
 * @brief Base Class of any Analog Module
 */
class BasicAnalogModule: public BasicIoModule
{

    friend class ProcessImageIOStrategy;
    friend class StdIOStrategy;

public:

    /**
     * @brief Constructor
     */
    BasicAnalogModule();

    /**
     * @brief Constructor
     */
    BasicAnalogModule(UINT32 ui32CardNumber, BOOL8 b8CreateChannels = TRUE);

    /**
     * @brief Default Destructor
     */
    virtual ~BasicAnalogModule();

    /**
     * @brief Write Value to Card
     *
     * @param ui32Channel selected Channel
     * @param si32Value value to write
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValue(UINT32 ui32Channel, SINT32 si32Value);

    /**
     * @brief Read Value from Card
     *
     * @param ui32Channel selected Channel
     *
     * @return Value of the channel
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SINT32 getValue(UINT32 ui32Channel);

    /**
     * @brief Write Values to Card
     *
     * Writes all Channels of a Card, psiValues must
     * contain data for all channels!!
     *
     * @param psi32Value values to write
     * @param ui32BufferSize number of values to be written
     *
     * @throws a MIOexception when data can't be read from card,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setValues(SINT32 *psi32Value, UINT32 ui32BufferSize);

    /**
     * @brief Read Values from Card
     *
     * Reads all Channels of a Card, psiValues must be
     * big enough to receive all channels
     *
     * @throws a MIOexception when data can't be read from card,
     * or a MIOexception if pointer to card is invalid
     *
     * @return array pointer to read data,
     * pointer can be deleted with SAFE_DELETE,
     * or left unallocated(Clean up by Destructor).
     */
    SINT32* getValues(VOID);

    /**
     * @brief Get one single Channel as Instance
     *
     * @param ui32Channel - Channelnumber (1....x)
     *
     * @throws a MIOexception when channel list is empty
     * or a MIOexception when channel is not found in the channel list!
     */
    AnalogChannel *getAnalogChannel(UINT32 ui32Channel);

    BOOL8 isDigitalModule()
    {
        return false;
    }

    BOOL8 isMixedModule()
    {
        return false;
    }

protected:
    /**
     ********************************************************************************
     * @brief      				   This function sets the values in the local object.
     * @param[in]  psi32Value      A pointer to the SINT32 array.
     * @param[in]  ui32BufferSize  The size of the buffer
     *******************************************************************************/
    VOID setValuesInternal(SINT32 *psi32Value, UINT32 ui32BufferSize);

    void setValueInternal(UINT32 ui32Channel, SINT32 si32Value, BOOL8 setDirtyflag = FALSE);

    void initInternal(VOID);

private:

    /**
     * @brief Override Method from Baseclass
     *
     * create Instances of AnalogChannel
     *
     */
    virtual VOID createChannels(VOID);
    SINT32 *m_psi32GetValuesBuffer;

};

#endif /** CBASICANALOGMODULE_HPP_ */
