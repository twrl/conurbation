#pragma once

#include "ll.hh"
#include "ll/heap/page_provider.hh"

namespace ll::Heap {

    class allocator_p {
    public:
        virtual auto page_provider() -> page_provider_p& = 0;
        virtual auto page_provider(page_provider_p& provider) -> allocator_p& = 0;

        virtual auto allocate(size_t size) -> _<uintptr_t> = 0;
        virtual auto deallocate(uintptr_t ptr, size_t size) -> status_t = 0;
        virtual auto reallocate(uintptr_t ptr, size_t oldSize, size_t newSize) -> _<uintptr_t> = 0;

    };



}
