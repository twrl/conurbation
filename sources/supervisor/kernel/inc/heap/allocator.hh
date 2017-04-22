#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/result.hh"

namespace Conurbation::Heap {


    /// Abstract base class for allocators
    class allocator_p {

    public:
        /// Attempt an allocation with the given size and alignment
        virtual auto allocate (size_t size, size_t align) -> result_t<void*> = 0;

        /// Deallocate
        virtual auto deallocate (void* ptr, size_t old_size, size_t align) -> status_t = 0;

        /// reallocate
        virtual auto reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> = 0;

        /// Attempt to reallocate in place
        virtual auto reallocate_in_place (void* ptr, size_t old_size, size_t new_size, size_t align) -> status_t = 0;

    };

}
