/**
 ********************************************************************************
 * @file     BEModule.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BEModule
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BEMODULE_HPP_
#define BEMODULE_HPP_

#pragma interface "BEModule.hpp"

/** Includes */
#include <setjmp.h>
#include <res_e.h>
#include <mod_e.h>
#include <list>
#include <string>

#include "BETask.hpp"
#include "Version.hpp"
#include "BEModuleState.hpp"
#include "ModuleConfiguration.hpp"

/**
 * @addtogroup MOD
 * @{
 */

/** Forward declarations */
class BEModule;
class SmiHandler;
class SviSystem;

/**
 ********************************************************************************
 * @brief:   This class is used as base class for software modules.
 *           BEModule makes the whole module initialization
 *           (SMI, SVI,...) and handles the SMI messages via RPC.
 *           Application specific methods could be applied by overwriting of
 *           the virtual methods.
 *******************************************************************************/
class BEModule
{
public:

    /**
     ********************************************************************************
     * @brief      Create an instance BEModule without panic and exception handling
     *******************************************************************************/
    BEModule();

    /**
     ********************************************************************************
     * @brief      Create an instance BEModule without panic and exception handling
     *             with specific SVI handling
     *******************************************************************************/
    BEModule(SviSystem *pSviSystem);


    /**
     ********************************************************************************
     * @brief      Create an instance BEModule with panic and exception handling
     *
     * @param[in]  fpPanicHandler   function pointer to panic handler function
     *******************************************************************************/
    explicit BEModule(VOIDFUNCPTR fpPanicHandler);

    /**
     ********************************************************************************
     * @brief     Destructor for cleanly removing of the application.
     *******************************************************************************/
    virtual ~BEModule();

    /**
     ********************************************************************************
     * @brief     This method is the entry point to the module and have to be
     *            called after instantiation of the new application.
     *            When this function is left the interface to the environment
     *            (SMI, SVI) will be initialized and ready to operate.
     *
     * @param[in]  pConf   Pointer to configuration structure (data of mconfig.ini).
     * @param[in]  pLoad   Parameter from module loading
     * @retval     >0      Task-ID, ==> module initialized correctly
     * @retval     <0      Error during initialisation
     *******************************************************************************/
    virtual void init(MOD_CONF *pConf, MOD_LOAD *pLoad);

    /**
     ********************************************************************************
     * @brief     Internal method for deinitializing the module when Init() fails.
     *******************************************************************************/
    VOID deinit(VOID);

    /**
     ********************************************************************************
     * @brief      Initialize all values
     *******************************************************************************/
    virtual VOID initValues(VOID);

    /**
     ********************************************************************************
     * @brief      Get task ID for SMI handling task
     *
     * @retval     SINT32   Task ID
     *******************************************************************************/
    SINT32 getSmiTaskId(VOID);

    /**
     ********************************************************************************
     * @brief     This method gets the module state.
     *
     * @retval     Module state
     *******************************************************************************/
    virtual BEModuleState getModState();

    /**
     ********************************************************************************
     * @brief     This method gets the debug mode.
     *
     * @retval     Debug mode
     *******************************************************************************/
    SINT32 getDebugMode(VOID);

    /**
     ********************************************************************************
     * @brief     This method sets the debug mode.
     *
     * @param[in]  debugMode    Debug mode to be set
     *******************************************************************************/
    VOID setDebugMode(UINT32 debugMode);

    /**
     ********************************************************************************
     * @brief     This method gets the application description.
     *
     * @retval     Description string
     *******************************************************************************/
    std::string getDescription(VOID);

    /**
     ********************************************************************************
     * @brief     This method sets the application description.
     *
     * @param[in]  sDescription   Description for application
     *******************************************************************************/
    void setDescription(std::string sDescription);

    /**
     ********************************************************************************
     * @brief     This method gets the application version.
     *
     * @retval     Version
     *******************************************************************************/
    Version getVersion(VOID);

    /**
     ********************************************************************************
     * @brief     This method sets the application version.
     *
     * @param[in]  version   Version number for application
     *******************************************************************************/
    void setVersion(Version version);

    /**
     ********************************************************************************
     * @brief     This method save the calling environment in a jmp_buf argument
     *
     * @param[in]  JumpEnv	jmp_buf for saving environment information
     *******************************************************************************/
    VOID setJumpEnv(jmp_buf JumpEnv);

