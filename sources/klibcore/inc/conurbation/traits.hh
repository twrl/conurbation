#pragma once

#include "numeric_types.hh"
#include "char_types.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

template <bool_t Head, bool_t... Tail> constexpr bool_t any_v = Head || any_v<Tail...>;
template <bool_t Head> constexpr bool_t any_v<Head> = Head;

template <bool_t Head, bool_t... Tail> constexpr bool_t all_v = Head&& all_v<Tail...>;
template <bool_t Head> constexpr bool_t all_v<Head> = Head;

namespace Conurbation {

    namespace _traits_internal {
        template <typename T> struct remove_const_t {
            typedef T type;
        };
        template <typename T> struct remove_const_t<const T> {
            typedef T type;
        };

        template <typename T> struct remove_volatile_t {
            typedef T type;
        };
        template <typename T> struct remove_volatile_t<volatile T> {
            typedef T type;
        };
        template <typename T> struct remove_cv_t {
            typedef typename remove_volatile_t<typename remove_const_t<T>::type>::type type;
        };

        template <typename T> struct add_const_t {
            typedef const T type;
        };
        template <typename T> struct add_volatile_t {
            typedef volatile T type;
        };
        template <typename T> struct add_cv_t {
            typedef typename add_const_t<typename add_volatile_t<T>::type>::type type;
        };

        template <typename T> struct remove_reference_t {
            typedef T type;
        };
        template <typename T> struct remove_reference_t<T&> {
            typedef T type;
        };
        template <typename T> struct remove_reference_t<T&&> {
            typedef T type;
        };

        template <typename T> struct remove_pointer_t {
            typedef T type;
        };
        template <typename T> struct remove_pointer_t<T*> {
            typedef T type;
        };
        template <typename T> struct remove_pointer_t<T* const> {
            typedef T type;
        };
        template <typename T> struct remove_pointer_t<T* volatile> {
            typedef T type;
        };
        template <typename T> struct remove_pointer_t<T* const volatile> {
            typedef T type;
        };
    }

    template <typename T> using remove_const_t = typename _traits_internal::remove_const_t<T>::type;
    template <typename T> using remove_volatile_t = typename _traits_internal::remove_volatile_t<T>::type;
    template <typename T> using remove_cv_t = typename _traits_internal::remove_cv_t<T>::type;
    template <typename T> using remove_reference_t = typename _traits_internal::remove_reference_t<T>::type;

    template <typename T> using add_const_t = typename _traits_internal::add_const_t<T>::type;
    template <typename T> using add_volatile_t = typename _traits_internal::add_volatile_t<T>::type;
    template <typename T> using add_cv_t = typename _traits_internal::add_cv_t<T>::type;

    template <typename T> using add_lvalue_reference_t = remove_reference_t<T>&;
    template <typename T> using add_rvalue_reference_t = remove_reference_t<T>&&;

    template <typename T> using remove_pointer_t = typename _traits_internal::remove_pointer_t<T>;

    template <typename T> constexpr bool_t is_integral_v = false;
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

    template <typename T> constexpr bool_t is_floating_point_v = false;
    template <> constexpr bool_t is_floating_point_v<float32_t> = true;
    template <> constexpr bool_t is_floating_point_v<float64_t> = true;
    template <> constexpr bool_t is_floating_point_v<float128_t> = true;

    template <typename T> constexpr bool_t is_arithmetic_v = is_integral_v<T> || is_floating_point_v<T>;

    template <typename T> constexpr bool_t is_pointer_v = false;
    template <typename T> constexpr bool_t is_pointer_v<T*> = true;

    template <typename T> constexpr bool_t is_lvalue_reference_v = false;
    template <typename T> constexpr bool_t is_lvalue_reference_v<T&> = true;

    template <typename T> constexpr bool_t is_rvalue_reference_v = false;
    template <typename T> constexpr bool_t is_rvalue_reference_v<T&&> = true;

    template <typename T> constexpr bool_t is_enum_v = __is_enum(T);

    template <typename T> constexpr bool_t is_member_pointer_v = false;
    template <typename T, typename U> constexpr bool_t is_member_pointer_v<T U::*> = true;

    template <typename T, typename U> constexpr bool_t is_same_v = false;
    template <typename T> constexpr bool_t is_same_v<T, T> = true;

    template <typename T> constexpr bool_t is_nullptr_v = is_same_v<remove_cv_t<T>, nullptr_t>;

    template <typename T>
    constexpr bool_t is_scalar_v
        = is_arithmetic_v<T> || is_enum_v<T> || is_pointer_v<T> || is_member_pointer_v<T> || is_nullptr_v<T>;

    template <typename T> constexpr bool_t is_const_v = false;
    template <typename T> constexpr bool_t is_const_v<const T> = true;

    template <typename T> constexpr bool_t is_volatile_v = false;
    template <typename T> constexpr bool_t is_volatile_v<volatile T> = true;

    namespace _traits_internal {
        template <bool_t If, typename Then, typename Else> struct if_t {
        };
        template <typename Then, typename Else> struct if_t<true, Then, Else> {
            typedef Then type;
        };
        template <typename Then, typename Else> struct if_t<false, Then, Else> {
            typedef Else type;
        };
    }

    template <bool_t If, typename Then, typename Else> using if_t = typename _traits_internal::if_t<If, Then, Else>::type;
}

#pragma clang diagnostic pop
