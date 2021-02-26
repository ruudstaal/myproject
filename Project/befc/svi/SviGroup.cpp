/**
 ********************************************************************************
 * @file     SviGroup.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviGroup
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <svi_e.h>
#include <res_e.h>

#include "mcpp.hpp"
#include "LocalSviItem.hpp"
#include "SviGroup.hpp"

#include "BEModule.hpp"
#include "SviException.hpp"
#include "SviItemModuleWrapper.hpp"
#include "value/ValueFactory.hpp"
#include "ListReadStrategyImpl.hpp"
#include "SingleItemReadStrategyImpl.hpp"
#include "M1SviSystem.hpp"
#include "ModuleException.hpp"

SviGroup::SviGroup(std::string name, BETask* pTask) :
        name(name), initialized(false), active(false), pTask(pTask), pSviSystem(new M1SviSystem())
{
    pMap = new TStrWrapMap();
    this->itemStrategy = new ListReadStrategyImpl(pSviSystem);
}

SviGroup::SviGroup() :
        initialized(false), active(false), pTask(NULL), pMap(NULL), itemStrategy(NULL), pSviSystem(
                new M1SviSystem())
{
}

std::string SviGroup::getName()
{
    return this->name;
}

SviGroup::~SviGroup()
{
    TStrWrapMap::iterator p;
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        SAFE_DELETE(p->second);
    }
    pMap->clear();
    SAFE_DELETE(pMap);
    SAFE_DELETE(this->itemStrategy);
    SAFE_DELETE(pSviSystem);
}

VOID SviGroup::init(void)
{

    if (initialized)
    {
        return;
    }

    /** We cannot initialize SVI variables unless device is in EOI or RUN state. */
    if (pTask->getModule()->getModState() != *BEModuleState::STATE_EOI
            && pTask->getModule()->getModState() != *BEModuleState::STATE_RUN)
    {
        throw SviException("Module state is NOT EOI or RUN - Cannot initialize SVI");
    }

    TStrWrapMap::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    SviItemModuleWrapper *pWrap;
    std::vector<AbstractSviItem*>* pItems;

    bool listStrat = dynamic_cast<ListReadStrategyImpl*>(this->itemStrategy) != NULL;
    /** Go through all modules and get addresses for module and pItems */
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        try
        {
            pWrap = p->second;
            pWrap->setLib(this->pTask->getModule()->getLibAddress(p->first));

            pItems = pWrap->getItems();
            /** Go through all pItems and get address and format */

            bool updatedPLib = false;
            for (ite = pItems->begin(); ite != pItems->end(); ++ite)
            {
                try
                {
                    //If items failed due to old address, we need also to reinitialize the plib.
                    if ((*ite)->getError() == SVI_E_OLDADDR)
                    {
                        if (updatedPLib == false)
                        {
                            pWrap->setLib(this->pTask->getModule()->renewLibAddress(p->first));
                            updatedPLib = true;
                        }
                    }
                    else if ((*ite)->isFailed())
                    {
                        continue;
                    }

                    /** Initialize the single item (svi_GetAddr) */
                    initializeItem((*ite), pWrap->getLib());

                    if ((*ite)->isArrayItem() && listStrat)
                    {
                        SAFE_DELETE(this->itemStrategy);
                        this->itemStrategy = new SingleItemStrategyImpl(this->pSviSystem);
                        listStrat = false;
                    }
                }
                catch (SviException const& svie)
                {
                    logException(svie);
                }
            }
        }
        catch (ModuleException &ex)
        {
            //If software module does not exist, getting the lib will throw exception.
        }
    }
    initialized = isInitialized();
    if (initialized)
    {
        setState(SviGroupEventListener::ONLINE);
    }
}

pLib SviGroup::getLibAddress(std::string moduleName)
{
    return this->pTask->getModule()->getLibAddress(moduleName);
}

pLib SviGroup::renewLibAddress(std::string moduleName)
{
    return this->pTask->getModule()->renewLibAddress(moduleName);
}

