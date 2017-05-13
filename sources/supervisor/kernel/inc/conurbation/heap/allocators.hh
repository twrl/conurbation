#pragma once

#include "conurbation/traits.hh"
#include "conurbation/object_traits.hh"
#include "conurbation/numeric_types.hh"

namespace Conurbation::Heap {

    class dumb_allocator_p {

    public:
        virtual auto allocate (size_t size) -> result_t<void*> = 0;
        virtual auto deallocate (void* ptr, size_t allocated_size) -> status_t = 0;
        virtual auto reallocate (void* ptr, size_t new_size, size_t original_size) -> result_t<void*> = 0;

    };

    class cstyle_allocator_p {

    public:
        virtual auto allocate (size_t size) -> result_t<void*> = 0;
        virtual auto deallocate (void* ptr) -> status_t = 0;
        virtual auto reallocate (void* ptr, size_t new_size) -> result_t<void*> = 0;

    };

    template <typename T>
    constexpr bool_t deallocates_foreign_v = false;

}

inline auto operator new (size_t size, Conurbation::Heap::dumb_allocator_p& allocator) -> void* {
    auto a = allocator.allocate(size);
    if (a) return a.some();
    else return nullptr;
}

inline auto operator new[] (size_t size, Conurbation::Heap::dumb_allocator_p& allocator) -> void* {
    auto a = allocator.allocate(size);
    if (a) return a.some();
    else return nullptr;
}

inline auto operator new (size_t size, Conurbation::Heap::cstyle_allocator_p& allocator) -> void* {
    auto a = allocator.allocate(size);
    if (a) return a.some();
    else return nullptr;
}

inline auto operator new[] (size_t size, Conurbation::Heap::cstyle_allocator_p& allocator) -> void* {
    auto a = allocator.allocate(size);
    if (a) return a.some();
    else return nullptr;
}
