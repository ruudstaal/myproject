/*
 * RemoteGroupEventListener.hpp
 *
 *  Created on: May 23, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_SVIGROUPEVENTLISTENER_HPP_
#define BEFC_SVI_SVIGROUPEVENTLISTENER_HPP_

#include "AbstractSviItem.hpp"

class AbstractSviGroup;

/**
    ********************************************************************************
    *
    * @brief      Pure virtual interface class for listening to group events. Functions
    *             will be called when events occur.
    *******************************************************************************/
class SviGroupEventListener
{
public:
    enum GroupState {ONLINE = 1, OFFLINE = 0, ERR = -1};

    SviGroupEventListener(){};

    virtual void groupUpdated(AbstractSviGroup *pGroup) = 0;

    virtual void groupStateChanged(AbstractSviGroup *pGroup, const GroupState state) = 0;

    DEPRECATED(virtual void groupStateChanged(GroupState state) = 0;);

    virtual void itemFailed(SINT32 reason, AbstractSviItem *pItem) = 0;

    virtual ~SviGroupEventListener(){};

};

#endif /* BEFC_SVI_SVIGROUPEVENTLISTENER_HPP_ */
