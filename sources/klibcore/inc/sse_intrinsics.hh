#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"
#include "vector_types.hh"

#define intrinsic extern "C" inline auto __attribute__((__always_inline__, __target__("sse")))

intrinsic _mm_add_ss(float32x4_t _a, float32x4_t _b)->float32x4_t
{
    _a[0] += _b[0];
    return _a;
}

intrinsic _mm_add_ps(float32x4_t _a, float32x4_t _b)->float32x4_t { return _a + _b; }

intrinsic _mm_sub_ss(float32x4_t _a, float32x4_t _b)->float32x4_t
{
    _a[0] -= _b[0];
    return _a;
}

intrinsic _mm_sub_ps(float32x4_t _a, float32x4_t _b)->float32x4_t { return _a - _b; }

intrinsic _mm_mul_ss(float32x4_t _a, float32x4_t _b)->float32x4_t
{
    _a[0] *= _b[0];
    return _a;
}

intrinsic _mm_mul_ps(float32x4_t _a, float32x4_t _b)->float32x4_t { return _a * _b; }

intrinsic _mm_div_ss(float32x4_t _a, float32x4_t _b)->float32x4_t
{
    _a[0] /= _b[0];
    return _a;
}

intrinsic _mm_div_ps(float32x4_t _a, float32x4_t _b)->float32x4_t { return _a / _b; }

intrinsic _mm_sqrt_ss(float32x4_t _a)->float32x4_t
{
    float32x4_t _c = __builtin_ia32_sqrtss(_a);
    return float32x4_t { _c[0], _a[1], _a[2], _a[3] }
}

intrinsic _mm_sqrt_ps(float32x4_t _a)->float32x4_t { return __builtin_ia32_sqrtps(_a); }

#undef intrinsic
