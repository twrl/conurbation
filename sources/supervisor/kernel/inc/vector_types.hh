#pragma once

#include "conurbation/numeric_types.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

typedef uint8_t uint8x16_t __attribute__((vector_size(16)));
typedef uint16_t uint16x8_t __attribute__((vector_size(16)));
typedef uint32_t uint32x4_t __attribute__((vector_size(16)));
typedef uint64_t uint64x2_t __attribute__((vector_size(16)));

typedef int8_t int8x16_t __attribute__((vector_size(16)));
typedef int16_t int16x8_t __attribute__((vector_size(16)));
typedef int32_t int32x4_t __attribute__((vector_size(16)));
typedef int64_t int64x2_t __attribute__((vector_size(16)));

typedef float32_t float32x4_t __attribute__((vector_size(16)));
typedef float64_t float64x2_t __attribute__((vector_size(16)));
