#pragma once

#include "numeric_types.hh"

namespace ll {

    template <size_t Length, size_t Alignment>
    struct aligned_storage {
        typedef struct {
            alignas(Alignment) uint8_t data[Length];
        } type;
    };

    template <size_t Length, size_t Alignment>
    using aligned_storage_t = typename aligned_storage<Length, Alignment>::type;

}
