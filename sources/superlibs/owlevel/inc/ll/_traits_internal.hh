#pragma once

#include "numeric_types.hh"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

 namespace ll::_traits_internal {
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

        template <typename T> struct add_pointer_t {
            typedef T* type;
        };
        template <typename T> struct add_pointer_t<T*> {
            typedef T* type;
        };

        template <bool_t Condition, typename T>
        struct enable_if_t {
        };

        template <typename T>
        struct enable_if_t<true, T> {
            typedef T type;
        };

        template <bool_t If, typename Then, typename Else> struct if_t {
        };
        template <typename Then, typename Else> struct if_t<true, Then, Else> {
            typedef Then type;
        };
        template <typename Then, typename Else> struct if_t<false, Then, Else> {
            typedef Else type;
        };

        template <typename T> struct align_of_t {
            static constexpr size_t value = alignof(T);
        };

        template <typename T> struct size_of_t {
            static constexpr size_t value = sizeof(T);
        };
    }


#pragma clang diagnostic pop
