#pragma once

#include "numeric_types.hh"
#include "conurbation/status.hh"
#include "uefi/tables.h"

namespace Conurbation::Mem
{

    class page_alloc_service_p {
    public:
        virtual _<uintptr_t> allocate(size_t num_pages) = 0;
        virtual void deallocate(size_t num_pages, uintptr_t base_address) = 0;
    };

    class efi_alloc_service_t : public page_alloc_service_p {
    private:
        UEFI::efi_system_table_t* system_table_;

    public:
        efi_alloc_service_t(UEFI::efi_system_table_t* systemTable)
            : system_table_(systemTable)
        {
        }

        virtual _<uintptr_t> allocate(size_t num_pages);

        virtual void deallocate(size_t num_pages, uintptr_t base_address);
    };
}
