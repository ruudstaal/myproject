/*
 * AbstractSviGroup.cpp
 *
 *  Created on: May 8, 2019
 *      Author: madsen
 */

#include "AbstractSviGroup.hpp"

AbstractSviGroup::AbstractSviGroup() : state(SviGroupEventListener::OFFLINE){
}

void AbstractSviGroup::addEventListener(SviGroupEventListener *pListener){
        if(pListener != NULL){
            listeners.push_back(pListener);
        }
    }

void AbstractSviGroup::setState(SviGroupEventListener::GroupState newState) {
    this->state = newState;
    notifyAboutState(newState);

}

void AbstractSviGroup::notifyAboutState(SviGroupEventListener::GroupState newState) {
    for(std::vector<SviGroupEventListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->groupStateChanged(this, newState);
        (*it)->groupStateChanged(newState);
    }
}

void AbstractSviGroup::notifyAboutGroupRefresh() {
    for(std::vector<SviGroupEventListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->groupUpdated(this);
    }
}


void AbstractSviGroup::notifyAboutItemFailed(SINT32 reason, AbstractSviItem *pItem){
    for(std::vector<SviGroupEventListener*>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->itemFailed(reason, pItem);
    }
}

void AbstractSviGroup::notifyFailList(TFailList list) {
    for (TFailList::const_iterator ite = list.begin(); ite != list.end(); ++ite) {
        notifyAboutItemFailed(ite->first, ite->second);
    }
}