    std::string getAppName(VOID)
    {
        return sAppName;
    }
    std::list<BETask*> *getAppTasklist(VOID) const
    {
        return pApplication_tasks;
    }

    UINT32 getCfgLine(VOID)
    {
        return cfgLine;
    }
    std::string getProfileName(VOID)
    {
        return sProfileName;
    }
    SINT32 getMemPart(VOID)
    {
        return memPart;
    }
    SINT32 getTaskPrior(VOID)
    {
        return taskPrior;
    }
    SEM_ID getStateSema(VOID) const
    {
        return stateSema;
    }

    SMI_ID* getSmiID(VOID) const
    {
        return pSmiID;
    }

    SmiHandler* getSmiHandler(void);

    VOIDFUNCPTR getPanicHandler(VOID)
    {
        return fpPanicHandler;
    }

    ModuleConfiguration* getModuleConfiguration() {
        return this->pModuleConf;
    }

    /**
     ********************************************************************************
     * @brief     Get library address for SVI interface in other SW-module
     *
     * @param[in]  name             Name of other SW-module
     * @throws     ModuleException  If module is not found
     * @retval     pLib             Pointer to SVI interface in other SW-module
     *******************************************************************************/
    virtual pLib getLibAddress(std::string name);

    /**
     ********************************************************************************
     * @brief     Renews the pointer to the software module. Useful in cases, where
     *            software module is reinstalled, which would make the pointer invalid.
     *
     * @throws     ModuleException  If module is not found
     * @retval     pLib             Pointer to SVI interface in other SW-module
     *******************************************************************************/
    pLib renewLibAddress(std::string name);

    /**
     ********************************************************************************
     * @brief      Adds a SviExportDescriptor for exporting to the SVI layer
     *
     * @param[in]  pDescriptor      A pointer to the descriptor
     *******************************************************************************/
    void exportToSvi(SviExportDescriptor *pDescriptor);

    std::vector<SviExportDescriptor*>* getModuleSvi()
    {
        return this->pLocalSviExportList;
    }

    /**
     ********************************************************************************
     * @brief     This method terminates all application tasks for this software
     *            module.
     *******************************************************************************/
    VOID terminateTasks(VOID);

    /**
     ********************************************************************************
     * @brief     This method check is all tasks have terminated.
     *            If the tasks state is SUSPENDED it give the state semaphore to allow
     *            task termination.
     *
     * @retval     false    One or more tasks are still terminating
     *             true     All tasks have terminated
     *******************************************************************************/
    bool isTasksTerminated(VOID);

    /**
     ********************************************************************************
     * @brief     This method clears the list of application tasks for this software
     *            module.
     *******************************************************************************/
    VOID clearTasks(VOID);

    /**
     ********************************************************************************
     * @brief     This method starts all application tasks for this software module.
     *            If the module is in state EOI the application tasks will be
     *            spawned, in any other case the state semaphore will be flushed to
     *            start the tasks running again.
     *******************************************************************************/
    VOID startTasks(VOID);

    /**
     ********************************************************************************
     * @brief     This method stops all application tasks for this software module.
     *******************************************************************************/
    VOID stopTasks(VOID);

    /**
     ********************************************************************************
     * @brief     This method adds a application task to the list of tasks for this
     *            software module
     *
     * @param[in]  pTask   Pointer to instance of a BETask
     *******************************************************************************/
    VOID addTask(BETask* pTask);

    virtual VOID AppPanicHandler(UINT32 PanicMode)
    {
    }
    ;

protected:
    UINT32 minVers;
    UINT32 maxVers;

    /**
     ********************************************************************************
     * @brief     This method removes a application task from the list of tasks for
     *            this software module
     *
     * @param[in]  pTask   Pointer to instance of a BETask
     *******************************************************************************/
    VOID removeTask(BETask* pTask);

    /**
     ********************************************************************************
     * @brief     Helper function to initialize application tasks.
     *
     * @throws     ModuleException
     *******************************************************************************/
    void doInitInternal(void);

    /**
     ********************************************************************************
     * @brief     Helper function to de-initialize application tasks.
     *******************************************************************************/
    void doDeinitInternal(void);

    /**
     ********************************************************************************
     * @brief     Function forces task to stop
     *******************************************************************************/
    void forceTaskDelete(void);

    /**
     ********************************************************************************
     * @brief     This method can be overridden, when wanting to read parameters from the mconfig.ini
     *
     *
     * @param[in]  config    Configuration where configuration parameters can be read.
     *******************************************************************************/
    virtual void doCfgRead(ModuleConfiguration config);

