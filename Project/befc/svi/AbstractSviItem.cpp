/*
 * AbstractSviItem.cpp
 *
 *  Created on: May 23, 2019
 *      Author: madsen
 */
#include "AbstractSviItem.hpp"

void AbstractSviItem::validateInitializedAndReadable()
{
    if (isInitialized())
    {
        if (isReadable() == false)
        {
            std::stringstream ss;
            ss << "SviItem " << this->getModuleName().c_str() << "/" << this->getVarName().c_str()
                    << " is not readable";
            throw SviException(ss.str());
        }
    }
    else
    {
        std::stringstream ss;
        ss << "SviItem " << this->getModuleName().c_str() << "/" << this->getVarName().c_str()
                << " is not initialized - cannot read values from it";
        throw SviException(ss.str());

    }
}

void AbstractSviItem::setQualityState(SviItemEventListener::DataQuality newQuality)
{
    if (this->quality == newQuality)
    {
        return;
    }

    SviItemEventListener::DataQuality theOldQuality = this->quality;
    this->quality = newQuality;
    for (std::vector<SviItemEventListener*>::iterator it = listeners.begin(); it != listeners.end();
            ++it)
    {
        (*it)->dataQualityChanged(this, theOldQuality, this->quality);
    }
}

void AbstractSviItem::handleErrorCode(SINT32 result)
{
    switch (result)
    {
        case SVI_E_OK:
            setQualityState(SviItemEventListener::GOOD);
            numTimeouts = 0;
            return;
        case SVI_E_UNDEF:
        case SVI_E_OLDADDR:
        case SVI_E_PARM:
            setInitialized(false);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_ACCDENIED:
        case SVI_E_BADUSERLVL:
            log_Wrn("Access is denied for item %s", getVarName().c_str());
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_WRITE:
            if (isWriteable())
            {
                log_Err("Write did not succeed on item: %s ", getVarName().c_str());
                setDirty(true);
                setFailed(true);
                setQualityState(SviItemEventListener::BAD);
            }
            break;
        case SVI_E_MBTRANS:
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            log_Err("Item has to be read using Multiblock transfer - not supported! %s: ",
                    getVarName().c_str());
            break;
        case M_E_TIMEOUT:
        case M_E_TIMEOUT1:
        case M_E_TIMEOUT2:
        case M_E_TIMEOUT3:
            numTimeouts++;
            if (numTimeouts == ALLOWED_NUM_TIMEOUTS)
            {
                setFailed(true);
                setQualityState(SviItemEventListener::TIMED_OUT);
            }
            break;
        case SVI_E_BADNAME:
            log_Err("Item name does not exist! %s in module %s", getVarName().c_str(),
                    getModuleName().c_str());
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_ADDR:
            log_Err("Address in request does not exist for item %s in module %s",
                    getVarName().c_str(), getModuleName().c_str());
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_NOMOD:
            log_Err("Module %s does not exist for item %s", getModuleName().c_str(),
                    getVarName().c_str());
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_FAILED:
            log_Err("Unspecified error for item %s", getVarName().c_str());
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_VARINUSE:
            log_Err("SVI item %s failed to write. Cause: %x", getVarName().c_str(), result);
            setQualityState(SviItemEventListener::BAD);
            break;
        default:
            log_Err("Item %s returncode handled default %x ", getVarName().c_str(), result);
            setFailed(true);
            setQualityState(SviItemEventListener::BAD);
    }
}

void AbstractSviItem::notifyFailedWrite(SINT32 reason)
{
    switch (reason)
    {
        case SVI_E_ACCDENIED:
        case SVI_E_BADUSERLVL:
            failed = true;
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_WRITE:
            failed = true;
            setQualityState(SviItemEventListener::BAD);
            break;
        case SVI_E_FAILED:
            failed = true;
            setQualityState(SviItemEventListener::BAD);
            break;
        case M_E_TIMEOUT:
        case M_E_TIMEOUT1:
        case M_E_TIMEOUT2:
        case M_E_TIMEOUT3:
            break;
    }

    for (std::vector<SviItemEventListener*>::iterator it = listeners.begin(); it != listeners.end();
            ++it)
    {
        (*it)->writeFailed(this, reason);
    }
}

void AbstractSviItem::reset()
{
    this->initialized = false;
    this->failed = false;
    this->errorCode = SVI_E_OK;
    this->dirty = false;
    this->quality = SviItemEventListener::INIT;

}

UINT32 AbstractSviItem::getDatatypeLength(UINT32 datatype)
{
    switch (datatype)
    {
        case SVI_F_BOOL8:
        case SVI_F_UINT1:
        case SVI_F_UINT8:
        case SVI_F_SINT8:
        case SVI_F_CHAR8:
            return 1;
        case SVI_F_UINT16:
        case SVI_F_SINT16:
        case SVI_F_CHAR16:
            return 2;
        case SVI_F_UINT32:
        case SVI_F_SINT32:
        case SVI_F_REAL32:
            return 4;
        case SVI_F_REAL64:
        case SVI_F_UINT64:
        case SVI_F_SINT64:
            return 8;
        default:
            throw SviException(
                    "Unsupported datatype - Should not ask for datalength for MIXED, BLK, etc.");
    }
}
