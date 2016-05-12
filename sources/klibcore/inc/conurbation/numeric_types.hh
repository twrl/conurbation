#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;
typedef unsigned __int128 uint128_t;

typedef __INT8_TYPE__ int8_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT64_TYPE__ int64_t;
typedef signed __int128 int128_t;

typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

// Set out prototypes for numeric traits
namespace Conurbation {

    template <typename T> constexpr T numeric_max_v = 0;
    template <typename T> constexpr T numeric_min_v = 0;
    template <typename T> constexpr size_t numeric_width_v = 8 * sizeof(T);
}

template <> constexpr uint8_t Conurbation::numeric_max_v<uint8_t> = __UINT8_MAX__;
template <> constexpr uint16_t Conurbation::numeric_max_v<uint16_t> = __UINT16_MAX__;
template <> constexpr uint32_t Conurbation::numeric_max_v<uint32_t> = __UINT32_MAX__;
template <> constexpr uint64_t Conurbation::numeric_max_v<uint64_t> = __UINT64_MAX__;
template <>
constexpr uint128_t Conurbation::numeric_max_v<uint128_t> = (static_cast<uint128_t>(__UINT64_MAX__) << 64) + __UINT64_MAX__;

template <> constexpr int8_t Conurbation::numeric_max_v<int8_t> = __INT8_MAX__;
template <> constexpr int8_t Conurbation::numeric_min_v<int8_t> = -Conurbation::numeric_max_v<int8_t> - 1;
template <> constexpr int16_t Conurbation::numeric_max_v<int16_t> = __INT16_MAX__;
template <> constexpr int16_t Conurbation::numeric_min_v<int16_t> = -Conurbation::numeric_max_v<int16_t> - 1;
template <> constexpr int32_t Conurbation::numeric_max_v<int32_t> = __INT32_MAX__;
template <> constexpr int32_t Conurbation::numeric_min_v<int32_t> = -Conurbation::numeric_max_v<int32_t> - 1;
template <> constexpr int64_t Conurbation::numeric_max_v<int64_t> = __INT64_MAX__;
template <> constexpr int64_t Conurbation::numeric_min_v<int64_t> = -Conurbation::numeric_max_v<int64_t> - 1;
template <>
constexpr int128_t Conurbation::numeric_max_v<int128_t> = (static_cast<uint128_t>(__INT64_MAX__) << 64) + __UINT64_MAX__;
template <> constexpr int128_t Conurbation::numeric_min_v<int128_t> = -Conurbation::numeric_max_v<int128_t> - 1;

typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;

template <> constexpr float32_t Conurbation::numeric_max_v<float32_t> = __FLT_MAX__;
template <> constexpr float32_t Conurbation::numeric_min_v<float32_t> = __FLT_MIN__;
template <> constexpr float64_t Conurbation::numeric_max_v<float64_t> = __DBL_MAX__;
template <> constexpr float64_t Conurbation::numeric_min_v<float64_t> = __DBL_MIN__;
template <> constexpr float128_t Conurbation::numeric_max_v<float128_t> = __LDBL_MAX__;
template <> constexpr float128_t Conurbation::numeric_min_v<float128_t> = __LDBL_MIN__;

namespace Conurbation {

    constexpr uintmax_t operator""_Ki(unsigned long long v) { return v * 1024; }
    constexpr uintmax_t operator""_Mi(unsigned long long v) { return v * 1024 * 1024; }
    constexpr uintmax_t operator""_Gi(unsigned long long v) { return v * 1024 * 1024; }
}

typedef decltype(nullptr) nullptr_t;
typedef bool bool_t;

#pragma clang diagnostic pop
