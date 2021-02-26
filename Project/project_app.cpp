
/**
 ********************************************************************************
 * @file     template_app.cpp
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
#define CLASS_NAME "project_app"

/** Includes */
#include "mcpp.hpp"
#include "project_app.hpp"
#include "BEModule.hpp"
#include "log_e.h"
#include <iostream>
#include "BETaskConfiguration.hpp"
#include <fftw3.h>

using namespace std;

project_app::project_app(BETaskConfiguration conf) :
        BETask(conf)
{
    /* Init program variables */
    retVal = 0;
    programCounter = 0;
    maxPrint = 5;
    fileName = "data.csv";

    /* Init AIC214 variables */
    moduleNumber = 4;
    channel = 2;
    RPSchannel = 13;
    numSamplesToRead = 0;
    status = UINT_MAX;
    prevStatus = UINT_MAX;
    firstSampleIdx = 0;
    valuesRead = 0;
    counter = 0;
    RMSvalue = 0;
    RPSvalue = 0;

    AIC214_init();
    AIC214_initSviClient();
    AIC214_initSVIServer();

}

project_app::~project_app()
{

}

void project_app::cycleWork(void)
{

        programCounter++;


        AIC214_checkStatus();


        if (programCounter >= 10){


            if (status == AIC2XX_RING_STATE_STOPPED){
                retVal = aic2xx_StartRingRecording(AIC206_card);
                if (retVal != MIO_ER_OK){
                    log_Err("Error when getting starting recording for AIC214, error code: %d", retVal);
                }
                else{
                    log_Info("AIC214 started recording");
                }
            }

            else if (status == AIC2XX_RING_STATE_RECORDING){


                retVal = aic2xx_StopRingRecording(AIC206_card);
                if (retVal != MIO_ER_OK){
                    log_Err("Error when getting stopping recording for AIC214, error code: %d", retVal);
                }
                else{
                    log_Info("AIC214 stopped recording");
                }


                retVal = aic2xx_SetRingReadSampleIdxIfParked(AIC206_card, channel, firstSampleIdx);
                if (retVal != MIO_ER_OK){
                    log_Err("Error when setting read pointer of ring, error code: %d", retVal);
                }
                else{
                    log_Info("Reseted the read pointer of the ring");
                }


                retVal = aic2xx_GetRingValues(AIC206_card, channel, numSamplesToRead, ringData.data(), &valuesRead);
                if (retVal != MIO_ER_OK){
                    log_Err("Error when getting values from ring for AIC214, error code: %d", retVal);
                }
                else{
                    log_Info("AIC214 number of values read: %d", valuesRead);
                }




                log_Info("Ring buffer values: \n");
                csvFile.open("data.csv",std::ios_base::app);

                if (csvFile.is_open())
                {
                    for (size_t i = 0; i<valuesRead; i++){
                        if (i < maxPrint){
                            log_Info("    ringData[%d]: time = %d [us], value = %d", i, ringData.at(i).timeUsec, ringData.at(i).ringSliceValue);
                        }
                        csvFile << i << "," << ringData.at(i).timeUsec << "," << ringData.at(i).ringSliceValue << "\n";
                    }
                }
                else{
                    log_Err("Error opening csv file");
                }
                csvFile << "\n";
                csvFile.close();


                retVal = aic2xx_ReleaseRing(AIC206_card, channel);
                if (retVal != MIO_ER_OK){
                    log_Err("Error when releasing the ring buffer, error code: %d", retVal);
                }
            }

            //programCounter = 0;
        }

        AIC214_GetRPSstat();



}


