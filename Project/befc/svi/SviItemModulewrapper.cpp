/**
 ********************************************************************************
 * @file     SviItemModulewrapper.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SviItemModulewrapper
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <stdexcept>
#include "SviItemModuleWrapper.hpp"
#include "mcpp.hpp"

SviItemModuleWrapper::SviItemModuleWrapper() :
        pItems(NULL), lib(NULL)
{
}

SviItemModuleWrapper::~SviItemModuleWrapper()
{
    std::vector<AbstractSviItem*>::iterator it;
    for (it = pItems->begin(); it != pItems->end(); ++it)
    {
        SAFE_DELETE(*it);
    }
    pItems->clear();
    SAFE_DELETE(pItems);
}

VOID SviItemModuleWrapper::setLib(pLib pLib)
{
    if (pLib == NULL)
    {
        throw std::invalid_argument("Pointer to library cannot be NULL");
    }
    this->lib = pLib;
}

VOID SviItemModuleWrapper::setItems(std::vector<AbstractSviItem*> *pItems)
{
    if (pItems == NULL)
    {
        throw std::invalid_argument("Pointer to Svi items cannot be NULL");
    }
    this->pItems = pItems;
}
