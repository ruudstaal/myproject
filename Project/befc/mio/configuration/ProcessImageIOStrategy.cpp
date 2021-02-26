/**
 ********************************************************************************
 * @file     ProcessImageIOStrategy.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProcessImageIOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <configuration/ProcessImageIOStrategy.hpp>
#include "mio/common/base/BasicDigitalModule.hpp"
#include "mio/common/base/BasicAnalogModule.hpp"
#include "mio/common/base/BasicMixedModule.hpp"

ProcessImageIOStrategy::ProcessImageIOStrategy(std::string moduleName) :
        IOStrategy()
{
    pProcessImage = new ProcessImage((char*) moduleName.c_str());
}

ProcessImageIOStrategy::~ProcessImageIOStrategy()
{
    SAFE_DELETE(pProcessImage);
}

void ProcessImageIOStrategy::readInput()
{
    std::vector<BasicIoModule*>::iterator ite;

    BasicDigitalModule *pDigModule;
    BasicAnalogModule *pAnaModule;
    BasicMixedModule *pMixModule;
    SINT32 m_si32Error;
    std::stringstream msg;

    /** Update from shadow RAM / Process image */
    pProcessImage->updateInput();
    for (ite = m_pRegistredCards->begin(); ite != m_pRegistredCards->end(); ++ite)
    {

        if ((*ite)->isDigitalModule())
        {
            pDigModule = dynamic_cast<BasicDigitalModule*>((*ite));
            readDigitalValues(pDigModule);
        }
        else
        { /** Analogue and mixed modules */
            SINT32 l_si32Buffer[(*ite)->getInfo()->MaxChan];

            m_si32Error = (*ite)->m_pMioSystem->getValues((*ite)->getDriverId(), l_si32Buffer);

            if (0 != m_si32Error)
            {
                msg << "ProcessImageIOStrategy::readInput::mio_GetValues: failed to read values from card(" << (*ite)->getCardNumber() << ")";
                continue;
            }
            else
            {
                if ((*ite)->isMixedModule())
                {
                    pMixModule = dynamic_cast<BasicMixedModule*>((*ite));
                    pMixModule->setValuesInternal(l_si32Buffer, (*ite)->getInfo()->MaxChan);
                }
                else
                {
                    pAnaModule = dynamic_cast<BasicAnalogModule*>((*ite));
                    pAnaModule->setValuesInternal(l_si32Buffer, (*ite)->getInfo()->MaxChan);
                }
            }
        }
    }
}

void ProcessImageIOStrategy::writeOutput()
{
    std::vector<BasicIoModule*>* p_dirtyList = getDirtyList();
    std::vector<BasicIoModule*>::iterator ite;

    BasicDigitalModule *pDigModule;
    BasicAnalogModule *pAnaModule;
    BasicMixedModule *pMixedModule;
    SINT32 m_si32Error = 0;

    for (ite = p_dirtyList->begin(); ite != p_dirtyList->end(); ++ite)
    {
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
                m_si32Error = (*ite)->m_pMioSystem->setValues(pMixedModule->getDriverId(), pMixedModule->getValues());
            }
            else
            {
                pAnaModule = dynamic_cast<BasicAnalogModule*>((*ite));
                m_si32Error = (*ite)->m_pMioSystem->setValues(pAnaModule->getDriverId(), pAnaModule->getValues());
            }
        }

        if (0 != m_si32Error)
        {
            std::stringstream msg;
            msg << "ProcessImageIOStrategy::writeOutput: failed to write values to card -> "
                    << m_si32Error;
            throw MIOexception(msg.str(), pDigModule->getCardNumber(), m_si32Error);
        }
    }

    pProcessImage->updateOutput();
    clearDirtyList();

}

void ProcessImageIOStrategy::registerCard(BasicIoModule *pIOModule)
{
    VOID* l_pDriverId = pProcessImage->addCard(pIOModule);

    if (l_pDriverId == NULL)
    {
        throw MIOexception("Cannot register card - No such module exists",
                pIOModule->getCardNumber(), 0);
    }

    pIOModule->setDriverId(l_pDriverId);
    pIOModule->setIOStrategy(this);
    m_pRegistredCards->push_back(pIOModule);
}
