/**
********************************************************************************
* @file     exceptions.hpp
* @author   gravers
* @version  $Revision: 000 $
* @date     $LastChangeDate: Jun 28, 2013 8:57:00 PM 11:00:00 $
*
* @brief    Common exception class for memory allocation exception, when using
*           the new operator.
*
********************************************************************************
* COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
*******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

/**
 * @addtogroup EXP
 * @{
 */

namespace bae
{
class memory_exc
{
public:
    const char* what() const throw ()
    {
        return "bad_alloc";
    }
};
}

/** @} */

#endif  /**EXCEPTIONS_HPP_*/
