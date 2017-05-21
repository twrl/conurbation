#pragma once

#include "numeric_types.hh"
#include "ll/result.hh"

namespace ll::Heap {

    /// Interface for a type which is a source of whole, raw, memory pages
    /// from the system.
    class page_provider_p {
    public:

        virtual auto allocate_pages(size_t numPages) -> _<uintptr_t> = 0;
        virtual auto deallocate_pages(uintptr_t base, size_t numPages) -> status_t = 0;

    };

}
