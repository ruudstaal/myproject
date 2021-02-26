/**
 ********************************************************************************
 * @file     MIOerrorcode.cpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of MIOerrorcode
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include "MIOerrorcode.hpp"

/**
 * default error code strings
 */
const std::string MIOerrorcode::MIO_ER_OK_STR = 			"No error";
const std::string MIOerrorcode::MIO_ER_FAIL_STR = 			"General error";
const std::string MIOerrorcode::MIO_ER_BADCHAN_STR = 		"Channel not valid";
const std::string MIOerrorcode::MIO_ER_BADMODE_STR = 		"Mode or Type not valid";
const std::string MIOerrorcode::MIO_ER_BUSY_STR = 			"Device is busy";
const std::string MIOerrorcode::MIO_ER_BADTEST_STR = 		"HwTest failed";
const std::string MIOerrorcode::MIO_ER_BADCMD_STR = 		"Command not supported";
const std::string MIOerrorcode::MIO_ER_BADIDREG_STR = 		"ID Register not valid";
const std::string MIOerrorcode::MIO_ER_BADCONF_STR = 		"Bad configuration";
const std::string MIOerrorcode::MIO_ER_BADPARM_STR = 		"Bad parameter";
const std::string MIOerrorcode::MIO_ER_TIMEOUT_STR = 		"Timeout";
const std::string MIOerrorcode::MIO_ER_BADFUNC_STR = 		"Function not supported";
const std::string MIOerrorcode::MIO_ER_BADWRITE_STR = 		"Error in write";
const std::string MIOerrorcode::MIO_ER_NOWRITE_STR = 		"Write on input channel";
const std::string MIOerrorcode::MIO_ER_BADCALIB_STR = 		"Bad calibration data";
const std::string MIOerrorcode::MIO_ER_BADPLAUS_STR = 		"Plausibility test failed";
const std::string MIOerrorcode::MIO_ER_BADREAD_STR = 		"Error in read";
const std::string MIOerrorcode::MIO_ER_REBOOT_STR = 		"Reboot is required";
const std::string MIOerrorcode::MIO_ER_DISABLED_STR = 		"Channel is disabled";
const std::string MIOerrorcode::MIO_ER_WRONGSTATE_STR = 	"Invalid state for this function";
const std::string MIOerrorcode::MIO_ER_BADCARD_STR = 		"Card not valid";
const std::string MIOerrorcode::MIO_ER_BUSFAIL_STR = 		"Bus error";
const std::string MIOerrorcode::MIO_ER_NODATA_STR = 		"No data available";
const std::string MIOerrorcode::MIO_ER_OUTOFMEM_STR = 		"No memory available";
const std::string MIOerrorcode::MIO_ER_NOFPTASK_STR = 		"No floating point operations allowed";
const std::string MIOerrorcode::MIO_ER_MODNOTINIT_STR = 	"Module is not initialized";
const std::string MIOerrorcode::MIO_ER_BADHANDLE_STR = 		"Bad handle";
const std::string MIOerrorcode::MIO_ER_LSTINFPGAFULL_STR = 	"The list in the FPGA is full";
const std::string MIOerrorcode::MIO_ER_WRONGITEMSIZE_STR = 	"The DMA item has a wrong size";
const std::string MIOerrorcode::MIO_ER_SEMCREATE_STR = 		"Error creating a semaphore";
const std::string MIOerrorcode::MIO_ER_SEMTAKE_STR = 		"Error / Timeout taking a semaphore";
const std::string MIOerrorcode::MIO_ER_WRONGMEMAREA_STR = 	"Wrong memory area passed to function";
const std::string MIOerrorcode::MIO_ER_BADALIGNMENT_STR = 	"Bad alignment";
const std::string MIOerrorcode::MIO_ER_UPDATELISTFULL_STR = "Update list is full";
const std::string MIOerrorcode::MIO_ER_WRONGPRIO_STR = 		"Wrong priority";
const std::string MIOerrorcode::MIO_ER_CHANNOTMAPPED_STR = 	"Channel is not mapped";
const std::string MIOerrorcode::MIO_ER_NOPIDRVID_STR = 		"A process image module handle was expected but not given";
const std::string MIOerrorcode::MIO_ER_HANDLEINUSE_STR = 	"The actual handle is already in use";
const std::string MIOerrorcode::MIO_ER_BIOSFAIL_STR = 		"BIOS on module not running";
const std::string MIOerrorcode::MIO_ER_DOWNGRADE_STR = 		"Software downgrade";
const std::string MIOerrorcode::MIO_ER_BADFIRMWARE_STR = 	"Firmware doesn't fit on module";
const std::string MIOerrorcode::MIO_ER_BADTYPE_STR = 		"Module type and software type are not compatible";
const std::string MIOerrorcode::MIO_ER_NOAPP_STR = 			"Application not found/registered";
const std::string MIOerrorcode::MIO_ER_NOSCALEINF_STR = 	"No scale information given for that channel";
const std::string MIOerrorcode::MIO_ER_WRONGFUNCTYPE_STR = 	"Wrong function type";
const std::string MIOerrorcode::MIO_ER_NOTPRESENT_STR = 	"Channel does not exist";
const std::string MIOerrorcode::MIO_ER_OVERFLOW_STR = 		"Channel value overflow";

