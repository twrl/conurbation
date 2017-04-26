#include "conurbation/heap/uefiheap.hh"
#include "conurbation/string.h"

namespace Conurbation::Heap {

    uefi_heap_t::uefi_heap_t(Conurbation::UEFI::efi_system_table_t* systab) : system_table_(systab) {

    }

    auto uefi_heap_t::allocate (size_t size, size_t align) -> result_t<void*> {
        if (this->system_table_->BootServices == nullptr) return status_t::serviceUnavailable;
        else {
            void* alloc_;
            // FIXME:: Check EFI Status
            this->system_table_->BootServices->AllocatePool(Conurbation::UEFI::memory_type_t::OsData, size, &alloc_);
            return alloc_;
        }

    }

    auto uefi_heap_t::deallocate (void* ptr, size_t old_size, size_t align) -> status_t {
        if (this->system_table_->BootServices == nullptr) return status_t::serviceUnavailable;
        else {
            this->system_table_->BootServices->FreePool(ptr);
            return status_t::success;
        }
    }

    auto uefi_heap_t::reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> {
        if (this->system_table_->BootServices == nullptr) return status_t::serviceUnavailable;
        else {
            void* new_alloc_;
            this->system_table_->BootServices->AllocatePool(Conurbation::UEFI::memory_type_t::OsData, new_size, &new_alloc_);
            memcpy(new_alloc_, ptr, static_cast<size_t>(old_size || new_size));
            this->system_table_->BootServices->FreePool(ptr);
            return new_alloc_;
        }
    }

}
