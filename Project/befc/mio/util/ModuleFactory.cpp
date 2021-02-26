/**
 ********************************************************************************
 * @file     ModuleFactory.cpp
 * @author   madsen
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of ModuleFactory
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "ModuleFactory.hpp"
#include "ModuleBuilder.hpp"
#include "cards/DI/DI212.hpp"
#include "cards/DI/DI216.hpp"
#include "cards/DI/DI232.hpp"
#include "cards/DO/DO216.hpp"
#include "cards/DO/DO232.hpp"
#include "cards/DO/DOR206.hpp"
#include "cards/DIO/DIO216.hpp"
#include "cards/DIO/DIO232.hpp"
#include "cards/DIO/DIO2XX.hpp"
#include "cards/AI/AI204.hpp"
#include "cards/AI/AI20xSI.hpp"
#include "cards/AI/PTAI216.hpp"
#include "cards/AI/TI214.hpp"
#include "cards/AI/AIC212.hpp"
#include "cards/AI/DMS202.hpp"
#include "cards/AIO/AIO288.hpp"
#include "cards/AIO/AIO2xx.hpp"
#include "cards/AIO/GIO2xx.hpp"
#include "cards/AO/AO202.hpp"
#include "cards/AO/AO20XSI.hpp"
#include "cards/AO/AO208I.hpp"
#include "cards/NET/GM2XX.hpp"
#include "cards/NET/GMP232.hpp"
#include "cards/NET/GMP232x.hpp"
#include "cards/NET/GSP274.hpp"
#include "cards/FCT/CNT204.hpp"
#include "cards/FCT/PWM202.hpp"
#include "cards/FCT/ACR2XX.hpp"
#include "cards/FCT/ISI2XX.hpp"
#include "cards/FCT/RS204.hpp"
#include "cards/UFB/MBM201.hpp"
#include "cards/UFB/PN201.hpp"
#include "cards/UFB/CAN.hpp"
#include "cards/UFB/ECAT201.hpp"
#include "cards/UFB/DA3284C.hpp"
#if INCLUDE_OPCUAS
#include "cards/UFB/OPCUAS.hpp"
#endif
#if INCLUDE_60870
#include "cards/UFB/S60870_5.hpp"
#endif
#if INCLUDE_MMSCLNT
#include "cards/UFB/MMSCNLT.hpp"
#endif
#if INCLUDE_DNP3
#include "cards/UFB/DNP3.hpp"
#endif


/**********************************************************************
 * system includes
 **********************************************************************/
#include <string.h>
#include <msys_e.h>
#include <prof_e.h>
#include <stdio.h>

/**********************************************************************
 * static members
 **********************************************************************/

