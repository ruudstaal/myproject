/**
 ********************************************************************************
 * @file     AO202.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog output module AO202
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef AO202_HPP_
#define AO202_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief  16 Bit Anaolog Output Module AO202
 *
 * Output   : +/-10V
 *
 */
class AO202: public BasicAnalogModule
{

public:

    /** switch channel to SYNC-Mode */
    static const UINT32 MODE_SYNC;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    AO202();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit AO202(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~AO202();

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_AO202;
    }
};

#endif /** AO202_HPP_ */
