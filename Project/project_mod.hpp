/**
 ********************************************************************************
 * @file     template_mop.hpp
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

/** Avoid problems with multiple inclusion */
#ifndef PROJECT_MOD_HPP_
#define PROJECT_MOD_HPP_

/** Includes */
#include <BEModule.hpp>

/**
 * @addtogroup APP-MOD
 * @{
 */

class project_mod: public BEModule
{
public:
    project_mod();
    explicit project_mod(VOIDFUNCPTR fpPanicHandler);
    ~project_mod();

protected:
    virtual BOOL8 doInit(VOID);

private:
};

/** @} */

#endif  /** PROJECT_MOD_HPP_ */
