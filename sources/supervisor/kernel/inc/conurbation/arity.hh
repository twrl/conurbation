#pragma once

#include "conurbation/numeric_types.hh"

namespace Conurbation {

    template <typename T>
    class one_t {

        // TODO: static assert that T has trivial default constructor

    public:
        inline auto operator()() -> T& {
            static float64_t buffer_[(sizeof(T) + sizeof(float64_t) -1)/sizeof(float64_t)];
            static T* true_ptr_ = new (buffer_) T;
            return *true_ptr_;
        }

    }

}