/**-----------------------------------------------------------------*/
ModuleFactory::ModuleFactory()
{
    m_ModuleMap = new ModuleFactory::ModuleConstructorMap_t();

    /**
     * Register all available Modules for Modulefactory
     */
    /** Analog Input */

    REGISTER_MODULE(BasicIoModule::TYPE_AI204, AI204);
    REGISTER_MODULE(BasicIoModule::TYPE_AI20XSI, AI20xSI);
    REGISTER_MODULE(BasicIoModule::TYPE_AIC212, AIC212);
    REGISTER_MODULE(BasicIoModule::TYPE_DMS202, DMS202);
    REGISTER_MODULE(BasicIoModule::TYPE_PTAI216, PTAI216);
    REGISTER_MODULE(BasicIoModule::TYPE_TI214, TI214);

    /** Analog Input/Output */
    REGISTER_MODULE(BasicIoModule::TYPE_AIO288, AIO288);
    REGISTER_MODULE(BasicIoModule::TYPE_AIO2XX, AIO2XX);
    REGISTER_MODULE(BasicIoModule::TYPE_GIO212, GIO2XX);

    /** Anlog Output */
    REGISTER_MODULE(BasicIoModule::TYPE_AO202, AO202);
    REGISTER_MODULE(BasicIoModule::TYPE_AO208, AO208I);
    REGISTER_MODULE(BasicIoModule::TYPE_AO20XSI, AO20XSI);
    /** Digital Input */
    REGISTER_MODULE(BasicIoModule::TYPE_DI212, DI212);
    REGISTER_MODULE(BasicIoModule::TYPE_DI216, DI216);
    REGISTER_MODULE(BasicIoModule::TYPE_DI232, DI232);

    /** Digital Input/Output */
    REGISTER_MODULE(BasicIoModule::TYPE_DIO216, DIO216);
    REGISTER_MODULE(BasicIoModule::TYPE_DIO232, DIO232);

    //Do not add the DIO280 module - the DIO2XX will handle it;
    REGISTER_MODULE(BasicIoModule::TYPE_DIO2XX, DIO2XX);

    /** Digital Output */
    REGISTER_MODULE(BasicIoModule::TYPE_DO216, DO216);
    REGISTER_MODULE(BasicIoModule::TYPE_DO232, DO232);
    REGISTER_MODULE(BasicIoModule::TYPE_DOR2XX, DOR206);

    /** Modules with special Functions */
    REGISTER_MODULE(BasicIoModule::TYPE_ACR2XX, ACR2XX);
    REGISTER_MODULE(BasicIoModule::TYPE_CNT204, CNT204);
    REGISTER_MODULE(BasicIoModule::TYPE_ISI222, ISI2XX);
    REGISTER_MODULE(BasicIoModule::TYPE_PWM202, PWM202);
    REGISTER_MODULE(BasicIoModule::TYPE_RS204, RS204);

    /** Modules for Netmeasurement */
    REGISTER_MODULE(BasicIoModule::TYPE_GMP232, GMP232);
    REGISTER_MODULE(BasicIoModule::TYPE_GMP232x, GMP232x);
    REGISTER_MODULE(BasicIoModule::TYPE_GSP274, GSP274);
    REGISTER_MODULE(BasicIoModule::TYPE_GM2XX, GM2XX);

    /** Modules for UFB */
    REGISTER_MODULE(BasicIoModule::TYPE_MBM201, MBM201);
    REGISTER_MODULE(BasicIoModule::TYPE_PN201, PN201);
    REGISTER_MODULE(BasicIoModule::TYPE_CAN, CAN);
    REGISTER_MODULE(BasicIoModule::TYPE_ECAT201, ECAT201);
    REGISTER_MODULE(BasicIoModule::TYPE_DA3284C, DA3284C);
#if INCLUDE_OPCUAS
    REGISTER_MODULE(BasicIoModule::TYPE_OPCUAS, OPCUAS);
#endif
#if INCLUDE_60870
    REGISTER_MODULE(BasicIoModule::TYPE_S60870_5, S60870_5);
#endif
#if INCLUDE_MMSCLNT
    REGISTER_MODULE(BasicIoModule::TYPE_MMSCNLT, MMSCNLT);
#endif
#if INCLUDE_DNP3
    REGISTER_MODULE(BasicIoModule::TYPE_DNP3, DNP3);
#endif
}

/**-----------------------------------------------------------------*/
ModuleFactory::~ModuleFactory()
{
    ModuleConstructorMap_t::iterator p;
    for (p = m_ModuleMap->begin(); p != m_ModuleMap->end(); ++p)
    {
        SAFE_DELETE(p->second);
    }
    m_ModuleMap->clear();
    SAFE_DELETE(m_ModuleMap);
}

/**-----------------------------------------------------------------*/
BasicIoModule * ModuleFactory::CreateModule(ModuleFactory::M1_MODULE_t *pCardInfo)
{
    BasicIoModule *pModule = NULL;
    ModuleFactory::ModuleConstructorMap_t::iterator l_ModuleMapIterator;

    /** try to find creator class for given module id */
    l_ModuleMapIterator = m_ModuleMap->find(pCardInfo->Type); //lint -e{1702}
    if (l_ModuleMapIterator != m_ModuleMap->end())
    {
        /** module creator class found, let it create a specific module and return the base class pointer */
        pModule = l_ModuleMapIterator->second->Create();

        if (NULL != pModule)
        {
            pModule->setCardNumber(pCardInfo->CardNb);
        }
    }
    return pModule;
}

/**-----------------------------------------------------------------*/
VOID ModuleFactory::RegisterModule(SINT32 si32ModuleId, BasicCreator *pModuleCreator)
{
    /** add module creator class to module class map */
    m_ModuleMap->insert(std::make_pair(si32ModuleId, pModuleCreator));
}

