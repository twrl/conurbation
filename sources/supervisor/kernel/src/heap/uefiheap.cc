#include "conurbation/heap/uefiheap.hh"

namespace Conurbation::Heap {

    auto uefi_heap_t::allocate (size_t size, size_t align) -> result_t<void*> {
        return status_t::notImplemented;
    }

    auto uefi_heap_t::deallocate (void* ptr, size_t old_size, size_t align) -> status_t {
        return status_t::notImplemented;
    }

    auto uefi_heap_t::reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> {
        return status_t::notImplemented;
    }

    auto uefi_heap_t::reallocate_in_place (void* ptr, size_t old_size, size_t new_size, size_t align) -> status_t {
        return status_t::notImplemented;
    }

}
