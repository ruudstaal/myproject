/**
 ********************************************************************************
 * @file     ProcessImageIOStrategy.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ProcessImageIOStrategy
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef PROCESSIMAGEIOSTRATEGY_HPP_
#define PROCESSIMAGEIOSTRATEGY_HPP_

#include "IOStrategy.hpp"
#include "../mio/util/processImage/ProcessImage.hpp"

class ProcessImageIOStrategy: public IOStrategy
{
public:
    void registerCard(BasicIoModule *pIOModule);
    void readInput();
    void writeOutput();

    explicit ProcessImageIOStrategy(std::string moduleName);
    ~ProcessImageIOStrategy();

private:
    ProcessImage *pProcessImage;
};

#endif /* PROCESSIMAGEIOSTRATEGY_HPP_ */
