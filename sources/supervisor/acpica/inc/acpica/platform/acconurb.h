// This is written to be (more-or-less) compatible with 
// the coding style of the rest of ACPICA

#include <system/allocate.h>
#include <types/locks.h>

#ifndef __ACCONURB_H_
#define __ACCONURB_H_

#define ACPI_MACHINE_WIDTH 64
#define COMPILER_DEPENDENT_INT64 signed long
#define COMPILER_DEPENDENT_UINT64 unsigned long


#ifdef ACPI_USE_SYSTEM_INTTYPES
#undef ACPI_USE_SYSTEM_INTTYPES
#endif


#define ACPI_CACHE_T cache_t
#define ACPI_SEMAPHORE semaphore_t*
#define ACPI_SPINLOCK ticketlock_t*

#define ACPI_MUTEX_TYPE ACPI_BINARY_SEMAPHORE
#endif