/*
 * AtomicWrapper.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: madsen
 */

#include <atomic/AtomicWrapper.hpp>
#include "SviException.hpp"
#include "svi_e.h"

AtomicWrapper::AtomicWrapper()
{
    semaLock = semMCreate(SEM_Q_PRIORITY | SEM_DELETE_SAFE | SEM_INVERSION_SAFE);

    if (semaLock == NULL)
    {
        log_Wrn("Could not allocate memory for semaphor in atomic wrapper");
    }
}

AtomicWrapper::~AtomicWrapper()
{
    if(semaLock == NULL) {
        return;
    }
    semDelete(semaLock);
}

SINT32 AtomicWrapper::lock()
{
    if(semaLock == NULL) {
        return 0;
    }
    return semTake(semaLock, WAIT_FOREVER);
}

SINT32 AtomicWrapper::unlock()
{
    if(semaLock == NULL) {
        return 0;
    }
    return semGive(semaLock);
}

UINT32 AtomicWrapper::getDatatype(const std::type_info& inf)
   {
       if (inf == typeid(UINT8))
       {
           return SVI_F_UINT8;
       }
       else if (inf == typeid(UINT16))
       {
           return SVI_F_UINT16;
       }
       else if (inf == typeid(SINT16))
       {
           return SVI_F_SINT16;
       }
       else if (inf == typeid(UINT32))
       {
           return SVI_F_UINT32;
       }
       else if (inf == typeid(SINT32))
       {
           return SVI_F_SINT32;
       }
       else if (inf == typeid(REAL32))
       {
           return SVI_F_REAL32;
       }
       else if (inf == typeid(BOOL8))
       {
           return SVI_F_BOOL8;
       }
       else if (inf == typeid(CHAR8))
       {
           return SVI_F_CHAR8;
       }
       else if (inf == typeid(UINT64))
       {
           return SVI_F_UINT64;
       }
       else if (inf == typeid(REAL64))
       {
           return SVI_F_REAL64;
       }
       else if (inf == typeid(CHAR16))
       {
           return SVI_F_CHAR16;
       }

       std::stringstream ss;
       ss << "Unable to determine SVI type from type_info. Type was " << inf.name();
       throw SviException(ss.str().c_str());
   }