std::string MIOerrorcode::errorCodesLookup(SINT32 errorCode)
{
	switch(errorCode){
		case MIO_ER_OK:
			return MIO_ER_OK_STR;
		case MIO_ER_FAIL:
			return MIO_ER_FAIL_STR;
		case MIO_ER_BADCHAN:
			return MIO_ER_BADCHAN_STR;
		case MIO_ER_BADMODE:
			return MIO_ER_BADMODE_STR;
		case MIO_ER_BUSY:
			return MIO_ER_BUSY_STR;
		case MIO_ER_BADTEST:
			return MIO_ER_BADTEST_STR;
		case MIO_ER_BADCMD:
			return MIO_ER_BADCMD_STR;
		case MIO_ER_BADIDREG:
			return MIO_ER_BADIDREG_STR;
		case MIO_ER_BADCONF:
			return MIO_ER_BADCONF_STR;
		case MIO_ER_BADPARM:
			return MIO_ER_BADPARM_STR;
		case MIO_ER_TIMEOUT:
			return MIO_ER_TIMEOUT_STR;
		case MIO_ER_BADFUNC:
			return MIO_ER_BADFUNC_STR;
		case MIO_ER_BADWRITE:
			return MIO_ER_BADWRITE_STR;
		case MIO_ER_NOWRITE:
			return MIO_ER_NOWRITE_STR;
		case MIO_ER_BADCALIB:
			return MIO_ER_BADCALIB_STR;
		case MIO_ER_BADPLAUS:
			return MIO_ER_BADPLAUS_STR;
		case MIO_ER_BADREAD:
			return MIO_ER_BADREAD_STR;
		case MIO_ER_REBOOT:
			return MIO_ER_REBOOT_STR;
		case MIO_ER_DISABLED:
			return MIO_ER_DISABLED_STR;
		case MIO_ER_WRONGSTATE:
			return MIO_ER_WRONGSTATE_STR;
		case MIO_ER_BADCARD:
			return MIO_ER_BADCARD_STR;
		case MIO_ER_BUSFAIL:
			return MIO_ER_BUSFAIL_STR;
		case MIO_ER_NODATA:
			return MIO_ER_NODATA_STR;
		case MIO_ER_OUTOFMEM:
			return MIO_ER_OUTOFMEM_STR;
		case MIO_ER_NOFPTASK:
			return MIO_ER_NOFPTASK_STR;
		case MIO_ER_MODNOTINIT:
			return MIO_ER_MODNOTINIT_STR;
		case MIO_ER_BADHANDLE:
			return MIO_ER_BADHANDLE_STR;
		case MIO_ER_LSTINFPGAFULL:
			return MIO_ER_LSTINFPGAFULL_STR;
		case MIO_ER_WRONGITEMSIZE:
			return MIO_ER_WRONGITEMSIZE_STR;
		case MIO_ER_SEMCREATE:
			return MIO_ER_SEMCREATE_STR;
		case MIO_ER_SEMTAKE:
			return MIO_ER_SEMTAKE_STR;
		case MIO_ER_WRONGMEMAREA:
			return MIO_ER_WRONGMEMAREA_STR;
		case MIO_ER_BADALIGNMENT:
			return MIO_ER_BADALIGNMENT_STR;
		case MIO_ER_UPDATELISTFULL:
			return MIO_ER_UPDATELISTFULL_STR;
		case MIO_ER_WRONGPRIO:
			return MIO_ER_WRONGPRIO_STR;
		case MIO_ER_CHANNOTMAPPED:
			return MIO_ER_CHANNOTMAPPED_STR;
		case MIO_ER_NOPIDRVID:
			return MIO_ER_NOPIDRVID_STR;
		case MIO_ER_HANDLEINUSE:
			return MIO_ER_HANDLEINUSE_STR;
		case MIO_ER_BIOSFAIL:
			return MIO_ER_BIOSFAIL_STR;
		case MIO_ER_DOWNGRADE:
			return MIO_ER_DOWNGRADE_STR;
		case MIO_ER_BADFIRMWARE:
			return MIO_ER_BADFIRMWARE_STR;
		case MIO_ER_BADTYPE:
			return MIO_ER_BADTYPE_STR;
		case MIO_ER_NOAPP:
			return MIO_ER_NOAPP_STR;
		case MIO_ER_NOSCALEINF:
			return MIO_ER_NOSCALEINF_STR;
		case MIO_ER_WRONGFUNCTYPE:
			return MIO_ER_WRONGFUNCTYPE_STR;
		case MIO_ER_NOTPRESENT:
			return MIO_ER_NOTPRESENT_STR;
		case MIO_ER_OVERFLOW:
			return MIO_ER_OVERFLOW_STR;
		default:
			return "";
	}
	return "";
}




