#include "conurbation/mem/pagealloc.hh"

namespace Conurbation::Mem
{

    _<uintptr_t> efi_alloc_service_t::allocate(size_t num_pages)
    {
        uintptr_t pages;
        UEFI::status_t st;
        st = system_table_->BootServices->AllocatePages(
            UEFI::allocate_type_t::AllocateAnyPages, UEFI::memory_type_t::OsData, num_pages, &pages);

        if (st == UEFI::status_t::Success) {
            return pages;
        }
        else
            return status_t::MemoryAllocationError;
    }

    void efi_alloc_service_t::deallocate(size_t num_pages, uintptr_t base_address)
    {
        system_table_->BootServices->FreePages(base_address, num_pages);
    }
}
