/**
 ********************************************************************************
 * @file     GM2XX.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid measurement module GM2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "GM2XX.hpp"
#include <cstring>

UINT64 GM2XX::csa_Selection[] =
{ 0, 1, };

/**-----------------------------------------------------------------*/
GM2XX::GM2XX() :
        BasicAnalogModule()
{
    /** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GM2XX::GM2XX(UINT32 ui32CardNumber) :
        BasicAnalogModule(ui32CardNumber)
{
    /** Check card type */
    checkCardType();

    init();
}

/**-----------------------------------------------------------------*/
GM2XX::~GM2XX()
{

}

/**-----------------------------------------------------------------*/
VOID GM2XX::init(VOID)
{
    memset(&m_Energy, 0, sizeof(m_Energy));
    memset(&m_EnergyReal, 0, sizeof(m_EnergyReal));
    memset(&m_BaseConfig, 0, sizeof(m_BaseConfig));
    memset(&m_SelectedValues, 0, sizeof(m_SelectedValues[eSlctAll]));
}

/**-----------------------------------------------------------------*/
VOID GM2XX::getMeasuredValues(SMeasuredValues_t* psValue)
{
    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, 0, (SINT32) psValue);
}

/**-----------------------------------------------------------------*/
GM2XX::SValues_t* GM2XX::getSelectedValues(ASelection_t *paSelection)
{
    PARAMETERLIST l_param;
    UINT64 l_ui64Selection = 0LL;

    l_param[0] = (SINT32) &m_SelectedValues;
    l_param[1] = (SINT32) &l_ui64Selection;

    /** if "ALL" is selected there is nothing else to do */
    if (TRUE == (*paSelection)[eSlctAll])
    {
        l_ui64Selection = 0;
    }
    else
    {
        /** if "ALL" is not selected loop through Bitmask an map */
        for (int iLoop = 0; iLoop < eSlctAll; ++iLoop)
        {
            if (TRUE == (*paSelection)[iLoop])
            {
                l_ui64Selection = l_ui64Selection | GM2XX::csa_Selection[iLoop];
            }
        }
    }

    BasicIoModule::doCommmand(MIO_CMD_GETSELECTEDVALUES, 0, &l_param, 2);
    return m_SelectedValues;
}

/**-----------------------------------------------------------------*/
GM2XX::SBaseConfig_t* GM2XX::getBaseConfig(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETCONFIG, 0, (SINT32) &m_BaseConfig);
    return &m_BaseConfig;
}

/**-----------------------------------------------------------------*/
VOID GM2XX::setEnergy(SEnergy_t* pValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETENERGY, 0, (SINT32) pValue);
}

/**-----------------------------------------------------------------*/
VOID GM2XX::setEnergy(SEnergyR_t* pValue)
{
    BasicIoModule::doCommmand(MIO_CMD_SETENERGYREAL, 0, (UINT32) pValue);
}

/**-----------------------------------------------------------------*/
GM2XX::SEnergy_t* GM2XX::getEnergy(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETENERGY, 0, (UINT32) &m_Energy);
    return &m_Energy;
}

/**-----------------------------------------------------------------*/

GM2XX::SEnergyR_t* GM2XX::getEnergyReal(VOID)
{
    BasicIoModule::doCommmand(MIO_CMD_GETENERGYREAL, 0, (UINT32) &m_EnergyReal);
    return &m_EnergyReal;
}

/**-----------------------------------------------------------------*/
VOID GM2XX::runEnergyMeasurement(BOOL8 b8Run)
{

    UINT32 l_ui32Temp = 0;

    if (TRUE == b8Run)
    {
        l_ui32Temp = 1;
    }

    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, 0, (SINT32) l_ui32Temp);
}

/**-----------------------------------------------------------------*/
BOOL8 GM2XX::getMeasurementState(VOID)
{
    UINT32 l_ui32Temp = 0;

    BasicIoModule::doCommmand(MIO_CMD_GETVALUES, 0, (SINT32) &l_ui32Temp);

    if (1 == l_ui32Temp)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
