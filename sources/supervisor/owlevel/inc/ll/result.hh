#pragma once

#include "numeric_types.hh"
#include "traits.hh"

namespace ll {

    enum class status_t {
        success,

        size_mismatch,
        type_mismatch
    };

    template <typename T>
    class result_t {
        using TStore = if_t<is_literal_v<T>, T, add_pointer_t<T>>;

    private:
        status_t status_;
        TStore result_val_;

    public:
        result_t(status_t status) : status_(status), result_val_(is_literal_v<T> ? T() : nullptr) {}
        result_t(T val) : status_(status_t::success), result_val_(is_literal_v<T> ? val : &val) {}

        inline operator bool_t() { return status_ == status_t::success; }
        inline operator status_t() { return status_; }
        inline explicit operator T() { return is_literal_v<T> ? result_val_ : *result_val_; }

        inline auto result() -> T { return is_literal_v<T> ? result_val_ : *result_val_; }
        inline auto status() -> status_t { return status_; }
    };

}

template <typename T>
using _ = ll::result_t<T>;