void project_app::AIC214_init()
{


    AIC206_card = mio_GetDrv(moduleNumber);
    if (AIC206_card == NULL){
        log_Err("AIC214 not available at module number %d!", moduleNumber);
    }


    log_Info("Number of samples that will be read: %d", numSamplesToRead);

    numSamplesToRead = channel_cfg.ai.sampleRate;
    ringData.resize((size_t) numSamplesToRead);
    log_Info("Allocated a buffer 'ringData' with a size of '%d'", ringData.size());


    retVal = aic2xx_GetAICfg(AIC206_card, channel, &channel_cfg);
    if (retVal != MIO_ER_OK){
        log_Err("Error when setting read pointer of ring, error code: %d", retVal);
    }
    else{
        if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_51K2){
            log_Info("Sample rate of channel %d: 51.200 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_25K6){
            log_Info("Sample rate of channel %d: 25.600 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_12K8){
            log_Info("Sample rate of channel %d: 12.800 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_06K4){
            log_Info("Sample rate of channel %d: 6.400 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_03K2){
            log_Info("Sample rate of channel %d: 3.200 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_01K6){
            log_Info("Sample rate of channel %d: 1.600 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_00K8){
            log_Info("Sample rate of channel %d: 800 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_00K4){
            log_Info("Sample rate of channel %d: 400 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_00K2){
            log_Info("Sample rate of channel %d: 200 Hz", channel);
        }
        else if (channel_cfg.ai.sampleRate == AIC2XX_SAMPLERATE_00K1){
            log_Info("Sample rate of channel %d: 100 Hz", channel);
        }
        else{
            log_Err("Sample rate of channel %d: unknown", channel);
        }

    }


}


void project_app::AIC214_checkStatus()
{

    retVal = aic2xx_GetRingState(AIC206_card, &status);
    if (retVal != MIO_ER_OK){
        log_Err("Error when getting ring status, error code: %d", retVal);
    }


    if (status == AIC2XX_RING_STATE_STOPPED){
        if (status != prevStatus){
            log_Info("AIC214 status changed to: Ring recording stopped");
        }
    }
    else if (status == AIC2XX_RING_STATE_RECORDING){
        if (status != prevStatus){
            log_Info("AIC214 status changed to: Ring recording is in progress");
        }
    }
    else{
        log_Err("Unknown AIC214_status: %d", status);
    }
    prevStatus = status;

}

void project_app::AIC214_GetRPSstat()
{
    //Gets device control block
    AIC206_card = mio_GetDrv(moduleNumber);

    retValRPS = aic2xx_GetRPSStatistics(AIC206_card, RPSchannel, &RPSStats);
    if (retValRPS != MIO_ER_OK){
                 log_Err("Error when getting values from ring for AIC214, error code: %d", retValRPS);
              }
              else{
                  log_Info("Channel: %d, AIC214 RPS max value channel: %d",channel, RPSStats.maxValue);
                  log_Info("Channel: %d, AIC214 RPS max value channel: %d",channel, RPSStats.minValue);
              }
    retValRPS = aic2xx_GetRPSValue(AIC206_card, RPSchannel, &RPSvalue);
    if (retValRPS != MIO_ER_OK){
                 log_Err("Error when getting values from ring for AIC214, error code: %d", retValRPS);
              }
              else{
                  log_Info("Channel: %d, AIC214 RPS max value channel: %d",channel, RPSvalue);
              }
}
/*
void project_app::AIC214_GetTime()
{


}
*/

void project_app::AIC214_initSviClient()
{
    /** Creates a helper class for creating descriptors */
    pSviGroup = new SviGroup("MyGroup", this);


    /** Export variables to SVI */
    //this->exportToSvi(helper.exportValue("AIC206/RMS", SVI_F_REAL32, true, false, (UINT32*) &RMS));
}

void project_app::AIC214_initSVIServer()
{
    /** Creates a helper class for creating descriptors */
    SviExportHelper helper;

    //Export variables to SVI
    this->exportToSvi(helper.exportValue("RPS/RPS_max", SVI_F_REAL64, true, true, (UINT32*) &RPSStats.maxValue));
    this->exportToSvi(helper.exportValue("RPS/RPS_min", SVI_F_REAL64, true, true, (UINT32*) &RPSStats.minValue));
    this->exportToSvi(helper.exportValue("RPS/RPS_value", SVI_F_REAL64, true, true, (UINT32*) &RPSvalue));
    this->exportToSvi(helper.exportValue("RMS/RMS_value", SVI_F_UINT64, true, true, (UINT32*) &RMSvalue));
    //this->exportToSvi(helper.exportValue("TIME/TIME", SVI_F_REAL64, true, true, (UINT32*) &TIME));
}

void project_app::getRMSvalue()
{

    AIC206_card = mio_GetDrv(moduleNumber);

    UINT32 retval;


    retval = aic2xx_GetRMSValue(AIC206_card, channel, AIC2XX_TYPE_RMS_A1, &RMSvalue);
    if (retVal != MIO_ER_OK){
            log_Err("Error when getting RMS values from AIC206, error code: %d", retVal);
        }
        else{
            log_Info("Read RMSvalue of : %d", valuesRead);
        }
    retval = aic2xx_GetRMSValuePhy(AIC206_card, channel, AIC2XX_TYPE_RMS_A1, &RMSvaluePsy);
    if (retVal != MIO_ER_OK){
             log_Err("Error when getting RMS values from AIC206, error code: %d", retVal);
         }
         else{
             log_Info("Read RMSvalue of : %d", valuesRead);
         }


}

void project_app::
{


}








