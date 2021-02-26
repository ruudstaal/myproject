/**
 ********************************************************************************
 * @file     PTAI216.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 3, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of analog input module PTAI216
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef PTAI216_HPP_
#define PTAI216_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief 16 Bit Analog Input Module PTAI216
 *
 * Input    : 4  \n
 * +/-10V, +/-1V, 0-20mA \n
 *
 * Input    : 12 \n
 * Pt100, PT1000
 */
class PTAI216: public BasicAnalogModule
{

public:

    /** modes for Channel 1-4 */
    static const UINT32 MODE_10V;
    static const UINT32 MODE_1V;
    static const UINT32 MODE_20mA;

    /** modes for Channel 5-16 */
    static const UINT32 MODE_PT100;
    static const UINT32 MODE_PT1000;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    PTAI216();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit PTAI216(UINT32 ui32CardNumber);

    /**
     * Destructor
     */
    virtual ~PTAI216();

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_PTAI216;
    }
};

#endif /** PTAI216_HPP_ */
