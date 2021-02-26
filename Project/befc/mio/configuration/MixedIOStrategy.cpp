/**
 ********************************************************************************
 * @file     MixedIOStrategy.cpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Dec 10, 2015 1:07:29 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#include <MixedIOStrategy.hpp>
#include "BEModule.hpp"

MixedIOStrategy::MixedIOStrategy(BETask *pTask)
{
    if (mio_PiUseProcImg) {
        pPiStrategy = new ProcessImageIOStrategy(pTask->getModule()->getAppName());
    }
    else {
        pPiStrategy = NULL;
    }

    pStdStrategy = new StdIOStrategy();

}

MixedIOStrategy::~MixedIOStrategy()
{
    SAFE_DELETE(pPiStrategy);
    SAFE_DELETE(pStdStrategy);
}

void MixedIOStrategy::registerCard(BasicIoModule *pIOModule) {
    try
    {
        //First, try to add it to the ProcessImage
        if (pPiStrategy != NULL)
        {
            pPiStrategy->registerCard(pIOModule);
            return;
        }
    }
    catch (MIOexception &ioe)
    {
        log_Info("Card %d not added to ProcessImage handling. Not supported",pIOModule->getCardNumber());
    }

    //If that does not work, then handle it "normally"
    pStdStrategy->registerCard(pIOModule);
}

void MixedIOStrategy::readInput(){
    if(pPiStrategy != NULL) {
        pPiStrategy->readInput();
    }

    pStdStrategy->readInput();
}

void MixedIOStrategy::writeOutput() {
    if(pPiStrategy != NULL) {
        pPiStrategy->writeOutput();
    }

    pStdStrategy->writeOutput();
}
