/**
 ********************************************************************************
 * @file     template_app.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 18, 2013 1:20:23 PM $
 *
 * @brief    This is an example of an instance of a working task for
 *           an application.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef PROJECT_APP_HPP_
#define PROJECT_APP_HPP_


/** Includes */
#include <string>
#include "BETask.hpp"

#include "aic2xx.h"
#include <fstream>

//SVI Server includes
#include "SviExportHelper.hpp"

/* SVI Client includes */
#include "Uint32Value.hpp"
#include "Sint32Value.hpp"
#include "Real32Value.hpp"
#include "Real64Value.hpp"


/**
 * @addtogroup APP-TASK
 * @{
 */
class project_app: public BETask


{
public:
    project_app(BETaskConfiguration conf);
    ~project_app();

    void cycleWork(void);

    void AIC214_init();

    void AIC214_checkStatus();

    void AIC214_GetRPSstat();

    void AIC214_initSviClient();

    void AIC214_getRMSstat();

    void AIC214_initSVIServer();

    void AIC214_getRPSvalue();

    void getRMSvalue();



    /**
     ********************************************************************************
     * @brief     This method is called cyclic for this application task.
     *******************************************************************************/



private:
    AbstractSviGroup *pSviGroup;


    SINT32 retVal;
    SINT32 retValRPS;
    UINT32 programCounter;
    UINT32 maxPrint;
    std::ofstream csvFile;
    std::string fileName;



    VOID *AIC206_card;
    AIC2XX_AI_CH_CFG channel_cfg;
    AIC2XX_RPS_STATISTICS RPSStats;
    REAL64 testvalue;
    UINT32 RPSchannel;
    UINT32 moduleNumber;
    UINT32 channel;
    UINT32 numSamplesToRead;
    UINT32 status;
    UINT32 prevStatus;
    UINT32 firstSampleIdx;
    UINT32 valuesRead;
    std::vector<AIC2XX_RING_SLICE> ringData;
    SINT32 counter;
    UINT32 RMSvalue;
    REAL64 RMSvaluePsy;
    REAL64 RPSvalue;

};

/** @} */

#endif  /** PROJECT_APP_HPP_ */
