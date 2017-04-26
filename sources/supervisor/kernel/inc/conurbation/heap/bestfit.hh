#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/heap/allocator.hh"

namespace { struct free_node_t; }

namespace Conurbation::Heap {

    class bestfit_t: public allocator_p {
    public:
        bestfit_t() noexcept;
        bestfit_t(void* firstblock, size_t firstblockSize) noexcept;

        /// Attempt an allocation with the given size and alignment
        virtual auto allocate (size_t size, size_t align) -> result_t<void*> override;

        /// Deallocate
        virtual auto deallocate (void* ptr, size_t old_size, size_t align) -> status_t override;

        /// reallocate
        virtual auto reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> override;


    private:
        free_node_t* root_;

    };

}
