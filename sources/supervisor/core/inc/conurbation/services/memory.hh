#pragma once

#include "numeric_types.hh"
#include "conurbation/services/locator.hh"

namespace Conurbation::Services
{

    class page_allocator_p {
    public:
        virtual auto allocate(size_t num_pages) -> uintptr_t = 0;
        virtual auto deallocate(size_t num_pages, uintptr_t base_address) -> void = 0;
    };
}
