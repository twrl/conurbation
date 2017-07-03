#pragma once

#include "numeric_types.hh"

namespace Conurbation::HW {

    class address_space_t;
    class address_range_t;
    class numa_node_t;

    enum class address_backing_mode_t {
        physical,
        paged_in,
        paged_out,
        mmio,
        unbacked
    };

    enum class address_disposition_t {
        hardware,
        firmware,
        supervisor,
        user,
        free,
        invalid
    };

    enum class address_canonical_form_t {
        zero,
        sign
    };

    class address_space_t {
    public:
        auto width() -> size_t;

        auto canonicalisation() -> address_canonical_form_t;

        auto specify(address_t, size_t) -> address_range_t&;

        auto find_address(address_t) -> address_range_t&;

    };

    class address_range_t {
    public:

        auto start() -> address_t;

        auto end() -> address_t;

        auto size() -> size_t;

        auto space() -> address_space_t&;

        //auto numa_node() -> numa_node_t&;

        auto backing_range() -> address_range_t&;
        auto backing_range(address_range_t&) -> address_range_t&;

        auto backing_mode() -> address_backing_mode_t;
        auto backing_mode(address_backing_mode_t) -> address_range_t&;

        auto disposition() -> address_disposition_t;
        auto disposition(address_disposition_t) -> address_range_t&;

    };

}
