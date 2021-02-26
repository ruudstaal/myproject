/**
 ********************************************************************************
 * @file     MIOerrorcode.hpp
 * @author   Patrick
 * @version  $Revision: 000 $
 * @date     $LastChangeDate: Jan 7, 2014 9:50:58 AM 11:00:00 $
 *
 * @brief    Implementation of MIOerrorcode
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#ifndef MIOERRORCODE_HPP_
#define MIOERRORCODE_HPP_

/**********************************************************************
 * system includes
 **********************************************************************/
#include <mio_e.h>
#include <string>

class MIOerrorcode
{
public:
    /**
	 * Creating error code string from mio_DoCmd error code
	 * @param errorCode     mio_DoCmd error code
	 *
	 */
	static std::string errorCodesLookup(SINT32 errorCode);

	static const std::string MIO_ER_OK_STR;
	static const std::string MIO_ER_FAIL_STR;
	static const std::string MIO_ER_BADCHAN_STR;
	static const std::string MIO_ER_BADMODE_STR;
	static const std::string MIO_ER_BUSY_STR;
	static const std::string MIO_ER_BADTEST_STR;
	static const std::string MIO_ER_BADCMD_STR;
	static const std::string MIO_ER_BADIDREG_STR;
	static const std::string MIO_ER_BADCONF_STR;
	static const std::string MIO_ER_BADPARM_STR;
	static const std::string MIO_ER_TIMEOUT_STR;
	static const std::string MIO_ER_BADFUNC_STR;
	static const std::string MIO_ER_BADWRITE_STR;
	static const std::string MIO_ER_NOWRITE_STR;
	static const std::string MIO_ER_BADCALIB_STR;
	static const std::string MIO_ER_BADPLAUS_STR;
	static const std::string MIO_ER_BADREAD_STR;
	static const std::string MIO_ER_REBOOT_STR;
	static const std::string MIO_ER_DISABLED_STR;
	static const std::string MIO_ER_WRONGSTATE_STR;
	static const std::string MIO_ER_BADCARD_STR;
	static const std::string MIO_ER_BUSFAIL_STR;
	static const std::string MIO_ER_NODATA_STR;
	static const std::string MIO_ER_OUTOFMEM_STR;
	static const std::string MIO_ER_NOFPTASK_STR;
	static const std::string MIO_ER_MODNOTINIT_STR;
	static const std::string MIO_ER_BADHANDLE_STR;
	static const std::string MIO_ER_LSTINFPGAFULL_STR;
	static const std::string MIO_ER_WRONGITEMSIZE_STR;
	static const std::string MIO_ER_SEMCREATE_STR;
	static const std::string MIO_ER_SEMTAKE_STR;
	static const std::string MIO_ER_WRONGMEMAREA_STR;
	static const std::string MIO_ER_BADALIGNMENT_STR;
	static const std::string MIO_ER_UPDATELISTFULL_STR;
	static const std::string MIO_ER_WRONGPRIO_STR;
	static const std::string MIO_ER_CHANNOTMAPPED_STR;
	static const std::string MIO_ER_NOPIDRVID_STR;
	static const std::string MIO_ER_HANDLEINUSE_STR;
	static const std::string MIO_ER_BIOSFAIL_STR;
	static const std::string MIO_ER_DOWNGRADE_STR;
	static const std::string MIO_ER_BADFIRMWARE_STR;
	static const std::string MIO_ER_BADTYPE_STR;
	static const std::string MIO_ER_NOAPP_STR;
	static const std::string MIO_ER_NOSCALEINF_STR;
	static const std::string MIO_ER_WRONGFUNCTYPE_STR;
	static const std::string MIO_ER_NOTPRESENT_STR;
	static const std::string MIO_ER_OVERFLOW_STR;
};

#endif /** MIOERRORCODE_HPP_ */
