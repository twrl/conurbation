#pragma once

#include "conurbation/numeric_types.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

typedef _Atomic(uint8_t) atomic_uint8_t;
typedef _Atomic(uint16_t) atomic_uint16_t;
typedef _Atomic(uint32_t) atomic_uint32_t;
typedef _Atomic(uint64_t) atomic_uint64_t;

typedef _Atomic(uintptr_t) atomic_uintptr_t;

typedef _Atomic(int8_t) atomic_int8_t;
typedef _Atomic(int16_t) atomic_int16_t;
typedef _Atomic(int32_t) atomic_int32_t;
typedef _Atomic(int64_t) atomic_int64_t;

typedef _Atomic(intptr_t) atomic_intptr_t;

typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;

typedef _Atomic(bool_t) atomic_bool_t;
