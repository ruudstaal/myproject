/**
 ********************************************************************************
 * @file     BasicCreator.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BasicCreator
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef BASICCREATOR_HPP_
#define BASICCREATOR_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <BeTypes.h>
#include <mtypes.h>

/**********************************************************************
 * project includes
 **********************************************************************/

/**********************************************************************
 * declarations
 **********************************************************************/
class BasicIoModule;


/**********************************************************************
 * class definition
 **********************************************************************/

/**
 *@brief  Base Class for Creator Pattern used in
 *@brief  ModuleFactory
 *
 */
class BasicCreator
{

public:

    /**
     * Default Constructor
     */
	BasicCreator(){};

    /**
     * Default Destructor
     */
	virtual ~BasicCreator(){};

	/**
	 * Create a new module class instance and return it.
	 * This method must be implemented by all derived module creator classes.
	 * @return              Pointer to new module instance.
	 */
	virtual BasicIoModule * Create(VOID) = 0;
};

#endif /* BASICCREATOR_HPP_ */
