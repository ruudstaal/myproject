/**
 ********************************************************************************
 * @file     StdIOStrategy.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of StdIOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "IOStrategy.hpp"

#ifndef STDIOSTRATEGY_HPP_
#define STDIOSTRATEGY_HPP_

class StdIOStrategy: public IOStrategy
{
public:
    void registerCard(BasicIoModule *pIOModule);
    void readInput();
    void writeOutput();

    StdIOStrategy();
    ~StdIOStrategy();
};

#endif /* STDIOSTRATEGY_HPP_ */
