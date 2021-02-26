/**
 ********************************************************************************
 * @file     ListReadStrategyImpl.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ListReadStrategyImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "ListReadStrategyImpl.hpp"
#include "SviExportDescriptor.hpp"
#include "value/ValueFactory.hpp"
#include "SviException.hpp"
#include "SviSystemException.hpp"
#include <SviGroup.hpp>
#include "M1SviSystem.hpp"


ListReadStrategyImpl::ListReadStrategyImpl(SviSystem *pSystem) : pSystem(pSystem){
}

TFailList ListReadStrategyImpl::writeValues(AbstractSviGroup *pSviGroup) {
    const int MAXITEMSINCALL = 64;
        SviGroup* pGroup = dynamic_cast<SviGroup*>(pSviGroup);

        if(pGroup == NULL) {
            log_Err("ListReadStrategyImpl used for group other than local controller. Group %s not refreshed", pSviGroup->getName().c_str());
            return TFailList();
        }

        TStrWrapMap::iterator p;

        /** Go through all modules and read variables */
        std::vector<AbstractSviItem*>::iterator ite;
        std::vector<AbstractSviItem*> *pVector;
        int i = 0;

        UINT32 vals[MAXITEMSINCALL];
        SVI_ADDR addresses[MAXITEMSINCALL];

        for (p = pGroup->pMap->begin(); p != pGroup->pMap->end(); ++p)
        {
            pVector = p->second->getItems();
            if (pVector->size() == 0)
            {
                continue;
            }
            i = 0;

            for (ite = pVector->begin(); ite != pVector->end(); ++ite)
            {
                if ((*ite)->isArrayItem())
                {
                    throw SviException("Array datatype not allowed in ListRead strategy");
                }

                if ((*ite)->isInitialized() && (*ite)->isWriteable()) /** Only add initialized (and writable) variables to the update list */
                {
                    addresses[i] = (*ite)->getSviAddr();
                    vals[i] = *(UINT32*) (*ite)->getValueAddress();
                    i++;
                    if (i == MAXITEMSINCALL)
                    {
                        i = 0;
                        SINT32 res = pSystem->SetValLst(p->second->getLib(), addresses, vals, MAXITEMSINCALL);
                        if(res != SVI_E_OK){
                            throw SviSystemException("Could not set SVI values", res);
                        }
                    }
                }
            }
            /** Read the mod 64 remaining items */
            if (i > 0)
            {
                SINT32 res = pSystem->SetValLst(p->second->getLib(), addresses, vals, i);
                if (res != SVI_E_OK)
                {
                    throw SviSystemException("Could not set SVI values", res);
                }
                i = 0;
            }
        }
        return TFailList(); //Cannot say for which ones failed
}

TFailList ListReadStrategyImpl::readValues(AbstractSviGroup *pSviGroup)
{
    const int MAXITEMSINCALL = 64;
    SviGroup* pGroup = dynamic_cast<SviGroup*>(pSviGroup);

    if(pGroup == NULL) {
        log_Err("ListReadStrategyImpl used for group other than local controller. Group %s not refreshed", pSviGroup->getName().c_str());
        return TFailList();
    }

    TStrWrapMap::iterator p;

    /** Go through all modules and read variables */
    std::vector<AbstractSviItem*>::iterator ite;
    std::vector<AbstractSviItem*> *pVector;
    int i = 0;

    AbstractSviItem* items[MAXITEMSINCALL];
    SVI_ADDR addresses[MAXITEMSINCALL];

    for (p = pGroup->pMap->begin(); p != pGroup->pMap->end(); ++p)
    {
        pVector = p->second->getItems();
        if (pVector->size() == 0)
        {
            continue;
        }
        i = 0;

        for (ite = pVector->begin(); ite != pVector->end(); ++ite)
        {
            if((*ite)->isInitialized() == false) {
                continue;
            }

            if ((*ite)->isArrayItem())
            {
                throw SviException("Array datatype not allowed in ListRead strategy");
            }
    
            if ((*ite)->isInitialized()) /** Only add initialized variables to the update list */
            {
                addresses[i] = (*ite)->getSviAddr();
                items[i] = (*ite);
                i++;
                if (i == MAXITEMSINCALL)
                {
                    i = 0;
                    fillValuesInternal(p->second->getLib(), addresses, items, MAXITEMSINCALL);

                    /** Exception might be thrown. */
                }
            }
        }
        /** Read the mod 64 remaining items */
        if (i > 0)
        {
            fillValuesInternal(p->second->getLib(), addresses, items, i);
            /** Exception might be thrown. */
            i = 0;
        }
    }
    return TFailList(); //Cannot say for which ones failed
}

void ListReadStrategyImpl::fillValuesInternal(pLib lib, SVI_ADDR addresses[], AbstractSviItem* pItems[], int size)
{
    UINT32 Buffer[size];
    UINT32 bufLen = size;
    SINT32 res = pSystem->GetValLst(lib, addresses, Buffer, bufLen);

    if (res == SVI_E_OK)
    {
        for (int i = 0; i < size; i++)
        {
            pItems[i]->updateInternalValue(Buffer[i]);
        }
    }
    else
    {
        std::string error = "Svi_GetValLst: Unknown error code recieved...";
        switch (res)
        {
            case SVI_E_UNDEF:
                error = "Svi_GetValLst: SVI server no longer exists";
                break;
            case SVI_E_ADDR:
                error = "Svi_GetValLst: SVI Address is invalid";
                break;
            case SVI_E_FAILED:
                error = "Svi_GetValLst: The function could not be executed properly";
                break;
            case SVI_E_OLDADDR:
                error = "Svi_GetValLst: Address no longer valid";
                break;
            case SVI_E_VARINUSE:
                error = "Svi_GetValLst: Variable is currently used by another task";
                break;
        }
        throw SviSystemException(error, res);
    }

}
