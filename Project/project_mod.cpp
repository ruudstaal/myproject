/**
 ********************************************************************************
 * @file     template_mop.cpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 18, 2013 1:20:23 PM $
 *
 * @brief    This is the implementation of the entry point of the application.
 *           Working tasks are created and added in the @see doInit method.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Includes */
#include "mcpp.hpp"

#include "project_mod.hpp"
#include "project_app.hpp"
#include <string>
#include "BETaskConfiguration.hpp"


using namespace std;


/** globals */
BEModule* MainModule;

/** SW-Module memory partition, needed for new operator */
UINT32 project_MemPart = 0;

/** Function definitions */


/**
 ********************************************************************************
 * @brief         This function is the entry point to the module.
 *                After module loading this function will be called as part
 *                of the module handler.
 *                This function has to initialize the interfaces to the
 *                environment (SMI, SVI) so that they are ready to operate.
 *
 *
 * @param[in]  pConf   Parameter for configuration (data from MCONFIG.INI).
 * @param[in]  pLoad   Parameter from module loading.
 * @retval     >0      Task-Id, module initialized correctly.
 * @retval     <0      Error during initialization.
 *******************************************************************************/
extern "C" SINT32 project_Init(MOD_CONF *pConf, MOD_LOAD *pLoad)
{
    /** SW-Module memory partition, needed for new operator */
    project_MemPart = pConf->MemPart;

    try
    {
        /** Create new application class. */
        MainModule = new project_mod();
        MainModule->init(pConf, pLoad);
        /** return the task int to the module handler */
        return MainModule->getSmiTaskId();
    }
    catch(int e)
    {
        /** Close application if an error is occurred. */
        SAFE_DELETE(MainModule)
        return(e);
    }

    return(0);
}

project_mod::project_mod()
{
}

project_mod::project_mod(VOIDFUNCPTR fpPanicHandler) : BEModule(fpPanicHandler)
{
}

project_mod::~project_mod()
{
}


BOOL8 project_mod::doInit(VOID)
{
        /** Create application task class */
        addTask(new project_app(BETaskConfiguration(this, "a" + getAppName())));
        return (true);

}

