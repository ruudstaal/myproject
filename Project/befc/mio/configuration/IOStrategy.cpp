/**
 ********************************************************************************
 * @file     IOStrategy.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of IOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <bitset>
#include <iostream>
#include "IOStrategy.hpp"
#include "../mio/common/base/BasicIoModule.hpp"
#include "../mio/common/base/BasicDigitalModule.hpp"
#include "mcpp.hpp"

IOStrategy::IOStrategy()
{
    m_pDirtyCards = new std::vector<BasicIoModule*>();
    m_pRegistredCards = new std::vector<BasicIoModule*>();

}

IOStrategy::~IOStrategy()
{
    m_pDirtyCards->clear();
    SAFE_DELETE(m_pDirtyCards);

    m_pRegistredCards->clear();
    SAFE_DELETE(m_pRegistredCards);
}

void IOStrategy::markModuleAsDirty(BasicIoModule *pIOModule)
{
    std::vector<BasicIoModule*>::iterator ite;
    for (ite = m_pDirtyCards->begin(); ite != m_pDirtyCards->end(); ++ite)
    {
        if ((*ite)->getCardNumber() == pIOModule->getCardNumber())
        {
            return; /** Already added */
        }

    }
    m_pDirtyCards->push_back(pIOModule);
}

void IOStrategy::clearDirtyList()
{
    m_pDirtyCards->clear();
}

std::vector<BasicIoModule*>* IOStrategy::getDirtyList()
{
    return m_pDirtyCards;
}

void IOStrategy::readDigitalValues(BasicDigitalModule *pModule)
{
    UINT32 channels = pModule->getInfo()->MaxChan;
    UINT32 intsNeeded = ((channels + 32 - 1) / 32);
    SINT32 values[intsNeeded];
    for (UINT32 i = 0; i < intsNeeded; i++)
    { /** Initialize the values */
        values[i] = 0;
    }

    SINT32 result = pModule->m_pMioSystem->getPackedValues(pModule->getDriverId(), values, 1,
            pModule->getInfo()->MaxChan);

    if (result < 0)
    {
        throw MIOexception("Could not read packed values", pModule->getCardNumber(), result);
    }

    UINT32 currentIntIndex = 0;
    UINT32 currentBitInInt = 0;
    std::bitset<32> bitset(values[currentIntIndex]);
    for (UINT32 i = 0; i < channels; i++, currentBitInInt++)
    {
        pModule->setValueInternal(i + 1, (BOOL8) (bitset[currentBitInInt] == 1));
        if (currentBitInInt == 31)
        { /** All bits in the integer is read? */
            currentIntIndex++; /**Get next integer */
            currentBitInInt = -1; /** Has to be set to 0 at next iteration  */
            bitset = std::bitset<32>(values[currentIntIndex]);
        }
    }
}

void IOStrategy::writeDigitalValues(BasicDigitalModule *pModule)
{
    UINT32 channels = pModule->getInfo()->MaxChan;
    BOOL8 *pValues = pModule->getValues();
    UINT32 intsNeeded = ((channels + 32 - 1) / 32);
    SINT32 values[intsNeeded];
    for (UINT32 i = 0; i < intsNeeded; i++)
    {
        values[i] = 0;
    }

    UINT32 currentIntIndex = 0;
    UINT32 currentBitInInt = 0;
    std::bitset<32> bitset;

    for (UINT32 i = 0; i < channels; i++, currentBitInInt++)
    {

        if ((*pValues))
        {
            bitset[currentBitInInt] = 1;
        }

        //if(((i+1) % 32) == 0) { /**Did we just reach the end of the 32 bit value. */
        if (currentBitInInt == 31)
        { /** All bits in the integer is read? */
            values[currentIntIndex++] = bitset.to_ulong();
            currentBitInInt = -1;
            bitset.reset();
        }

        pValues++;
    }

    if (currentBitInInt != 0)
    { /** The scenario where the Channel count mod 32 = 0. (We just finished an packing an UINT32) */
        values[intsNeeded - 1] = bitset.to_ulong();
    }

    SINT32 result = pModule->m_pMioSystem->setPackedValues(pModule->getDriverId(), values, 1,
                    pModule->getInfo()->MaxChan);

    if (result < 0)
    {
        throw MIOexception("Could not write packed values to HW", pModule->getCardNumber(), result);
    }
}
