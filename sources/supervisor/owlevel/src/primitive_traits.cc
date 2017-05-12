#include "traits.hh"
#include "guid.hh"

    template <> constexpr bool_t is_integral_v<uint8_t> = true;
    template <> constexpr bool_t is_integral_v<uint16_t> = true;
    template <> constexpr bool_t is_integral_v<uint32_t> = true;
    template <> constexpr bool_t is_integral_v<uint64_t> = true;
    template <> constexpr bool_t is_integral_v<int8_t> = true;
    template <> constexpr bool_t is_integral_v<int16_t> = true;
    template <> constexpr bool_t is_integral_v<int32_t> = true;
    template <> constexpr bool_t is_integral_v<int64_t> = true;
    template <> constexpr bool_t is_integral_v<bool_t> = true;
    template <> constexpr bool_t is_integral_v<char8_t> = true;
    template <> constexpr bool_t is_integral_v<char16_t> = true;
    template <> constexpr bool_t is_integral_v<char32_t> = true;
    
    
    template <> constexpr bool_t is_floating_point_v<float32_t> = true;
    template <> constexpr bool_t is_floating_point_v<float64_t> = true;
    
    template <> constexpr uint8_t numeric_max_v<uint8_t> = __UINT8_MAX__;
template <> constexpr uint16_t numeric_max_v<uint16_t> = __UINT16_MAX__;
template <> constexpr uint32_t numeric_max_v<uint32_t> = __UINT32_MAX__;
template <> constexpr uint64_t numeric_max_v<uint64_t> = __UINT64_MAX__;

template <> constexpr int8_t numeric_max_v<int8_t> = __INT8_MAX__;
template <> constexpr int8_t numeric_min_v<int8_t> = -numeric_max_v<int8_t> - 1;
template <> constexpr int16_t numeric_max_v<int16_t> = __INT16_MAX__;
template <> constexpr int16_t numeric_min_v<int16_t> = -numeric_max_v<int16_t> - 1;
template <> constexpr int32_t numeric_max_v<int32_t> = __INT32_MAX__;
template <> constexpr int32_t numeric_min_v<int32_t> = -numeric_max_v<int32_t> - 1;
template <> constexpr int64_t numeric_max_v<int64_t> = __INT64_MAX__;
template <> constexpr int64_t numeric_min_v<int64_t> = -numeric_max_v<int64_t> - 1;

template <> constexpr float32_t numeric_max_v<float32_t> = __FLT_MAX__;
template <> constexpr float32_t numeric_min_v<float32_t> = __FLT_MIN__;
template <> constexpr float64_t numeric_max_v<float64_t> = __DBL_MAX__;
template <> constexpr float64_t numeric_min_v<float64_t> = __DBL_MIN__;