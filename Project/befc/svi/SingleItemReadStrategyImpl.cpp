/**
 ********************************************************************************
 * @file     SingleItemReadStrategyImpl.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of SingleItemReadStrategyImpl
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "SingleItemReadStrategyImpl.hpp"
#include "value/ValueFactory.hpp"
#include "SviException.hpp"
#include <utility>

TFailList SingleItemStrategyImpl::writeValues(AbstractSviGroup *pGroup)
{
    std::vector<AbstractSviItem*> vector = pGroup->getItems();
    SINT32 res;
    TFailList err;
    for (std::vector<AbstractSviItem*>::iterator ite = vector.begin(); ite != vector.end(); ++ite)
    {
        if ((*ite)->isInitialized() == false) {
            continue; //No need to proceed
        }

        if ((*ite)->isDirty() && (*ite)->isWriteable())
        {
            if((*ite)->isArrayItem()) {
                res = pSviSystem->SetBlk((*ite)->getLib(), (*ite)->getSviAddr(),
                        (UINT32*)(*ite)->getValueAddress(), (*ite)->getDataLength());
            }
            else{
                res = pSviSystem->SetVal((*ite)->getLib(), (*ite)->getSviAddr(),
                        *((UINT32*) (*ite)->getValueAddress()));
            }

            if (res != SVI_E_OK)
            {

                err.push_back(makePair(res, (*ite)));
                (*ite)->handleErrorCode(res);
            }
            else
            {
                (*ite)->setDirty(false);
            }
        }
    }
    return err;
}

TFailList SingleItemStrategyImpl::readValues(AbstractSviGroup *pGroup)
{

    std::pair<SINT32, AbstractSviItem*> pair;
    SINT32 res;
    std::vector<AbstractSviItem*> vector = pGroup->getItems();
    TFailList err;
    for (std::vector<AbstractSviItem*>::iterator ite = vector.begin(); ite != vector.end(); ++ite)
    {
        if ((*ite)->isInitialized() == false) {
            continue;
        }

        if ((*ite)->isArrayItem())
        {
            UINT32 nbrLength = (*ite)->getDataLength();
            UINT8 value[(*ite)->getDataLength()];
            res = pSviSystem->GetBlk((*ite)->getLib(), (*ite)->getSviAddr(), &value, &nbrLength);
            if (res == SVI_E_OK)
            {
                (*ite)->updateInternalValue((UINT8*) &value, nbrLength);
            }
            else
            {
                err.push_back(makePair(res, (*ite)));
                (*ite)->handleErrorCode(res);
            }
        }
        else
        {
            UINT32 value;
            res = pSviSystem->GetVal((*ite)->getLib(), (*ite)->getSviAddr(), &value);
            if (res == SVI_E_OK)
            {
                (*ite)->updateInternalValue(value);
            }
            else {
                err.push_back(makePair(res, (*ite)));
                (*ite)->handleErrorCode(res);
            }

        }
    }
    return err;
}
