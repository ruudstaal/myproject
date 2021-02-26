/*
 * SviItemEventListener.hpp
 *
 *  Created on: May 21, 2019
 *      Author: madsen
 */

#ifndef BEFC_SVI_SVIITEMEVENTLISTENER_HPP_
#define BEFC_SVI_SVIITEMEVENTLISTENER_HPP_

class AbstractSviItem;

/**
 ********************************************************************************
 *
 * @brief      Listener interface for getting events for an AbstractSviItem. This is
 *             when quality of data changes, or a write fails.
 *
 *******************************************************************************/
class SviItemEventListener
{
public:
    SviItemEventListener(){}
    /**
     *  INIT is before SVI variable has been read.
     *  GOOD is when SVI data has been correctly read
     *  BAD is when variable cannot be read due to failures
     *  TIMED_OUT is when read or write timed out
     */
    enum DataQuality {INIT = 0, GOOD = 1, BAD = -1, TIMED_OUT = -2};

    virtual void dataQualityChanged(AbstractSviItem *pItem, DataQuality oldQuality, DataQuality newQuality) = 0;

    virtual void writeFailed(AbstractSviItem *pItem, SINT32 failure) = 0;

    virtual ~SviItemEventListener(){};
};

#endif /* BEFC_SVI_SVIITEMEVENTLISTENER_HPP_ */
