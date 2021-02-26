/**
 ********************************************************************************
 * @file     M1Scan.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of M1Scan
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/**********************************************************************
 * system includes
 **********************************************************************/
#include <string.h>
#include <msys_e.h>
#include <prof_e.h>
#include <stdio.h>
#include <inf.h>
#include <iostream>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "M1Scan.hpp"
#include "ModuleFactory.hpp"
#include "ModuleBuilder.hpp"
#include "BasicMixedModule.hpp"
#include "BasicAnalogModule.hpp"
#include "BasicDigitalModule.hpp"

extern "C" VOID callBack_M1Scan(VOID *DrvId, UINT32 CardNb, UINT32 *pM1Scan)
{
    M1Scan *pScan = reinterpret_cast<M1Scan*>(pM1Scan);
    pScan->addByCardNumber(DrvId, CardNb);
}

/**-----------------------------------------------------------------*/
M1Scan::M1Scan()
{
    pm_CardList = new ModuleMap_t();
    pm_ChannelList = new ChannelMap_t();
    /**
     * trigger system to call callback-method and
     * create list of cards
     */
    (void) mio_WalkCardList((VOID (*)())callBack_M1Scan, this);
}

/**-----------------------------------------------------------------*/
M1Scan::~M1Scan()
{

    //Delete all modules which were created
    ModuleMap_t::iterator p;
    for (p = pm_CardList->begin(); p != pm_CardList->end(); ++p) {
        SAFE_DELETE(p->second);
    }

    //Channels are deleted when modules are deleted
    pm_ChannelList->clear();
    pm_CardList->clear();
    SAFE_DELETE(pm_ChannelList);
    SAFE_DELETE(pm_CardList);
}

/**-----------------------------------------------------------------*/
void M1Scan::addByCardNumber(void* pDriverId, UINT32 ui32Card)
{


    ModuleFactory::M1_MODULE_t CardInfo;

    if (NULL == pDriverId)
    {
        return;
    }
    /** get info about card type and size */
    if (0 == mio_GetCardInf(pDriverId, &CardInfo))
    {
        /** Nothing to be done for these modules */
        if (CardInfo.Type == MIO_T_NT250 || CardInfo.Type == MIO_T_NT255
                || CardInfo.Type == MIO_T_FCS2XX || CardInfo.Type == MIO_T_FM2XX
                || CardInfo.Type == MIO_T_FM2XX || CardInfo.Type == MIO_T_FS2XX
                || CardInfo.Type == MIO_T_FM2XX || CardInfo.Type == MIO_T_MX2XX
                || CardInfo.Type == MIO_T_MP2XX || CardInfo.Type == MIO_T_MPC2XX
                || CardInfo.Type == MIO_T_MC2XX || CardInfo.Type == MIO_T_MH2XX
                || CardInfo.Type == MIO_T_CM202 || CardInfo.Type == MIO_T_EM203
                || CardInfo.Type == MIO_T_RS204 || CardInfo.Type == MIO_T_EM213)
        {
            return;
        }

        try
        {

            /** try to create module */
            BasicIoModule *pModule = pFactory.CreateModule(&CardInfo);

            if (NULL != pModule)
            {
                /** add Module to list of known cards */
                if (pm_CardList->find(ui32Card) == pm_CardList->end())
                {
                    pm_CardList->insert(std::pair<SINT32, BasicIoModule*>(ui32Card, pModule));
                    buildSymbolList(pModule);
                }
                else
                {
                    log_Wrn("M1Scan::callback : duplicate Card %d", ui32Card);
                }
            }
            else
            {
                log_Wrn("M1Scan::callback : failed to add Card %d of type %d", ui32Card, CardInfo.Type);
            }
        }
        catch(MIOexception &ex)
        {
            log_Wrn("M1Scan::callback : failed to add Card %d due to : %s", ui32Card, ex.what());
        }
    }
    else
    {
        log_Wrn("M1Scan::callback : failed to get CardInfo for Card %d", ui32Card);
    }
}

/**-----------------------------------------------------------------*/

/**-----------------------------------------------------------------*/
UINT16 M1Scan::getCardCounter(VOID)
{
    return (UINT16)pm_CardList->size();
}

