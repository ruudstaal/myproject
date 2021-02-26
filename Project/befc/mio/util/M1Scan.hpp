/**
 ********************************************************************************
 * @file     M1Scan.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of M1Scan
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef CM1SCAN_HPP_
#define CM1SCAN_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>
#include <mio_e.h>
#include <log_e.h>
#include <map>
#include <string>
#include "ModuleFactory.hpp"

/**********************************************************************
 * project includes
 **********************************************************************/
class BasicChannel;

class BasicIoModule;

/**
 *@brief  Receives Information about all available
 *        HW-Modules
 *
 * \note SINGLETON-Class Implementation
 *
 * \code {cpp}
 *

 UINT32 l_ui32Value = 3276;

 DigitalChannel *pOut  = NULL;
 AnalogChannel  *pAOut = NULL;
 AnalogChannel  *pAIn  = NULL;

 UINT32 ui32Cards = M1Scan::Instance()->getCardCounter();
 log_Info("found %d Modules", ui32Cards);

 pOut  = dynamic_cast<DigitalChannel*>(M1Scan::Instance()->getChannel("Kanal_2"));
 pAOut = dynamic_cast<AnalogChannel*>(M1Scan::Instance()->getChannel("Kanal_11"));
 pAIn  = dynamic_cast<AnalogChannel*>(M1Scan::Instance()->getChannel("Kanal_12"));

 if (NULL != pOut)
 {
 pOut->setValue(TRUE);
 }

 if (NULL != pAIn)
 {
 pAIn->getValue(&l_ui32Value);

 l_ui32Value += 3276;
 }

 if (NULL != pAOut)
 {
 pAOut->setValue(l_ui32Value);
 }



 *
 * \endcode
 */
class M1Scan
{

public:

    /**
     * List of IO-Channels
     * contains Name of Channel and Pointer to Channelclass
     */
    typedef std::map<std::string, BasicChannel*> ChannelMap_t;

    /**
     * Map of Modules
     * contains Modulenumber and Pointer to Moduleclass
     */
    typedef std::map<SINT32, BasicIoModule*> ModuleMap_t;

private:
    /**
     * List of call possible cards
     */
    ModuleMap_t *pm_CardList;

    /**
     * List of all symbolic names
     */
    ChannelMap_t *pm_ChannelList;

    ModuleFactory pFactory;

public:
    /**
     * Default Constructor
     */
    M1Scan();

    /**
     * Default Destructor
     */
    virtual ~M1Scan();

    /**
     * read number of available Modules
     */
    UINT16 getCardCounter(VOID);

    /**
     * @brief get pointer to specified Card
     *
     * \code {cpp}
     *
     * DI232 *pModule  = NULL;
     *
     * pModule  = dynamic_cast<DI232*>(M1Scan::Instance()->getCard(23));
     *
     * \endcode
     *
     * @param si32CardNumber Cardnumber from MConfig
     *
     * @returns pointer to Module as Baseclass-pointer
     */
    BasicIoModule* getCard(SINT32 si32CardNumber);

    /**
     * @brief get pointer to specified Card
     *
     * Sample for a digital output
     * \code {cpp}
     *
     * DigitalChannel *pOut  = NULL;
     *
     * pOut  = dynamic_cast<DigitalChannel*>(M1Scan::Instance()->getChannel("Kanal_2"));
     *
     * if (pOut != NULL)
     * {
     *     pOut->setValue(TRUE);
     * }
     *
     *
     * \endcode
     *
     * @param strChannelname Symbolic Name from MConfig
     * @returns pointer to DigitalChannel or AnalogChannel
     *
     */
    BasicChannel* getChannel(std::string strChannelname);

    /**
     * get copy of Card List
     *
     * @return ModuleMap_t* - pointer to ModuleMap_t
     */
    ModuleMap_t* getCardList();

    /**
     * callback method for walkCardList
     *
     * @param pDriverId - Driver Identifier
     * @param ui32Card - Card Number
     *
     */
    void addByCardNumber(VOID *pDriverId, UINT32 ui32Card);

private:

    /**
     * method to create List of channels with symbolic names
     *
     * The given Module is searched in MConfig and all configured
     * Symbolic Channelnames a added to sm_ChannelList
     *
     * @param pModule - pointer to Module to search in Mconfig
     */
    void buildSymbolList(BasicIoModule *pModule);

    M1Scan(const M1Scan& that); /** no copy */
    M1Scan& operator=(M1Scan const&); /** no assign */
};

#endif /** M1SCAN_HPP_ */
