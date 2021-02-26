/**
 ********************************************************************************
 * @file     BEFCTypes.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Apr 17, 2013 12:00:00 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BEFCTYPES_HPP_
#define BEFCTYPES_HPP_

#include <mtypes.h>
#include <string>
#include <map>

/**
 * @addtogroup COM
 * @{
 */

typedef SINT32 (**pLib)(VOID); /**< Function pointer to SVI in other SW-module */
typedef std::map<std::string, pLib> TStrLibMap;
typedef std::pair<std::string, pLib> TStrLibPair;

/** Defines */
#define DEF_TASK_PRIO    128                 /** Default priority for all tasks */
#define DEF_STACK_SIZE   10000               /**< Stack size of the user-task */
#define SMI_SRV_PRIO     120                 /**< Priority of the SMI task (bTask) */
#define SMI_SRV_STACK    10000               /**< Stack size of the SMI-task */
/** @} */

#endif  /**BEFCTYPES_HPP_*/
