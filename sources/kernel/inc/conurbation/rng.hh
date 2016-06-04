#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"
#include "conurbation/obmodel/service.hh"
#include "conurbation/numeric_traits.hh"
#include "cpu_intrinsics.hh"

namespace Conurbation {

    class rng_service_p;

    template <> constexpr guid_t service_type_v<rng_service_p> = "3a39b736-8e77-45e6-b760-a6ab9fc9294c"_guid;

    class rng_service_p : public service_p {
    public:
        inline virtual auto service_type() -> guid_t const final { return service_type_v<rng_service_p>; };

        virtual auto reseed(uint64_t seed) -> rng_service_p& = 0;
        virtual auto generate() -> uint64_t = 0;
        virtual auto fill(uint8_t* buffer, size_t length) -> rng_service_p& = 0;
    };

    class lfsr_rng_service_t : public rng_service_p {
    private:
        static constexpr uint64_t polynomial_ = (1UL << 59) | (1UL << 60) | (1UL << 62) | (1UL << 63);
        uint64_t state_;

    public:
        inline lfsr_rng_service_t()
            : state_(__rdtsc())
        {
            for (int j = 0; j < 7; ++j) {
                for (int i = 0; i < 23; ++i) {
                    generate();
                }
                state_ ^= __rdtsc();
            }
        }

        inline virtual auto reseed(uint64_t seed) -> rng_service_p& final
        {
            if (seed != -1)
                state_ = seed;
            else {
                state_ = __rdtsc();
                for (int j = 0; j < 8; ++j) {
                    for (int i = 0; i < 32; ++i) {
                        generate();
                    }
                    state_ ^= __rdtsc();
                }
            }
            return *this;
        }

        inline virtual auto generate() -> uint64_t final
        {
            auto lsb = state_ & 1;
            state_ >>= 1;
            state_ ^= (-lsb) & polynomial_;
            return state_;
        }

        inline virtual auto fill(uint8_t* buffer, size_t length) -> rng_service_p& final
        {
            auto llen = length / 8;
            auto slen = length % 8;
            uint64_t* lbuffer = reinterpret_cast<uint64_t*>(buffer);
            while (llen-- > 0) {
                *lbuffer++ = generate();
            }
            uint8_t* sbuffer = reinterpret_cast<uint8_t*>(lbuffer);
            while (slen-- > 0) {
                *sbuffer++ = static_cast<uint8_t>(generate());
            }
            return *this;
        }
    };
}
