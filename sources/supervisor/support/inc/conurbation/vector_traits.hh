#pragma once

#include "vector_types.hh"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

namespace Conurbation {

    template <typename T> constexpr size_t vector_element_count_v = 0;
    template <typename T> constexpr size_t vector_element_width_v = 0;
    template <typename T> constexpr bool_t is_vector_v = false;
}

template <> constexpr bool_t Conurbation::is_vector_v<uint32x4_t> = true;
template <> constexpr size_t Conurbation::vector_element_count_v<uint32x4_t> = 4;
template <> constexpr size_t Conurbation::vector_element_width_v<uint32x4_t> = 32;
// TODO: Vector traits...

#pragma clang diagnostic pop
