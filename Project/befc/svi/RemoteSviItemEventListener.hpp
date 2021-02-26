/*
 * RemoteSviItemEventListener.hpp
 *
 *  Created on: May 29, 2017
 *      Author: madsen
 */

#ifndef BEFC_SVI_REMOTESVIITEMEVENTLISTENER_HPP_
#define BEFC_SVI_REMOTESVIITEMEVENTLISTENER_HPP_

class RemoteSviItem;

class RemoteSviItemEventListener
{
public:
    RemoteSviItemEventListener(){};

    /**
     *  INIT is before SVI variable has been read.
     *  GOOD is when SVI data has been correctly read
     *  BAD is when variable cannot be read due to failures
     *  TIMED_OUT is when read or write timed out
     */
    enum DataQuality {INIT = 0, GOOD = 1, BAD = -1, TIMED_OUT = -2};

    virtual void dataQualityChanged(RemoteSviItem *pItem, DataQuality oldQuality, DataQuality newQuality) = 0;

    virtual void writeFailed(RemoteSviItem *pItem, SINT32 failure) = 0;

    virtual ~RemoteSviItemEventListener(){};
};

#endif /* BEFC_SVI_REMOTESVIITEMEVENTLISTENER_HPP_ */
