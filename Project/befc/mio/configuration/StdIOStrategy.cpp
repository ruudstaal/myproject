/**
 ********************************************************************************
 * @file     StdIOStrategy.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StdIOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "StdIOStrategy.hpp"
#include <configuration/ProcessImageIOStrategy.hpp>
#include "mio/common/base/BasicDigitalModule.hpp"
#include "mio/common/base/BasicAnalogModule.hpp"
#include "mio/common/base/BasicMixedModule.hpp"
#include <iostream>
#include <string.h>

StdIOStrategy::StdIOStrategy() :
        IOStrategy()
{
}

StdIOStrategy::~StdIOStrategy()
{
}

void StdIOStrategy::readInput()
{
    std::vector<BasicIoModule*>::iterator ite;

    BasicDigitalModule *pDigModule;
    BasicAnalogModule *pAnaModule;
    BasicMixedModule *pMixModule;
    SINT32 m_si32Error;

    for (ite = m_pRegistredCards->begin(); ite != m_pRegistredCards->end(); ++ite)
    {
        BasicIoModule::EError_t cardError = *((*ite)->getError(true));
        // Check only card related errors, errors on single channels are ok
        if(cardError == BasicIoModule::eDEAD){
            continue;
        }

        if ((*ite)->isDigitalModule())
        { /** Digital values can be read as packed values */
            pDigModule = dynamic_cast<BasicDigitalModule*>((*ite));
            readDigitalValues(pDigModule);
        }
        else
        { /** Analogue and mixed modules */
            SINT32 l_si32Buffer[(*ite)->getNbOfChannels()];
            memset(&l_si32Buffer, 0, (*ite)->getNbOfChannels() * sizeof(SINT32));

            m_si32Error = (*ite)->m_pMioSystem->getValues((*ite)->getDriverId(), l_si32Buffer);

            // If set values is not supported, try setting channel individually
            if (MIO_ER_BADFUNC == m_si32Error)
            {
                //readSingleChannelsCnt++;
                m_si32Error = 0;
                for(UINT32 i = 0; i < (*ite)->getNbOfChannels(); i++)
                {
                    m_si32Error = (*ite)->m_pMioSystem->getValue((*ite)->getDriverId(), i + 1, &l_si32Buffer[i]);
                    if(m_si32Error)
                    {
                        l_si32Buffer[i] = 0;
                    }
                }
            }

            if(0 != m_si32Error)
            {
//                std::stringstream msg;
//                msg << "StdIOStrategy::readInput::mio_GetValues: failed to read values from card("<< (*ite)->getCardNumber() << "), frc = " << m_si32Error;
//                log_Wrn("%s", msg.str().c_str());
                continue;
            }
            else
            {
                if ((*ite)->isMixedModule())
                {
                    pMixModule = dynamic_cast<BasicMixedModule*>((*ite));
                    pMixModule->setValuesInternal(l_si32Buffer, (*ite)->getNbOfChannels());
                }
                else
                {
                    pAnaModule = dynamic_cast<BasicAnalogModule*>((*ite));
                    pAnaModule->setValuesInternal(l_si32Buffer, (*ite)->getNbOfChannels());
                }
            }
        }
    }
}

void StdIOStrategy::writeOutput()
{
    std::vector<BasicIoModule*>* p_dirtyList = getDirtyList();
    std::vector<BasicIoModule*>::iterator ite;

    BasicDigitalModule *pDigModule;
    BasicAnalogModule *pAnaModule;
    BasicMixedModule *pMixedModule;
    SINT32 m_si32Error = 0;

    for (ite = p_dirtyList->begin(); ite != p_dirtyList->end(); ++ite)
    {
        // Check only card related errors, errors on single channels are ok
        if(*((*ite)->getError()) == BasicIoModule::eDEAD){
            continue;
        }

        if ((*ite)->isDigitalModule())
        {
            pDigModule = dynamic_cast<BasicDigitalModule*>((*ite));
            writeDigitalValues(pDigModule);
        }
        else
        {
            if ((*ite)->isMixedModule())
            {
                pMixedModule = dynamic_cast<BasicMixedModule*>((*ite));
                m_si32Error = pMixedModule->m_pMioSystem->setValues(pMixedModule->getDriverId(), pMixedModule->getValues());
                // If set values is not supported, try setting channel individually
                if(m_si32Error == MIO_ER_BADFUNC)
                {
                    m_si32Error = 0;
                    for(UINT32 i = 1; i <= pMixedModule->getNbOfChannels(); i++)
                    {
                        if(pMixedModule->getBasicChannel(i)->getInfo()->Category == MIO_CATEG_DO ||
                           pMixedModule->getBasicChannel(i)->getInfo()->Category == MIO_CATEG_AO)
                        {
                            // Need to consider a channel dirty flag for UFB cards (e.g. S60870-5-104)
                            if(pMixedModule->isDirtyChannel(i))
                            {
                                m_si32Error = pMixedModule->m_pMioSystem->setValue(pMixedModule->getDriverId(), i, pMixedModule->getValue(i));
                                pMixedModule->clearDirtyChannel(i);
                            }
                        }
                    }
                }
            }
            else
            {
                pAnaModule = dynamic_cast<BasicAnalogModule*>((*ite));
                m_si32Error = pAnaModule->m_pMioSystem->setValues(pAnaModule->getDriverId(), pAnaModule->getValues());
            }
        }

        if (0 != m_si32Error)
        {
            std::stringstream msg;
            UINT32 cardNo = -1;
            if ((*ite)->isDigitalModule())
            {
                cardNo = pDigModule->getCardNumber();
            }
            else if ((*ite)->isMixedModule())
            {
                cardNo = pMixedModule->getCardNumber();
            }
            else
            {
                cardNo = pAnaModule->getCardNumber();
            }
            msg << "StdIOStrategy::writeOutput: failed to write values to card -> " << m_si32Error;
            throw MIOexception(msg.str(), cardNo, m_si32Error);
        }
    }
    clearDirtyList();
}

void StdIOStrategy::registerCard(BasicIoModule *pIOModule)
{
    VOID* l_pDriverId = pIOModule->m_pMioSystem->getDrv(pIOModule->getCardNumber());

    if (l_pDriverId == NULL)
    {
        throw MIOexception("Cannot register card - No such module exists",
                pIOModule->getCardNumber(), 0);
    }

    pIOModule->setDriverId(l_pDriverId);
    pIOModule->setIOStrategy(this);
    m_pRegistredCards->push_back(pIOModule);

}

