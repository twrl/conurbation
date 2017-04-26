#pragma once

#include "conurbation/heap/allocator.hh"
#include "conurbation/uefi/tables.hh"

#include "conurbation/heap/selfdescribe.hh"


namespace Conurbation::Heap {

    class uefi_heap_t: public allocator_p {
    private:
        Conurbation::UEFI::efi_system_table_t* system_table_;

    public:

        uefi_heap_t(Conurbation::UEFI::efi_system_table_t* systab);

        /// Attempt an allocation with the given size and alignment
        virtual auto allocate (size_t size, size_t align) -> result_t<void*> override;

        /// Deallocate
        virtual auto deallocate (void* ptr, size_t old_size, size_t align) -> status_t override;

        /// reallocate
        virtual auto reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> override;

    };


}
