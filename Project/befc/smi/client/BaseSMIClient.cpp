/**
 ********************************************************************************
 * @file     BaseSMIClient.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Sep 16, 2016 10:47:18 AM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <BaseSMIClient.hpp>
#include <algorithm>
#include "mcpp.hpp"


BaseSMIClient::BaseSMIClient() : state(SMIClientEventListener::OFFLINE)
{
    m_pListeners = new std::vector<SMIClientEventListener*>();
}

BaseSMIClient::~BaseSMIClient()
{
    m_pListeners->clear();
    SAFE_DELETE(m_pListeners);
}

void BaseSMIClient::removeEventListener(SMIClientEventListener *pListener) {
    std::vector<SMIClientEventListener*>::iterator ite = std::find(m_pListeners->begin(), m_pListeners->end(), pListener);
    if(ite != m_pListeners->end()){
        m_pListeners->erase(ite);
    }
}

void BaseSMIClient::addEventListener(SMIClientEventListener *pListener) {
    m_pListeners->push_back(pListener);
}

void BaseSMIClient::notifyListeners(SMIClientEventListener::ClientState state){
    for(std::vector<SMIClientEventListener*>::iterator ite = m_pListeners->begin(); ite != m_pListeners->end(); ++ite) {
        (*ite)->eventRecieved(state);
    }
}

void BaseSMIClient::setState(SMIClientEventListener::ClientState state, bool notify){
    this->state = state;
    if(notify) {
        notifyListeners(state);
    }
}

