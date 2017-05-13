#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/heap/allocators.hh"

namespace Conurbation::Heap {

    template <bool_t (*Predicate)(ptrdiff_t), typename A, typename B>
    class until_allocator_t: public dumb_allocator_p {

        static_assert(is_base_of_v<dumb_allocator_p, A>);
        static_assert(is_base_of_v<dumb_allocator_p, B>);
        static_assert(deallocates_foreign_v<B>, "B must be able to deallocate objects that it didn't allocate")

    private:
        bool_t latch_ = false;
        A& superA_;
        B& superB_;
        
    public:
        until_allocator_t(A& a, B& b) : superA_(a), superB_(b) {}

        inline virtual auto allocate (size_t size) -> result_t<void*> override
        {
            if (latch_ || latch_ = Predicate(size)) {
                return superB_.allocate(size);
            } else return superA_.allocate(size);
        }

        inline virtual auto deallocate (void* ptr, size_t allocated_size) -> status_t override {
            if (latch_ || latch_ = Predicate(-allocated_size)) {
                return superB_.deallocate(ptr, allocated_size);
            } else return superA_.deallocate(allocated_size);
        }

        inline virtual auto reallocate (void* ptr, size_t new_size, size_t original_size) -> result_t<void*> override {
            if (latch_ || latch_ = Predicate(new_size - original_size)) {
                return superB_.reallocate(ptr, new_size, original_size);
            } else return superA_.reallocate(ptr, new_size, original_size);
        }
    }

}
