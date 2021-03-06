#pragma once

#include "ll/heap/allocator.hh"

namespace ll::Heap {

    /// Best Fit Linked List Allocator
    ///
    /// Keeps a linked list of free blocks and allocates them best-fit
    class bestfit_allocator_t: public allocator_p {
    protected:
        page_provider_p& page_provider_;

    public:
        bestfit_allocator_t(page_provider_p& provider);

        inline virtual auto page_provider() -> page_provider_p& override { return page_provider_; }
        inline virtual auto page_provider(page_provider_p& provider) -> allocator_p& override { page_provider_ = provider; return *this; }

        virtual auto allocate(size_t size) -> _<uintptr_t> override;
        virtual auto deallocate(uintptr_t ptr, size_t size) -> status_t override;
        virtual auto reallocate(uintptr_t ptr, size_t oldSize, size_t newSize) -> _<uintptr_t> override;

    };

}
