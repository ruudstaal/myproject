/**
 ********************************************************************************
 * @file     MixedIOStrategy.hpp
 * @author   madsen
 * @version  $Revision: 000 $ $LastChangedBy: XXXX $
 * @date     $LastChangeDate: Dec 10, 2015 1:07:29 PM 11:00:00 $
 *
 * @brief
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2011
 *******************************************************************************/

#ifndef BEFC_MIO_CONFIGURATION_MIXEDIOSTRATEGY_HPP_
#define BEFC_MIO_CONFIGURATION_MIXEDIOSTRATEGY_HPP_

#include <IOStrategy.hpp>
#include "BETask.hpp"
#include "ProcessImageIOStrategy.hpp"
#include "StdIOStrategy.hpp"

class MixedIOStrategy: public IOStrategy
{
public:
    MixedIOStrategy(BETask *pTask);

    void registerCard(BasicIoModule *pIOModule);
    void readInput();
    void writeOutput();

    virtual ~MixedIOStrategy();

private:
    ProcessImageIOStrategy *pPiStrategy;
    StdIOStrategy *pStdStrategy;
};

#endif /* BEFC_MIO_CONFIGURATION_MIXEDIOSTRATEGY_HPP_ */
