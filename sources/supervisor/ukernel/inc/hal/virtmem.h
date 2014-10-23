#pragma once

#include "types.h"

namespace Conurbation {

    typedef uintptr_t paddr_t;
    typedef uintptr_t vaddr_t;

    struct address_space_t {};

    struct address_mapping_t {
        vaddr_t virtualBase;
        paddr_t physicalBase;
        size_t length;
    };

    namespace HAL {

        class virtmem_i {
            public:
            virtual address_space_t* getCurrentAddressSpace() = 0;
            virtual void setAddressSpace(address_space_t* space) = 0;

            virtual void invalidateTLBs() = 0;
        };
    }
}