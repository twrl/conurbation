#pragma once

#include "conurbation/heap/allocator.hh"
#include "conurbation/uefi/tables.hh"

namespace Conurbation::Heap {

    class uefi_heap_t: public allocator_p {
    private:
        Conurbation::UEFI::efi_boot_services_t* boot_services_;

    public:

        uefi_heap_t(Conurbation::UEFI::efi_system_table_t* systab) : boot_services_(systab->BootServices) {}

        /// Attempt an allocation with the given size and alignment
        virtual auto allocate (size_t size, size_t align) -> result_t<void*> override;

        /// Deallocate
        virtual auto deallocate (void* ptr, size_t old_size, size_t align) -> status_t override;

        /// reallocate
        virtual auto reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> override;

        /// Attempt to reallocate in place
        virtual auto reallocate_in_place (void* ptr, size_t old_size, size_t new_size, size_t align) -> status_t override;

    };

}
