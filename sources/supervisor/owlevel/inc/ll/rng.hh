#pragma once

#include "numeric_types.hh"

namespace ll {

    class rng_t {

    private:
        uint64_t state_[4][64];

    public:
        rng_t();

        auto stir() -> void;
        auto feed(uint64_t) -> void;
        auto fetch() -> uint64_t;



    };

}
