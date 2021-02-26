/**
 ********************************************************************************
 * @file     IOStrategy.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of IOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef IOSTRATEGY_HPP_
#define IOSTRATEGY_HPP_

#include "mtypes.h"
#include "vector"

class BasicDigitalModule;
class BasicIoModule;

/**
 ********************************************************************************
 * @brief     The classes which inherits from this base class has the responsibility
 * 			  to implement the behaviour of how to handle IO at each cycle. This is
 * 			  done to separate the behaviour of when ProcessImage is enabled or not.
 * 			  (or maybe some third/fourth option)
 *******************************************************************************/
class IOStrategy
{

public:

    /**
     ********************************************************************************
     * @brief     This function marks the module as dirty, and when the writeOutput()
     * 			  function is called, the values of that module will be written to HW
     *
     * @param[in]  pIOModule  Pointer to the module to mark as dirty
     *******************************************************************************/
    void markModuleAsDirty(BasicIoModule *pIOModule);

    /**
     ********************************************************************************
     * @brief     This function registers the card. This means, that it will get the
     * 			  driver id from the mio system functions, so that values can be read.
     *
     * @param[in]  pIOModule  Pointer to the module to register
     *******************************************************************************/
    virtual void registerCard(BasicIoModule *pIOModule) = 0;

    /**
     ********************************************************************************
     * @brief     This function should be called in the beginning of the task cycle.
     * 			  This will update values on all the modules in memory, which are
     * 			  registered.
     * @throws    MIOException if anything goes wrong during reading the output
     *******************************************************************************/
    virtual void readInput() = 0;

    /**
     ********************************************************************************
     * @brief     This function should be called in the end of the task cycle.
     * 			  This will write the values to the HW modules.
     *
     * @throws    MIOException if anything goes wrong during writing the output
     *******************************************************************************/
    virtual void writeOutput() = 0;

    IOStrategy();

    virtual ~IOStrategy();

protected:

    std::vector<BasicIoModule*>* getDirtyList();

    void clearDirtyList();

    std::vector<BasicIoModule*> *m_pRegistredCards;

    void readDigitalValues(BasicDigitalModule *pModule);

    void writeDigitalValues(BasicDigitalModule *pModule);

private:

    std::vector<BasicIoModule*> *m_pDirtyCards;

    explicit IOStrategy(IOStrategy const& that); /** no copy */
    IOStrategy& operator=(IOStrategy const&); /** no assign */
};

#endif /* IOSTRATEGY_HPP_ */
