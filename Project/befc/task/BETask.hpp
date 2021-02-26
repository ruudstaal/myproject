/**
 ********************************************************************************
 * @file     BETask.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BETask
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BETASK_HPP_
#define BETASK_HPP_

#pragma interface "BETask.hpp"

/** includes */
#include "BETaskState.hpp"
#include "IllegalStateException.hpp"
#include "SviGroup.hpp"
#include "SmiRequest.hpp"
#include "SviExportDescriptor.hpp"
#include "ManualConfiguration.hpp"

/**
 * @addtogroup TASK
 * @{
 */

namespace Task
{
class RunState;
}

class BETaskState;
class IllegalStateException;
class MIOConfiguration;
class BEModule;
/** Forward declaration */
class SviGroup;
/** Forward declaration */
class IOConfigurationFactory;
/** Forward declaration */
class BETaskConfiguration;

class BETask
{
public:

    /**
     ********************************************************************************
     * @brief      Create an instance BETask.
     *
     * @param[in]  conf     The configuration for the task
     *******************************************************************************/
    BETask(BETaskConfiguration conf);

    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *             This instance has no delay.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName));

    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime));

    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     * @param[in]  autoDetectIO     All IO cards are automatically detected and added to configuration
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, BOOL8 autoDetectIO));
    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     * @param[in]  priority         Priority for the task
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority));
    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     * @param[in]  priority         Priority for the task
     * @param[in]  pIOFactory		IO configuration factory
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority,
            IOConfigurationFactory *pIOFactory));

    /**
     ********************************************************************************
     * Constructor is deprecated - use BETask(BETaskConfiguration conf);
     *
     * @brief      Create an instance BETask with application and task name.
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     * @param[in]  priority         Priority for the task
     * @param[in]  stackSize        Stack size for the task
     *******************************************************************************/
    DEPRECATED(BETask(BEModule *pModule, std::string sTaskName, UINT32 cycleTime, UINT32 priority,
            UINT32 stackSize));

    /**
     ********************************************************************************
     * @brief Destructor of BETask.
     *******************************************************************************/
    virtual ~BETask();

    /**
     ********************************************************************************
     * @brief   Set the a pointer to the application state semaphore
     *
     * @param[in]  pStateSema  Pointer to the state semaphore
     *******************************************************************************/
    void setStateSemaphore(SEM_ID* pStateSema);

    /**
     ********************************************************************************
     * @brief      Adds SVI client group to the task.
     *
     *             If a group with the same name already exist the group is not added.
     *
     *             ATTENTION: Groups added with this function are freed from memory
     *             when task is destroyed.
     *
     * @param[in]  pGroup       Pointer to SviGroup
     * @retval     true         Group successfully added
     * @retval     false        Group already exist, group not added
     *******************************************************************************/
    bool addSviGroup(AbstractSviGroup *pGroup);

    /**
     ********************************************************************************
     * @brief      Removes SVI client group from the task.
     *
     * @param[in]  pGroup       Pointer to SviGroup
     * @retval     true         Group successfully removed
     * @retval     false        Group doesn't exist, group not removed
     *******************************************************************************/
    bool removeSviGroup(AbstractSviGroup *pGroup);

    /**
     ********************************************************************************
     * @brief      Refresh SVI client groups in the task.
     *
     * @throws     SviException
     *******************************************************************************/
    void refreshSviGroups(void);

    /**
     ********************************************************************************
     * @brief      Writes out values to SVI layer (SVI client)
     *
     * @throws     SviException
     *******************************************************************************/
    void sviGroupUpdateOut(void);

    /**
     ********************************************************************************
     * @brief   Set the task debug mode
     *
     * @param[in]  debugMode   The application debug mode
     *******************************************************************************/
    virtual void setDebugMode(UINT32 debugMode);

    /**
     ********************************************************************************
     * @brief   Get the task debug mode
     *
     * @retval     The task debug mode
     *******************************************************************************/
    UINT32 getDebugMode(void);

    /**
     ********************************************************************************
     * @brief      Spawn the task. Parameter already set.
     *
     * @param[in]  autoSuspend		Start tasks suspended or running
     * @throws     IllegalStateException
     *******************************************************************************/
    void start(bool autoSuspend) throw (IllegalStateException);

    /**
     ********************************************************************************
     * @brief      Set the task to STOP.
     *
     * @throws     IllegalStateException
     *******************************************************************************/
    void stop(void) throw (IllegalStateException);

    void terminate(void) throw (IllegalStateException);

    /**
     ********************************************************************************
     * @brief      This is the main loop of the task.
     *******************************************************************************/
    virtual void run(void);

    /**
     ********************************************************************************
     * @brief      Terminate the Task.
     *
     * @throws     IllegalStateException
     *******************************************************************************/
    bool isTerminated();

    /**
     ********************************************************************************
     * @brief      Get the task name.
     *
     * @retval     the task name
     *******************************************************************************/
    std::string getTaskName(void);

    /**
     ********************************************************************************
     * @brief      Get the task id.
     * @retval     the task id.
     *******************************************************************************/
    SINT32 getTaskId(void);

    /**
     ********************************************************************************
     * @brief      Get the module.
     *
     * @retval     Pointer to the module
     *******************************************************************************/
    BEModule* getModule(VOID);

    /**
     ********************************************************************************
     * @brief      Get the task state.
     *
     * @retval     Pointer to the task state
     *******************************************************************************/
    BETaskState* getTaskState(void);

    /**
     ********************************************************************************
     * @brief      Get a list with SMI-Procedures from the task. This function is
     *             used from M1Module to add the SMI-Procedures from the task to the
     *             Module.
     *
     * @retval     list with SMI-Procedures
     *******************************************************************************/
    std::vector<SmiRequest*>* getSmiRequestList(void);

    /**
     ********************************************************************************
     * @brief      Get a list with SVIExportDescriptors which describes what should be
     * 			   exported to the SVI Layer
     *
     * @retval     list with SviExportDescriptors
     *******************************************************************************/
    std::vector<SviExportDescriptor*>* getSviDescriptorList();

    /**
     ********************************************************************************
     * @brief      Adds a SviExportDescriptor for exporting to the SVI layer
     *
     * @param[in]  pDescriptor      A pointer to the descriptor
     *******************************************************************************/
    void exportToSvi(SviExportDescriptor *pDescriptor);

    /**
     ********************************************************************************
     * @brief      Adds multiple SviExportDescriptors for exporting to the SVI layer
     *
     * @param[in]  pDescriptor      A list of SviExportDescriptors
     *******************************************************************************/
    void exportToSvi(std::vector<SviExportDescriptor*> descriptors);

    /**
     ********************************************************************************
     * @brief      Gets the IO configuration for the task. This can be used for adding
     *             IO cards, which should be used for writing/reading IO.
     *
     * @retval     list with SviExportDescriptors
     *******************************************************************************/
    MIOConfiguration* getIOConfiguration();

