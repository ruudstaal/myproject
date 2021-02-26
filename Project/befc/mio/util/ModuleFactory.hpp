/**
 ********************************************************************************
 * @file     ModuleFactory.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ModuleFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MODULEFACTORY_HPP_
#define MODULEFACTORY_HPP_

/**
 * Macro to register modules in module factory.
 */
#define REGISTER_MODULE(ModuleName, ClassName)     \
    ModuleFactory::RegisterModule(ModuleName, new ModuleBuilder<ClassName>)

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mtypes.h>
#include <mio_e.h>

#include <map>
#include <string>

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../mio/common/base/BasicIoModule.hpp"

/**********************************************************************
 * declarations
 **********************************************************************/
class BasicCreator;

/**
 *@brief  Contains all registered Constructors of Modules
 *@brief  Modules which are not known can not be build!
 *
 */

class ModuleFactory
{

public:

    /**
     * Typedefintion of a single Module
     */
    typedef MIO_CARDINF M1_MODULE_t;

    /**
     * List of all available constructors
     */
    typedef std::map<SINT32, BasicCreator*> ModuleConstructorMap_t;

private:

    /**
     * All registered module classes with its corresponding creator class are stored here.
     * If a new module shall be created with CreateModule(), a lookup of the class
     * name is done in this map and the corresponding creator class method is called.
     */
    ModuleConstructorMap_t *m_ModuleMap;

    ModuleFactory(const ModuleFactory& that); /** no copy */
    ModuleFactory& operator=(ModuleFactory const&); /** no assign */

public:

    ModuleFactory();

    ~ModuleFactory();

    /**
     * Create a new module instance and return a pointer to it.
     *
     * @param               pCardInfo - Pointer to ModuleInfo .
     *
     * @return              Pointer to created module instance, or NULL if class name was not found.
     */
    BasicIoModule * CreateModule(ModuleFactory::M1_MODULE_t *pCardInfo);

    /**
     * Register a new module class with the corresponding module creator instance.
     * @param               si32ModuleId  - Module Type as Integer.
     * @param               pModuleCreator - Pointer to module creator class.
     */
    VOID RegisterModule(SINT32 si32ModuleId, BasicCreator *pModuleCreator);

};

#endif /** MODULEFACTORY_HPP_ */
