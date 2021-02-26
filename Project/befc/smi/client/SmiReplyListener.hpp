/**
 ********************************************************************************
 * @file     SmiReplyListener.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Aug 9, 2016 12:57:22 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_SMI_CLIENT_SMIREPLYLISTENER_HPP_
#define BEFC_SMI_CLIENT_SMIREPLYLISTENER_HPP_

#include "SmiCallReply.hpp"

class SmiReplyListener
{
public:

    /**
     ********************************************************************************
     *
     * @brief      Function which is called when a reply is recieved
     *
     * @param[in]  pReply   The reply object which should read the answer.
     * @param[in]  procID   Procedure ID of the call which was sent
     *******************************************************************************/
    virtual void replyRecieved(SmiCallReply *pReply, UINT32 procID) = 0;


    /**
     ********************************************************************************
     *
     * @brief      Function which is called when a SMI call fails.
     *
     * @param[in]  pReply   The reply object which should have read the answer.
     * @param[in]  procID   Procedure ID of the call which failed
     * @param[in]  reason   Reason for the call which failed (M_E_xx, SMI_E_xx)
     *******************************************************************************/
    virtual void callFailed(SmiCallReply *pReply, UINT32 procID, SINT32 reason) = 0;


    /**
     ********************************************************************************
     * DEPRECATED - Use callFailed(pReply,procID,reason) instead. This function provides
     *              the response object to the call which failed.
     *
     * @brief      Function which is called when a SMI call fails.
     *
     * @param[in]  procID   Procedure ID of the call which failed
     * @param[in]  reason   Reason for the call which failed (M_E_xx, SMI_E_xx)
     *******************************************************************************/
    DEPRECATED(virtual void callFailed(UINT32 procID, SINT32 reason) = 0;);

protected:
    SmiReplyListener(){};
    virtual ~SmiReplyListener(){};


};

#endif /* BEFC_SMI_CLIENT_SMIREPLYLISTENER_HPP_ */
