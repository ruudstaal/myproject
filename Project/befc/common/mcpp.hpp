/**
 ********************************************************************************
 * @file     mcpp.hpp
 * @author   eckrodt
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 25, 2013 05:40:00 AM 11:00:00 $
 *
 * @brief    This file implements helper function for BEFC.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef MCPP_HPP_
#define MCPP_HPP_

#include <typeinfo>
#include <sstream>

#include <mtypes.h>
#include <log_e.h>

/**
 * @addtogroup COM
 * @{
 */

#define CLASSNAME (typeid(this).name())

#define info(s){std::stringstream log; log << CLASSNAME << "::" << __FUNCTION__ << ": " << s; log_Info("%s",log.str().c_str()); }
#define warn(s){std::stringstream log; log << CLASSNAME << "::" << __FUNCTION__ << ": " << s; log_Wrn("%s",log.str().c_str()); }
#define error(s){std::stringstream log; log << CLASSNAME << "::" << __FUNCTION__ << ": " << s; log_Err("%s",log.str().c_str()); }

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }

/** @} */

#endif  /** MCPP_HPP_*/
