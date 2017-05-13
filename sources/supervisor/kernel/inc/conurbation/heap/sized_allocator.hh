#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/result.hh"
#include "conurbation/heap/allocators.hh"

namespace Conurbation::Heap {

    class sized_allocator_t: public cstyle_allocator_p {

    private:
        dumb_allocator_p& superheap_;

    public:
        sizing_allocator_t(dumb_allocator_p& superheap) : superheap_(superheap) {};

        virtual inline auto allocate(size_t size) -> result_t<void*> override {
            auto r = Superheap::allocate(size + sizeof(size_t));
            if (r) {
                auto k = reinterpret_cast<size_t*>(r.some());
                *k = size;
                return reinterpret_cast<void*>(k+1);
            } else return r.none();
        }

        virtual inline auto deallocate(void* ptr) -> status_t override {
            auto k = reinterpret_cast<size_t*>(ptr) - 1;
            auto s = Superheap::deallocate(reinterpret_cast<void*>(k), *k + sizeof(size_t));
            return s;
        }

        virtual inline auto reallocate(void* ptr, size_t new_size) -> result_t<void*> override {
            auto k = reinterpret_cast<size_t*>(ptr) - 1;
            auto r = Superheap::reallocate(reinterpret_cast<void*>(k), new_size + sizeof(size_t), *k);
            if (r) {
                k = reinterpret_cast<size_t*>(r.some());
                *k = size;
                return reinterpret_cast<void*>(k+1);
            } else return r.none();
        }
    }

}
