#pragma once

#include "conurbation/traits.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

namespace Conurbation {

    template <typename T> constexpr bool_t is_abstract_v = __is_abstract(T);

    template <typename TBase, typename TDerived> constexpr bool_t is_base_of_v = __is_base_of(TBase, TDerived);

    template <typename T> constexpr bool_t is_class_v = __is_class(T);

    template <typename T> constexpr bool_t is_pod_v = __is_pod(T);
}
