/**
 ********************************************************************************
 * @file     AnalogChannel.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of AnalogChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "AnalogChannel.hpp"
#include "BasicAnalogModule.hpp"
#include "BasicMixedModule.hpp"

/**-----------------------------------------------------------------*/
AnalogChannel::AnalogChannel()
{

}

/**-----------------------------------------------------------------*/
AnalogChannel::~AnalogChannel()
{

}

/**-----------------------------------------------------------------*/
VOID AnalogChannel::setValue(SINT32 si32Value)
{
    this->m_pModule->setValueInternal(this->m_ui32Channel, si32Value, TRUE);
}

/**-----------------------------------------------------------------*/
SINT32 AnalogChannel::getValue(VOID)
{
    if (this->m_pModule->isDigitalModule() == false)
    {
        if (this->m_pModule->isMixedModule())
        {
            return (dynamic_cast<BasicMixedModule*>(this->m_pModule))->getValue(this->m_ui32Channel);
        }
        else
        {
            return (dynamic_cast<BasicAnalogModule*>(this->m_pModule))->getValue(
                    this->m_ui32Channel);
        }
    }
    throw MIOexception("AnalogChannel::getValue::Module was not mixed or analogue.",
            this->m_pModule->getCardNumber(), this->m_ui32Channel);
}

/**-----------------------------------------------------------------*/
VOID AnalogChannel::setValue(UINT32 ui32Value)
{
    this->m_pModule->setValueInternal(this->m_ui32Channel, (SINT32) ui32Value, TRUE);
}

/**-----------------------------------------------------------------*/
/** Overload not possible based upon return value! */
UINT32 AnalogChannel::getValue_UINT32(VOID)
{
    return BasicChannel::getBasicValue();
}
