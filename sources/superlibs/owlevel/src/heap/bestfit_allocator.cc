#include "ll/heap/bestfit_allocator.hh"

namespace ll::Heap {

    bestfit_allocator_t::bestfit_allocator_t(page_provider_p& provider): page_provider_(provider) {}

    auto bestfit_allocator_t::allocate(size_t size) -> result_t<uintptr_t> {

    }

    auto bestfit_allocator_t::deallocate(uintptr_t ptr, size_t size) -> status_t {

    }

    auto bestfit_allocator_t::reallocate(uintptr_t ptr, size_t oldSize, size_t newSize) -> result_t<uintptr_t> {

    }

}
