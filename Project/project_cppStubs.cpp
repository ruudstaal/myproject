/**
 ********************************************************************************
 * @file     cppStubs.cpp
 * @author   Bachmann electronic GmbH
 * @version  $Revision: 000 $ $LastChangedBy: BE $
 * @date     $LastChangeDate: 2011-08-10 11:00:00 $
 *
 * @brief    This file contains C++ stubs and workarounds for problems
 *           in the C++ implementation from VxWorks.
 *
 ********************************************************************************
 * COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2015
 *******************************************************************************/

#include <mtypes.h>
#include <taskLib.h>
#include <msys_e.h>
#include <log_e.h>

#include "exceptions.hpp"

/** SW-Module memory partition, needed for new operator */
extern UINT32 project_MemPart;

/**
 ********************************************************************************
 * @brief     This method overwrites the C++ operator new. All C++ new calls
 *            allocate memory from the configured SW-Module memory partition.
 *            Only memory allocations from munching are allocated from the
 *            default memory partition.
 *
 * @param[in]  size    size in bytes of object to allocate.
 * @retval     pointer to reserved memory for allocated object.
 *******************************************************************************/
void * operator new(size_t size)
{
    void * pTemp;

    pTemp = sys_MemXPAlloc(project_MemPart, size);
    if (pTemp == NULL)
    {
        throw bae::memory_exc();
    }

    return pTemp;
}

/**
 ********************************************************************************
 * @brief     This method overwrites the C++ operator new[]. All C++ new calls
 *            allocate memory from the configured SW-Module memory partition.
 *            Only memory allocations from munching are allocated from the
 *            default memory partition.
 *
 * @param[in]  size    size in bytes of object to allocate.
 * @retval     pointer to reserved memory for allocated object.
 *******************************************************************************/
void * operator new[](size_t size)
{
    void * pTemp;

    pTemp = sys_MemXPAlloc(project_MemPart, size);
    if (pTemp == NULL)
    {
        throw bae::memory_exc();
    }

    return pTemp;
}

/**
 ********************************************************************************
 * @brief     This method overwrites the C++ operator delete. All C++ delete
 *            calls frees memory which has been allocated by the new operator.
 *
 * @param[in]  ptr     pointer to reserved memory allocated by new.
 *******************************************************************************/
void operator delete(void *ptr)
{
    sys_MemXFree(ptr);
}

/**
 ********************************************************************************
 * @brief     This method overwrites the C++ operator delete. All C++ delete[]
 *            calls frees memory which has been allocated by the new[] operator.
 *
 * @param[in]  ptr     pointer to reserved memory allocated by new[].
 *******************************************************************************/
void operator delete[](void *ptr)
{
    sys_MemXFree(ptr);
}