    /**
     ********************************************************************************
     * @brief     This virtual function will be called after loading of the
     *            software module.
     *
     * @retval     0   Everything is Ok
     * @retval     <0  Error occurred
     *******************************************************************************/
    virtual BOOL8 doInit(void) = 0;

    /**
     ********************************************************************************
     * @brief     This method bring the software module in the state DEINIT
     *
     * @retval     false      Setting SW-module in DEINIT state failed, module state is
     *                        now ERROR
     *             true       Setting SW-module in DEINIT state successfully done
     *******************************************************************************/
    virtual BOOL8 doDeinit(void);

    /**
     ********************************************************************************
     * @brief     This method bring the software module in the state RUN
     *
     * @retval     false      Setting SW-module in RUN state failed, module state is
     *                        now ERROR
     *             true       Setting SW-module in RUN state successfully done
     *******************************************************************************/
    virtual BOOL8 doRun(void);

    /**
     ********************************************************************************
     * @brief     This method bring the software module in the state EOI
     *
     * @retval     false      Setting SW-module in EOI state failed, module state is
     *                        now ERROR
     *             true       Setting SW-module in EOI state successfully done
     *******************************************************************************/
    virtual BOOL8 doEndOfInit(void);

    /**
     ********************************************************************************
     * @brief     This method bring the software module in the state STOP
     *
     * @retval     false      Setting SW-module in STOP state failed, module state is
     *                        now ERROR
     *             true       Setting SW-module in STOP state successfully done
     *******************************************************************************/
    virtual BOOL8 doStop(void);

    /**
     ********************************************************************************
     * @brief     This method read a new configuration to the software module and
     *            set it to state EOI
     *
     * @retval     false      Reading new cfg failed, module state is now ERROR
     *             true       Reading new cfg successfully done
     *******************************************************************************/
    virtual BOOL8 doNewCfg(void);

    /**
     ********************************************************************************
     * @brief     This method resets the software module and set it to state EOI.
     *
     * @retval     false      Resetting SW-module failed, module state is now ERROR
     *             true       Resetting SW-module successfully done
     *******************************************************************************/
    virtual BOOL8 doReset(void);

    friend class BEModuleState;
    friend class Smi_ProcDeinit;
    friend class Smi_ProcEndOfInit;
    friend class Smi_ProcNewCfg;
    friend class Smi_ProcReset;
    friend class Smi_ProcRun;
    friend class Smi_ProcStop;

private:
    /** SMI Server */
    SMI_ID* pSmiID;
    BEModuleState *pModuleState; /**< Module state */
    std::string sAppName; /**< Instance name of module */
    std::string sDescription; /**< Module description */

    UINT32 cfgLine; /**< Start line in config file */
    SINT32 debug; /**< Debugmode of modules */
    std::string sProfileName; /**< Name of config file */
    SINT32 memPart; /**< Memory partition of module */
    SINT32 taskPrior; /**< Task priority from mconfig.ini */

    Version cVersion; /**< Module version */

    VOIDFUNCPTR fpPanicHandler; /**< Pointer to PanicHandler function */
    jmp_buf JumpEnv;

    SmiHandler* pSmiHandler; /**< bTask for SMI communication */

    SEM_ID stateSema; /**< State change semaphore */
    std::list<BETask*> *pApplication_tasks;

    TStrLibMap *pLibMap;

    /** list for Exporting to SVI */
    std::vector<SviExportDescriptor*>* pLocalSviExportList;

    ModuleConfiguration *pModuleConf;

    SviSystem *pSviSystem;

    /**
     ********************************************************************************
     * @brief     This method changes the module state.
     *
     * @param[in]  pModState    Pointer to new module state.
     *******************************************************************************/
    void setModState(BEModuleState * const pModState);

    /**
     ********************************************************************************
     * @brief     Helper function which starts all application tasks.
     *
     * @param[in]  suspend Start task in suspended mode or not
     *******************************************************************************/
    void startTasksInternal(bool suspend);

    /**
     ********************************************************************************
     * @brief     Initializes the module configuration to be used by client
     *
     *******************************************************************************/
    void initConfiguration(SINT32 lineNumber);

    explicit BEModule(BEModule const& that); /**< no copy */
    BEModule& operator=(BEModule const&); /**< no assign */

};
/** @} */

#endif  /** BEMODULE_HPP_*/
