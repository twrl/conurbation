#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "conurbation/numeric_types.hh"

namespace Conurbation {

    enum class status_t : int32_t {
        OK = 1,

        // Error Conditions
        UnknownError = 0,
        MemoryAllocationError = -1,
        NotFound = -2

    };

    template <typename T> class expect_t {
    private:
        T _val;
        status_t _status;

    public:
        expect_t(status_t Status)
            : _status(Status)
        {
        }
        expect_t(T Value)
            : _val(Value)
            , _status(status_t::OK)
        {
        }
        expect_t(status_t Status, T Value)
            : _val(Value)
            , _status(Status)
        {
        }

        inline explicit operator T() { return _val; }

        inline operator bool_t() { return static_cast<int32_t>(_status) > 0; }

        inline operator status_t() { return _status; }

        inline auto status() -> status_t { return _status; }
        inline auto value() -> T { return _val; }
    };

    template <typename T> using _ = expect_t<T>;
}
