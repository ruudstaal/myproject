/**
 ********************************************************************************
 * @file     AutomaticConfiguration.hpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of AutomaticConfiguration
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef BEFC_MIO_CONFIGURATION_AUTOMATICCONFIGURATION_HPP_
#define BEFC_MIO_CONFIGURATION_AUTOMATICCONFIGURATION_HPP_

#include <vector>
#include "IOStrategy.hpp"
#include <configuration/ManualConfiguration.hpp>
#include "M1Scan.hpp"

class AutomaticConfiguration: public ManualConfiguration
{
public:
    explicit AutomaticConfiguration(IOStrategy *pIOStrategy);
    ~AutomaticConfiguration();

    BasicChannel* getChannel(std::string symbolicName);

protected:
    void init();

private:
    AutomaticConfiguration();
    M1Scan *pScan;
};

#endif /* BEFC_MIO_CONFIGURATION_AUTOMATICCONFIGURATION_HPP_ */