void SviGroup::initializeItem(AbstractSviItem *pItem, pLib pLib)
{
    SVI_ADDR valueAddr;
    UINT32 format = SVI_F_EXTLEN;
    SINT32 res;
    try
    {
        res = pSviSystem->GetAddr(pLib, (CHAR*) pItem->getVarName().c_str(), &valueAddr, &format);
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "SystemException while getting address for " << pItem->getVarName() << std::endl;
        throw SviException(ss.str());
    }

    if (res == SVI_E_OK)
    {
        pItem->initialize(valueAddr, format, pLib);

        bool listStrat = dynamic_cast<ListReadStrategyImpl*>(this->itemStrategy) != NULL;
        if (pItem->isArrayItem() && listStrat)
        { //Force reading single values - one call pr item.
            SAFE_DELETE(this->itemStrategy);
            this->itemStrategy = new SingleItemStrategyImpl(this->pSviSystem);
            log_Info(
                    "SVI Group %s : Switched to single update strategy - performance will decrease. Group by 32 bit values when possible",
                    this->getName().c_str());
        }
    }
    else
    {
        pItem->initialize(res);
        notifyAboutItemFailed(res, pItem);
    }
}

VOID SviGroup::logException(std::exception const& e)
{
    info(e.what());
}

VOID SviGroup::log(std::stringstream *pStream)
{
    info(pStream);
}

std::vector<AbstractSviItem*> SviGroup::getItems()
{
    std::vector<AbstractSviItem*> result;
    TStrWrapMap::iterator p;
    std::vector<AbstractSviItem*> *pVector;
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        pVector = p->second->getItems();
        result.insert(result.end(), pVector->begin(), pVector->end());
    }
    return result;
}

bool SviGroup::addItem(AbstractSviItem* pSviItem)
{
    TStrWrapMap::iterator p;
    BOOL8 bFound = FALSE;
    SviItemModuleWrapper *wrap;

    if (this->active)
    {
        return false;
    }

    /** Go through module list to see if one exists already for item to add. */
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        if (0 == pSviItem->getModuleName().compare(p->first))
        {
            wrap = p->second;

            /** Create new item vector */
            if (initialized)
            {
                /** Lists are already initialized.. Initialize right away */
                initializeItem(pSviItem, wrap->getLib());
            }

            /** Add item to vector */
            wrap->getItems()->push_back(pSviItem);
            bFound = true;
            break;
        }
    }
    /** If not found we should create the module instance */
    if (!bFound)
    {

        /** Create new wrapper with vector and insert the item there */
        SviItemModuleWrapper *wrap = new SviItemModuleWrapper();

        if (initialized)
        {
            /** Lists are already initialized.. Initialize right away */
            pLib lib = getLibAddress(p->first);
            initializeItem(pSviItem, lib);
            wrap->setLib(lib);
        }

        std::vector<AbstractSviItem*> *itemvector = new std::vector<AbstractSviItem*>();
        itemvector->push_back(pSviItem);
        wrap->setItems(itemvector);
        pMap->insert(
                std::pair<std::string, SviItemModuleWrapper*>(pSviItem->getModuleName(), wrap));
    }

    return true;
}

bool SviGroup::removeItem(AbstractSviItem* pSviItem)
{
    std::string modulename = pSviItem->getModuleName();
    TStrWrapMap::iterator p;

    SviItemModuleWrapper *wrap;
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        if (p->first == modulename)
        {
            wrap = p->second;
            break;
        }
    }

    if (wrap == NULL)
    {
        return false;
    }

    std::vector<AbstractSviItem*> *pItemList = wrap->getItems();
    std::vector<AbstractSviItem*>::iterator ite;
    for (ite = pItemList->begin(); ite != pItemList->end(); ++ite)
    {
        if ((*ite)->getVarName() == pSviItem->getVarName())
        {
            pItemList->erase(ite);
            return true;
        }
    }
    return false;
}

void SviGroup::setActive(bool active)
{
    this->active = active;
    if (initialized)
    {
        setState(active ? SviGroupEventListener::ONLINE : SviGroupEventListener::OFFLINE);
    }
    else
    {
        if (active == false)
        {
            setState(SviGroupEventListener::OFFLINE); //We do not handle active = true if not initialized
        }
    }
}

