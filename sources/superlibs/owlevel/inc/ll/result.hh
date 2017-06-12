#pragma once

#include "numeric_types.hh"
#include "traits.hh"

namespace ll {

    enum class status_t {
        success,

        size_mismatch,
        type_mismatch
    };

    template <typename TResult, typename TStatus = status_t>
    class result_t {
        using TStore = if_t<is_literal_v<TResult>, TResult, add_pointer_t<TResult>>;

    private:
        TStatus status_;
        TStore result_val_;

    public:
        result_t(TStatus status) : status_(status), result_val_(is_literal_v<TResult> ? TResult() : nullptr) {}
        result_t(TResult val) : status_(TStatus::success), result_val_(is_literal_v<TResult> ? val : &val) {}

        inline operator bool_t() { return status_ == TStatus::success; }
        inline operator TStatus() { return status_; }
        inline explicit operator TResult() { return is_literal_v<TResult> ? result_val_ : *result_val_; }

        inline auto result() -> TResult { return is_literal_v<TResult> ? result_val_ : *result_val_; }
        inline auto status() -> TStatus { return status_; }
    };

}
