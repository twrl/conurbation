#pragma once

#include "conurbation/util/numeric_types.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

namespace Conurbation {

    template <typename T> constexpr size_t vector_element_count_v = 0;
    template <typename T> constexpr size_t vector_element_width_v = 0;
    template <typename T> constexpr bool_t is_vector_v = false;
}

typedef uint32_t uint32x4_t __attribute__((vector_size(16)));
typedef uint64_t uint64x2_t __attribute__((vector_size(16)));

template <> constexpr bool_t Conurbation::is_vector_v<uint32x4_t> = true;
template <> constexpr size_t Conurbation::vector_element_count_v<uint32x4_t> = 4;
template <> constexpr size_t Conurbation::vector_element_width_v<uint32x4_t> = 32;
// TODO: Vector traits...

typedef int32_t int32x4_t __attribute__((vector_size(16)));
typedef int64_t int64x2_t __attribute__((vector_size(16)));

typedef float32_t float32x4_t __attribute__((vector_size(16)));
typedef float64_t float64x2_t __attribute__((vector_size(16)));

#pragma clang diagnostic pop
