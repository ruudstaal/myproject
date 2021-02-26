/**
 ********************************************************************************
 * @file     DigitalChannel.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of DigitalChannel
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "DigitalChannel.hpp"
#include "BasicDigitalModule.hpp"
#include "BasicMixedModule.hpp"

/**-----------------------------------------------------------------*/
DigitalChannel::DigitalChannel()
{

}

/**-----------------------------------------------------------------*/
DigitalChannel::~DigitalChannel()
{

}

/**-----------------------------------------------------------------*/
VOID DigitalChannel::setValue(BOOL8 b8Value)
{
	this->m_pModule->setValueInternal(this->m_ui32Channel, b8Value, TRUE);
}

/**-----------------------------------------------------------------*/
BOOL8 DigitalChannel::getValue(VOID)
{
	if(this->m_pModule->isDigitalModule()){
		return (dynamic_cast<BasicDigitalModule*>(this->m_pModule))->getValue(this->m_ui32Channel);
	}
	else if(this->m_pModule->isMixedModule()){
		return (dynamic_cast<BasicMixedModule*>(this->m_pModule))->getBoolValue(this->m_ui32Channel);
	}
	throw MIOexception("DigitalChannel::getValue::Module was not mixed or digital.",this->m_pModule->getCardNumber(),this->m_ui32Channel);
}
