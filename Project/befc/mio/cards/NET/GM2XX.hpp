/**
 ********************************************************************************
 * @file     GM2XX.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of grid measurement module GM2XX
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef GM2XX_HPP_
#define GM2XX_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/

/**********************************************************************
 * project includes
 **********************************************************************/
#include "../../common/base/BasicAnalogModule.hpp"

/**
 * @brief Netmeasurement Module GM230
 *
 * Channels : 14
 */
class GM2XX: public BasicAnalogModule
{

    /**
     * Selection Table for Do Command
     * getSelectedValues
     */
    static UINT64 csa_Selection[64];

public:

    typedef UINT32 SEnergy_t;
    typedef REAL32 SEnergyR_t;
    typedef UINT32 SMeasuredValues_t;
    typedef UINT32 SBaseConfig_t;
    typedef UINT32 SValues_t;

    /**
     * This enum is used for Indexing through
     * csa_Selection[]
     * do not change the order
     */
    typedef enum
    {
        MP1_U_L1L2_RMS = 0,
        MP1_U_L2L3_RMS = 1,
        MP1_U_L3L1_RMS = 2,
        MP1_U_L1N_RMS = 3,
        MP1_U_L2N_RMS = 4,
        MP1_U_L3N_RMS = 5,
        MP1_I_L1_RMS = 6,
        MP1_I_L2_RMS = 7,
        MP1_I_L3_RMS = 8,
        MP1_I_N_RMS = 9,
        MP1_f = 10,
        MP1_Phi_U1I1 = 11,
        MP1_Phi_U2I2 = 12,
        MP1_Phi_U3I3 = 13,
        Phi_U1U2 = 14,
        Phi_U2U3 = 15,
        Phi_U1U3 = 16,
        MP1_PF_sum = 17,
        MP1_PF_L1 = 18,
        MP1_PF_L2 = 19,
        MP1_PF_L3 = 20,
        MP1_P_sum = 21,
        MP1_P_L1 = 22,
        MP1_P_L2 = 23,
        MP1_P_L3 = 24,
        MP1_Q_sum = 25,
        MP1_Q_L1 = 26,
        MP1_Q_L2 = 27,
        MP1_Q_L3 = 28,
        MP1_S_sum = 29,
        MP1_S_L1 = 30,
        MP1_S_L2 = 31,
        MP1_S_L3 = 32,
        MP1_RotDir_U = 33,
        MP2_I_L1_RMS = 34,
        MP2_I_L2_RMS = 35,
        MP2_I_L3_RMS = 36,
        MP2_I_N_RMS = 37,
        MP2_Phi_U1I1 = 38,
        MP2_Phi_U2I2 = 39,
        MP2_Phi_U3I3 = 40,
        MP2_PF_sum = 41,
        MP2_PF_L1 = 42,
        MP2_PF_L2 = 43,
        MP2_PF_L3 = 44,
        MP2_P_sum = 45,
        MP2_P_L1 = 46,
        MP2_P_L2 = 47,
        MP2_P_L3 = 48,
        MP2_Q_sum = 49,
        MP2_Q_L1 = 50,
        MP2_Q_L2 = 51,
        MP2_Q_L3 = 52,
        MP2_S_sum = 53,
        MP2_S_L1 = 54,
        MP2_S_L2 = 55,
        MP2_S_L3 = 56,
        eSlctAll = 57
    } ESelection_t;

    /**
     * Selection Array for getSelectedValues CALL
     * see eSelctXXX - Constants
     */
    typedef BOOL8 ASelection_t[GM2XX::eSlctAll + 1];

    /**
     * Modes of Module
     * Can only be set during Bootup!
     */
    typedef enum
    {
        eMode3Wire = 0, eMode4Wire = 1
    } EMode_t;

    /**
     * Constructor
     *
     * @throws a MIOexception when card does not match class
     */
    GM2XX();

    /**
     * Constructor
     *
     * @param ui32CardNumber - configured Cardnumber
     *
     * @throws a MIOexception when card does not match class
     */
    explicit GM2XX(UINT32 ui32CardNumber);

    /**
     * Default Destructor
     */
    virtual ~GM2XX();

    /**
     * Set EnergyCounter
     * Values are from Type UINT64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(SEnergy_t *pValue);

    /**
     * Set EnergyCounter
     * Values are from Type REAL64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when writing to card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID setEnergy(SEnergyR_t *pValue);

    /**
     * Read EnergyCounter
     * Values are from Type UINT64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SEnergy_t* getEnergy(VOID);

    /**
     * Read EnergyCounter
     * Values are from Type REAL64
     *
     * @param pValue - pointer to variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SEnergyR_t* getEnergyReal(VOID);

    /**
     * Read Base Config of Module
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SBaseConfig_t* getBaseConfig();

    /**
     * Read defined values
     *
     * @param paSelection
     * @param psValues - pointer to variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    SValues_t* getSelectedValues(ASelection_t *paSelection);

    /**
     * Read all measured values
     *
     * @param psValue - pointer to variable
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID getMeasuredValues(SMeasuredValues_t *psValue);

    /**
     * Start Measurement
     *
     * @param b8Run - TRUE = Start Measurement
     *                FALSE = Stop
     *
     * @throws a MIOexception when reading from card fails,
     * or a MIOexception if pointer to card is invalid
     */
    VOID runEnergyMeasurement(BOOL8 b8Run);

    /**
     * Read state of measurement
     *
     * @returns TRUE = Start Measurement \n
     *          FALSE = Stop
     *
     */
    BOOL8 getMeasurementState(VOID);

protected:

    /**
     * get Type of Module
     * see BasicIoModule::TYPE_xxxxx
     *
     * @returns > 0 - Type
     */
    SINT32 getTypeId(VOID)
    {
        return BasicIoModule::TYPE_GM2XX;
    }
private:
    /**
     * Initialize all values at construction.
     */
    VOID init(VOID);

    SEnergy_t m_Energy;
    SEnergyR_t m_EnergyReal;
    SBaseConfig_t m_BaseConfig;
    UINT32 m_SelectedValues[eSlctAll];
};

#endif /** GM2XX_HPP_ */