protected:
    /** status variables */
    BETaskState *pState;
    SEM_ID* pStateSema;
    SEM_ID cycleSema;

    /** debug mode parameter */
    UINT32 debugMode;

    /** task parameter */
    std::string sTaskName;
    std::string sAppName;
    UINT32 cycleTime;
    UINT32 priority;
    UINT32 stackSize;
    UINT32 options;
    BEModule *pModule;
    std::string coreCategory;


    /** task variables */
    SINT32 taskId;
    UINT32 sysClkRate;
    UINT32 sampleTicks;
    UINT32 tickNext;
    SINT32 tickWait;

    /**
     ********************************************************************************
     * @brief      Task cycle work function
     *******************************************************************************/
    virtual void cycleWork(void) = 0;

    /**
     ********************************************************************************
     * @brief      Task delay function for event tasks
     *******************************************************************************/
    virtual void doEventDelay(void);

    /**
     ********************************************************************************
     * @brief      Wake up task that is waiting for an semaphore
     * 			   Prints a log message if function is not implemented for event tasks.
     *******************************************************************************/
    virtual void doTerminate(void);

    /**
     ********************************************************************************
     * @brief      Perform application specific tasks at the state EIO.
     *******************************************************************************/
    virtual void doEOI(void);

    /**
     ********************************************************************************
     * @brief      Adds a SmiRequest to be initialized
     *
     * @param[in]  pRequest		A pointer to the request
     *******************************************************************************/
    void addSmiRequest(SmiRequest *pRequest);

    /**
     ********************************************************************************
     * @brief   This function should be overwritten when the task needs
     *             information after terminating.
     *******************************************************************************/
    virtual void terminated();

    /**
     ********************************************************************************
     * @brief      This function will be called when cycle starts. This
     *             function inform the system about cycle start.
     *******************************************************************************/
    void cycleStart();

    /**
     ********************************************************************************
     * @brief      This function will be called when cycle ends. This
     *             function inform the system about cycle end.
     *******************************************************************************/
    void cycleEnd();

    /**
     ********************************************************************************
     * @brief      This function will be called when cycle ends and a cycle time is
     *             set. This function inform the system about cycle end.
     *******************************************************************************/
    void cycleDelay();

    /**
     ********************************************************************************
     * @brief      Set the current task state
     *
     * @param[in]  pState  A pointer to the current task state
     *******************************************************************************/
    void setState(BETaskState* const pState);

private:

    /**
     ********************************************************************************
     * @brief   Initialize the IO
     *
     * @throws     std::invalid_argument if already initialized
     *******************************************************************************/
    void initIO();

    /**
     ********************************************************************************
     * @brief   Helper function for different constructors
     *
     * @param[in]  pModule          A pointer to the module
     * @param[in]  sTaskName        The task name
     * @param[in]  cycleTime        The cycle time [ms] of the task. 0 = no delay
     * @param[in]  priority         Priority for the task
     * @param[in]  stackSize        Stack size for the task
     * @param[in]  pIOFactory       The factory for creating handle to the IO layer
     * @param[in]  coreCategory     The core category id to specify on which core to run
     *******************************************************************************/
    void init(BEModule *pModule, std::string sTaskName, int cycleTime, UINT32 priority,
            UINT32 stackSize, IOConfigurationFactory *pIOFactory, std::string coreCategory);

    /** list for and smi calls */
    std::vector<SmiRequest*>* pLocalSmiRequestList;

    /** list for Exporting to SVI */
    std::vector<SviExportDescriptor*>* pLocalSviExportList;

    std::vector<AbstractSviGroup*> *pGroups;

    /** Members for IO handling */
    MIOConfiguration *pIOConfiguration;

    /** Factory for creating IO setup. */
    IOConfigurationFactory *pIOFactory;

    explicit BETask(BETask const& that); /** no copy */

    BETask& operator=(BETask const&); /** no assign */

private:
    friend class InitializedState;
    friend class Task::RunState;
    friend class SuspendedState;
    friend class TerminatingState;
    friend class TerminatedState;
};
/** @} */

#endif  /*BETASK_HPP_*/