/**-----------------------------------------------------------------*/
BasicIoModule* M1Scan::getCard(SINT32 si32CardNumber)
{
    M1Scan::ModuleMap_t::iterator it;

    it = pm_CardList->find(si32CardNumber);
    if (it != pm_CardList->end())
    {
        return it->second;
    }

    return NULL;
}

/**-----------------------------------------------------------------*/
BasicChannel* M1Scan::getChannel(std::string strChannelName)
{
    M1Scan::ChannelMap_t::iterator it;

    it = pm_ChannelList->find(strChannelName);
    if (it != pm_ChannelList->end())
    {
        return it->second;
    }

    return NULL;
}

/**-----------------------------------------------------------------*/
M1Scan::ModuleMap_t* M1Scan::getCardList()
{
    return pm_CardList;
}

/**-----------------------------------------------------------------*/
void M1Scan::buildSymbolList(BasicIoModule *pModule)
{
    UINT32 l_ui32Channel = 1;
    CHAR l_Card[9];
    CHAR l_ChannelName[20];
    CHAR l_buffer[80];
    std::string l_strChannelName;

    BasicIoModule::SInfo_t *Info;
    BasicChannel *l_pBasicChannel = NULL;
    BasicAnalogModule *l_pAnalogModule = NULL;
    BasicDigitalModule *l_pDigitalModule = NULL;
    BasicMixedModule *l_pMixedModule = NULL;

    if (0 == pModule)
    {
        return;
    }

    /** set structure to 0 */
    memset(&Info, 0, sizeof(Info));

    Info = pModule->getInfo();
    /**
     * which kind of module we have here ?
     * if Base-class is wrong we get a NULL-Pointer
     */
    if (pModule->isDigitalModule())
    {
        l_pDigitalModule = dynamic_cast<BasicDigitalModule*>(pModule);
    }
    else if (pModule->isMixedModule())
    {
        l_pMixedModule = dynamic_cast<BasicMixedModule*>(pModule);
    }
    else
    {
        l_pAnalogModule = dynamic_cast<BasicAnalogModule*>(pModule);
    }

    memset(l_Card, 0, sizeof(l_Card));
    sprintf(l_Card, "Card%d", Info->CardNb);

    /**
     * search for all possible Channel entries
     */
    for (l_ui32Channel = 1; l_ui32Channel <= Info->MaxChan; ++l_ui32Channel)
    {
        memset(l_ChannelName, 0, sizeof(l_ChannelName));
        memset(l_buffer, 0, sizeof(l_buffer));

        sprintf(l_ChannelName, "ChanName%d", l_ui32Channel);

        //Done to avoid warnings (const char to char conversion - pf functions take char arrays, not const char arrays)
        char section[sizeof(PF_S_DRIVERS)];
        strncpy(section, PF_S_DRIVERS, sizeof(PF_S_DRIVERS));
        char empty[] = "";

        /**
         * search MConfig for String ChanName1 - ChanNameXY
         * and copy into buffer
         */
        if (0 < pf_GetStrg(section, l_Card, l_ChannelName, empty, l_buffer, 80, 0, NULL))
        {
            /**
             * Test if a symbolic Name  is configured and add
             * it to static list of Channels.
             */
            if (0 < strlen(l_buffer))
            {
                l_pBasicChannel = NULL;

                l_strChannelName.clear();
                l_strChannelName = l_buffer;

                if (pModule->isDigitalModule())
                {
                    l_pBasicChannel = l_pDigitalModule->getDigitalChannel(l_ui32Channel);
                }
                else
                {
                    if (pModule->isMixedModule())
                    {
                        l_pBasicChannel = l_pMixedModule->getChannel(l_ui32Channel);
                    }
                    else
                    {
                        l_pBasicChannel = l_pAnalogModule->getAnalogChannel(l_ui32Channel);
                    }
                }

                if (NULL != l_pBasicChannel)
                {

                    pm_ChannelList->insert(
                            std::pair<std::string, BasicChannel*>(l_strChannelName,
                                    l_pBasicChannel));
                }
                else
                {
                    log_Err("M1Scan::buildSymbolList: Channel %d not found!", l_ui32Channel);
                }
            }
        }
    }
}
