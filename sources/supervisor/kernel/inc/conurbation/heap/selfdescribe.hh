#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/heap/allocator.hh"

namespace Conurbation::Heap {

    template <typename BaseAllocator>
    class self_describing_t: public allocator_p {

        struct sd_header_t {
            allocator_p* alloc;
            size_t reqLength;
        };

    public:

        self_describing_t(): base() {
        }

        /// Attempt an allocation with the given size and alignment
        virtual auto allocate (size_t size, size_t align) -> result_t<void*> override {
            auto ba = this->base.allocate(size+sizeof(sd_header_t), align);
            if (ba) {
                auto v = ba.some();
                auto hdr = reinterpret_cast<sd_header_t*>(v);
                hdr->alloc = &base;
                hdr->reqLength = size;
                return v + sizeof(sd_header_t);
            } else return ba.none();
        }

        /// Deallocate
        virtual auto deallocate (void* ptr, size_t old_size, size_t align) -> status_t override {
            auto hdr = reinterpret_cast<sd_header_t*>(ptr - sizeof(sd_header_t));
            return hdr->alloc->deallocate(ptr - sizeof(sd_header_t), static_cast<size_t>(old_size || hdr->reqLength) + sizeof(sd_header_t), align);
        }

        /// reallocate
        virtual auto reallocate (void* ptr, size_t old_size, size_t new_size, size_t align) -> result_t<void*> override {
            auto hdr = reinterpret_cast<sd_header_t*>(ptr - sizeof(sd_header_t));
            auto s = hdr->alloc->reallocate(ptr - sizeof(sd_header_t), static_cast<size_t>(old_size || hdr->reqLength) + sizeof(sd_header_t), new_size + sizeof(sd_header_t), align);
            if (s) {
                hdr = reinterpret_cast<sd_header_t*>(s.some());
                hdr->alloc = &base;
                hdr->reqLength = new_size;
                return s.some() + sizeof(sd_header_t);
            } else return s.none();
        }

    protected:
        BaseAllocator base;

    };

}
