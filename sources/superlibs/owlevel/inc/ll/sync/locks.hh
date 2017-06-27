#pragma once

#include "atomic_types.hh"

namespace ll::Sync {

    class spinlock_t {
    private:
        atomic_uint32_t lock_;
    public:
        auto acquire() -> void;
        auto release() -> void;
    };

    class ticketlock_t {
    private:
        atomic_uint32_t issue_;
        atomic_uint32_t ctr_;
    public:
        auto acquire() -> void;
        auto release() -> void;
    };

}
