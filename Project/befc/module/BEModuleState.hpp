/**
 ********************************************************************************
 * @file     BEModuleState.hpp
 * @author   gravers
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Feb 12, 2013 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of BEModuleState
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

/** Avoid problems with multiple inclusion */
#ifndef BEMODULESTATE_HPP_
#define BEMODULESTATE_HPP_

#include <string>
#include <mtypes.h>

/**
 * @addtogroup MOD
 * @{
 */

class BEModule;

class BEModuleState {
public:
	/**
	 ********************************************************************************
	 * @brief      Create an instance BEModuleState
	 *
	 * @param[in]  sStateName       Name of the state
	 * @param[in]  resState         Resource handler state related to this state (RES_S_*)
	 *******************************************************************************/
	BEModuleState(std::string sStateName, UINT32 resState);

	virtual ~BEModuleState() {};

	static BEModuleState * const STATE_INIT;
	static BEModuleState * const STATE_EOI;
	static BEModuleState * const STATE_RUN;
	static BEModuleState * const STATE_STOP;
	static BEModuleState * const STATE_CFG;
	static BEModuleState * const STATE_DEINIT;
	static BEModuleState * const STATE_RESET;
	static BEModuleState * const STATE_ERROR;

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for init state
	 *
	 *             Throws illegal state exception
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 * @throws     IllegalStateException
	 *******************************************************************************/
	virtual void doInit(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behavior for end of init state
	 *
	 *             Throws illegal state exception
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 * @throws     IllegalStateException
	 *******************************************************************************/
	virtual void doEOI(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for run state
	 *
	 *             Resume all suspended application tasks
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 *******************************************************************************/
	virtual void doRun(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for stop state
	 *
	 *             Throws illegal state exception
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 * @throws     IllegalStateException
	 *******************************************************************************/
	virtual void doStop(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for new cfg state
	 *
	 *             Reads configuration (CRU) from mconfig.ini
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 *******************************************************************************/
	virtual void doCfgNew(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for deinit state
	 *
	 *             Deinitialize and terminate all application tasks in the software
	 *             module
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 *******************************************************************************/
	virtual void doDeInit(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Default behaviour for reset state
	 *
	 *             - Deinitialize all SMI request, except BE standard SMI
	 *             - Deinitialize all exported SVI variables, and SVI server
	 *             - Deinitialize and terminate all application tasks in the software
	 *               module
	 *             - Initialize all application tasks
	 *             - Initialize all module specific SMI requests
	 *             - Initialize SVI server and export variables
	 *
	 * @param[in]  pModule         Pointer to BEModule class
	 *******************************************************************************/
	virtual void doReset(BEModule *pModule);

	/**
	 ********************************************************************************
	 * @brief      Helper funtion to get exception string for IllegalStateException
	 *
	 * @param[in]  sFunctionName            Name of the calling function
	 * @retval     String with message for IllegalState Exception
	 *******************************************************************************/
	std::string getIllegalStateString(std::string sFunctionName);

	UINT32 getResState(void)              {return resState;}

	std::string getName()                      {return name;}

	/**
	 ********************************************************************************
	 * @brief      Operator '=='
	 *
	 *             Compare the name for two module states to evaluate if they are
	 *             equal
	 *
	 * @param[in]  other            BEModuleState to be compared
	 * @retval     true             BEModuleStates are equal
	 * @retval     false            BEModuleStates are not equal
	 *******************************************************************************/
	bool operator==(const BEModuleState &other) const;

	/**
	 ********************************************************************************
	 * @brief      Operator '!='
	 *
	 *             Compare the name for two module states to evaluate if they are
	 *             unequal
	 *
	 * @param[in]  other            BEModuleState to be compared
	 * @retval     true             BEModuleStates are not equal
	 * @retval     false            BEModuleStates are equal
	 *******************************************************************************/
	bool operator!=(const BEModuleState &other) const;

private:
	BEModuleState(){resState = 0;};

	std::string name;
	UINT32 resState;
};
/** @} */

#endif  /** BEMODULESTATE_HPP_*/
