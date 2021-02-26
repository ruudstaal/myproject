/**
 ********************************************************************************
 * @file     BETaskConfiguration.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Nov 4, 2015 1:06:19 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_TASK_BETASKCONFIGURATION_HPP_
#define BEFC_TASK_BETASKCONFIGURATION_HPP_

#include "IOConfigurationFactory.hpp"

class BEModule;

class BETaskConfiguration
{
public:
    enum TaskType
    {
        CYCLIC, EVENT
    };

    /**
     ********************************************************************************
     * @brief      This constructor should be used, when settings should be read from
     *             CRU. It will look for this part of the CRU:
     *             (ControlTask)
     *                 CycleTime = ?
     *                 Priority  = ?
     *
     *             This means that the cycletime and priority will be used for the
     *             Task
     *
     * @param[in]  pModule       The module, where the task is running
     * @param[in]  sTaskName     The name for the task
     *******************************************************************************/
    BETaskConfiguration(BEModule *pModule, std::string sTaskName);

    /**
     ********************************************************************************
     * @brief      This constructor should be used when creating event based tasks.
     *             This means, that the task will not be running cyclicly, but
     *             depends on how the doEventDelay is implemented on the BETask
     *             implementation.,
     *
     * @param[in]  pModule       The module, where the task is running
     * @param[in]  sTaskName     The name for the task
     * @param[in]  priority      The priority for the task
     *******************************************************************************/
    BETaskConfiguration(BEModule *pModule, std::string sTaskName, UINT32 priority);

    /**
     ********************************************************************************
     * @brief      This constructor should be used when creating a cyclic task.
     *
     * @param[in]  pModule       The module, where the task is running
     * @param[in]  sTaskName     The name for the task
     * @param[in]  priority      The priority for the task
     * @param[in]  cycleTime     The cycletime for the task in microseconds
     *******************************************************************************/
    BETaskConfiguration(BEModule *pModule, std::string sTaskName, UINT32 priority,
            UINT32 cycleTime);

    /** Getters and Setters **/
    TaskType getTaskType();

    std::string getTaskName();
    BEModule* getModule();

    UINT32 getPriority();
    void setPriority(UINT32 priority);

    UINT32 getStackSize();
    void setStackSize(UINT32 stackSize);

    UINT32 getCycleTime();
    void setCycleTime(UINT32 cycleTime);

    void setIOConfigurationFactory(IOConfigurationFactory *pFactory);
    IOConfigurationFactory* getIOConfigurationFactory();

    const std::string& getCoreCategory() const
    {
        return coreCategory;
    }

    void setCoreCategory(const std::string& coreCategory)
    {
        this->coreCategory = coreCategory;
    }

    ~BETaskConfiguration()
    {
    }


private:

    /**
     ********************************************************************************
     * @brief      this function will load the cycletime and priority from the CRU
     *
     *******************************************************************************/
    void initDataFromCRU();

    /**
     ********************************************************************************
     * @brief      This is a helper function to the constructors, which will set
     *             default values to its attributes
     *
     * @param[in]  pModule       The module, where the task is running
     * @param[in]  sTaskName     The name for the task
     *******************************************************************************/
    void init(BEModule *pModule, std::string sTaskName);

    bool isCycleTimeValid(UINT32 cycleTime);

    bool isPriorityValid(UINT32 prior);

    BETaskConfiguration(); //Should not be used..
    TaskType type;
    UINT32 cycleTime;
    UINT32 priority;
    UINT32 stackSize;
    BEModule *pModule;
    std::string sTaskName;
    IOConfigurationFactory *pIOFactory;

    std::string coreCategory;

};

#endif /* BEFC_TASK_BETASKCONFIGURATION_HPP_ */
