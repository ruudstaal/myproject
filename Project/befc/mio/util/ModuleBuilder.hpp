/**
 ********************************************************************************
 * @file     ModuleBuilder.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ModuleBuilder
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MODULEBUILDER_H_
#define MODULEBUILDER_H_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "BasicCreator.hpp"

/**********************************************************************
 * declarations
 **********************************************************************/

/**********************************************************************
 * class definition
 **********************************************************************/

/**
 *@brief  Template to create specific Modules
 *
 */
template<class T>
class ModuleBuilder: public BasicCreator
{
public:
    /**
     * Default Constructor
     */
    ModuleBuilder()
    {
    }
    ;

    /**
     * Default Destructor
     */
    virtual ~ModuleBuilder()
    {
    }
    ;

    /**
     * Create a new module class instance and return it.
     *
     * @return              Pointer to new module instance.
     */
    virtual BasicIoModule * Create(VOID)
    {
        return new T;
    }

};

#endif /* MODULECREATOR_H_ */
