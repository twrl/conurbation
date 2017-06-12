#include "ll/rng.hh"
#include "ll/memory.hh"

namespace ll {

    namespace {



        static auto matrix_swap(uint64_t matrix[64], int width, uint64_t mask) -> void {
            int i, o;
            for (o = 0; o < 32/width; ++o) {
                for (i = 0; i < width; ++i) {
                    uint64_t* x = &matrix[i + (o*width*2)];
                    uint64_t* y = &matrix[(i+width) + (o*width*2)];
                    *x ^= ((*y << width) & mask);
                    *y ^= ((*x & mask) >> width);
                    *x ^= ((*y << width) & mask);
                }
            }
        }

        static auto matrix_transpose(uint64_t matrix[64]) -> void {
            auto width = 64;
            uint64_t mask = -1;
            while (width != 1) {
                width >>= 1;
                mask = mask ^ (mask >> width);
                matrix_swap(matrix, width, mask);
            }
        }


        static auto lfsr() -> uint16_t {
            static uint16_t lfsr = 0xACE1u;

            unsigned lsb = lfsr & 1;  /* Get lsb (i.e., the output bit). */
            lfsr >>= 1;               /* Shift register */
            if (lsb == 1)             /* Only apply toggle mask if output bit is 1. */
            lfsr ^= 0xB400u;        /* Apply toggle mask, value has 1 at bits corresponding
                                     * to taps, 0 elsewhere. */
            return lfsr;
        }


    }

    rng_t::rng_t() {
        for (int i = 0; i < 16; i += 2)
        {
            state_[0][i] = __builtin_readcyclecounter();
            state_[0][i + 1] = lfsr();
            //asm volatile ("invtlb");
        }
        feed(__builtin_readcyclecounter());

    }

    auto rng_t::stir() -> void {
        uint64_t newState[4][64];
        uint64_t* newStateE = &newState[0][0];

        memory_t ns(&newState, sizeof(newState));
        memory_t os(&state_, sizeof(state_));

        os.subrange(0 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)).copy_to(ns.subrange(0 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)));
        os.subrange(2 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)).copy_to(ns.subrange(1 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)));
        os.subrange(1 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)).copy_to(ns.subrange(2 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)));
        os.subrange(3 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)).copy_to(ns.subrange(3 * 64 * sizeof(uint64_t), 64 * sizeof(uint64_t)));

        // newState[0] = state_[0];
        // newState[1] = state_[2];
        // newState[2] = state_[1];
        // newState[3] = state_[3];

        for (int l = 0; l < 8; ++l)
        {
            matrix_transpose(newState[0]);
            matrix_transpose(newState[1]);
            matrix_transpose(newState[2]);
            matrix_transpose(newState[3]);

            auto _a = newStateE[lfsr() >> 10];
            for (int i = 0; i < 64; ++i)
            {
                auto b = lfsr() >> 10;
                auto _b = newStateE[b];
                newStateE[b] += _a;
                _a = _b;
            }

        }

        ns.copy_to(os);
    }

    auto rng_t::feed(uint64_t value) -> void {
        state_[0][0] = value;
        stir();
    }

    auto rng_t::fetch() -> uint64_t {
        stir();
        return state_[4][63];
    }

}