bool SviGroup::isActive()
{
    return this->active;
}

void SviGroup::updateOut()
{
    try
    {
        if (initialized)
        {
            notifyFailList(this->itemStrategy->writeValues(this));
        }
    }
    catch (SviException &ex)
    {
        log_Err("Detected errors when doing update out on group %s. (%s)", this->name.c_str(),
                ex.what());
        setActive(false);
        initialized = false;
    }
}

bool SviGroup::isInitialized()
{
    TStrWrapMap::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    SviItemModuleWrapper *pWrap;
    std::vector<AbstractSviItem*>* pItems;

    /** Go through all modules and get addresses for module and pItems */
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        pWrap = p->second;
        pItems = pWrap->getItems();
        /** Go through all pItems and get address and format */
        for (ite = pItems->begin(); ite != pItems->end(); ++ite)
        {
            if ((*ite)->isFailed())
            {
                continue; //Failed items is considered as initialized
            }

            if ((*ite)->isInitialized() == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool SviGroup::hasValidItems()
{
    TStrWrapMap::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    std::vector<AbstractSviItem*>* pItems;
    SviItemModuleWrapper *pWrap;

    /** Go through all modules and get addresses for module and pItems */
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        pWrap = p->second;
        pItems = pWrap->getItems();
        /** Go through all pItems and get address and format */
        for (ite = pItems->begin(); ite != pItems->end(); ++ite)
        {
            if ((*ite)->isFailed() == false && (*ite)->isInitialized() == true)
            {
                return true;
            }
        }
    }
    return false;
}

void SviGroup::refresh(void)
{
    if (initialized == false)
    {
        if (pTask->getDebugMode() == APP_DBG_SVI1)
        {
            warn("Init not called before refresh. Calling Init()");
        }
        init();

        if (hasValidItems() == false)
        {
            setActive(false);
            log_Wrn("No valid items exists in group %s - group is set inactive",
                    this->name.c_str());
            return;
        }
    }

    try
    {
        TFailList errList = this->itemStrategy->readValues(this);
        notifyFailList(errList);

        if (errList.empty())
        {
            notifyAboutGroupRefresh();
        }
        else
        {
            initialized = isInitialized();
            if (initialized == false)
            {
                setState(SviGroupEventListener::OFFLINE);
            }
            log_Info("Initialized set to %u", initialized);
        }

    }
    catch (SviException &ex)
    {
        log_Err("Detected errors when refreshing value for group %s. (%s)", this->name.c_str(),
                ex.what());
        setActive(false);
        initialized = false;
        setState(SviGroupEventListener::ERR);
    }

}

void SviGroup::reset()
{

    TStrWrapMap::iterator p;
    std::vector<AbstractSviItem*>::iterator ite;
    SviItemModuleWrapper *pWrap;
    std::vector<AbstractSviItem*>* pItems;
    for (p = pMap->begin(); p != pMap->end(); ++p)
    {
        pWrap = p->second;
        pWrap->setLib(this->pTask->getModule()->getLibAddress(p->first));
        pItems = pWrap->getItems();
        for (ite = pItems->begin(); ite != pItems->end(); ++ite)
        {
            (*ite)->reset();
        }
    }
}

void SviGroup::setSviSystem(SviSystem *pSystem)
{
    if (this->pSviSystem != NULL)
    {
        SAFE_DELETE(pSviSystem);
    }

    this->pSviSystem = pSystem;

    if (dynamic_cast<SingleItemStrategyImpl*>(this->itemStrategy) != NULL)
    {
        SAFE_DELETE(this->itemStrategy);
        this->itemStrategy = new SingleItemStrategyImpl(this->pSviSystem);
    }
    else if (dynamic_cast<ListReadStrategyImpl*>(this->itemStrategy) != NULL)
    {
        SAFE_DELETE(this->itemStrategy);
        this->itemStrategy = new ListReadStrategyImpl(this->pSviSystem);
    }
}
