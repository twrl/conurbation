#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"
#include "conurbation/traits.hh"

namespace Conurbation {

    enum class status_t : int32_t {
        OK = 1,

        // Error Conditions
        UnknownError = 0,
        MemoryAllocationError = -1,
        NotFound = -2,
        ServiceNotFound = -3

    };

    template <typename T> class expect_t {
    private:
        using storage_type = if_t<is_scalar_v<T>, T, add_pointer_t<remove_reference_t<T>>>;
        storage_type _val;
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
