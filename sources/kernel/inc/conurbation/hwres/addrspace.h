#pragma once

#include "conurbation/status.h"
#include "conurbation/numeric_types.hh"

namespace Conurbation::HwRes
{

    class address_space_t;

    enum class address_usage_t { available, inuse, reserved, reclaimable, unusable, noexist };

    enum class address_backing_t { self, page, mmio, ported, absent, none };

    enum class address_reclaim_t { ACPI, EFI_boot_services };

    class address_region_t {
        friend class address_space_t;

    private:
        uintptr_t _base;
        size_t _extent;
        address_usage_t _usage;
        address_space_t* _address_space;
        address_backing_t _backing_mode;
        address_reclaim_t _reclaim_policy;
        address_region_t* _backing_region;
        address_region_t* _prev;
        address_region_t* _next;

    public:
        address_region_t(address_space_t* Space, uintptr_t Base, size_t Extent);

        inline auto address_space() -> address_space_t * { return _address_space; }

        inline auto base() -> uintptr_t { return _base; }
        inline auto base(uintptr_t Base) -> address_region_t *
        {
            _base = Base;
            return this;
        }

        inline auto extent() -> size_t { return _extent; }
        inline auto extent(size_t Extent) -> address_region_t *
        {
            _extent = Extent;
            return this;
        }

        inline auto limit() -> uintptr_t { return _base + _extent; }
        inline auto limit(uintptr_t Limit) -> address_region_t *
        {
            _extent = Limit - _base;
            return this;
        }

        inline auto usage() -> address_usage_t { return _usage; }
        inline auto usage(address_usage_t Usage) -> address_region_t *
        {
            _usage = Usage;
            return this;
        }

        inline auto backing_mode() -> address_backing_t { return _backing_mode; }
        inline auto backing_mode(address_backing_t BackingMode) -> address_region_t *
        {
            _backing_mode = BackingMode;
            return this;
        }

        inline auto backing_region() -> address_region_t * { return _backing_region; }
        inline auto backing_region(address_region_t* BackingRegion) -> address_region_t *
        {
            _backing_region = BackingRegion;
            return this;
        }

        inline auto reclaim_policy() -> address_reclaim_t { return _reclaim_policy; }
        inline auto reclaim_policy(address_reclaim_t ReclaimPolicy) -> address_region_t *
        {
            _reclaim_policy = ReclaimPolicy;
            return this;
        }

        inline auto prev() -> address_region_t * { return _prev; }

        inline auto next() -> address_region_t * { return _next; }
    };

    class address_space_t {
    private:
        address_region_t* _first;
        address_region_t* _last;

        uintptr_t _lowestAddress;
        size_t _spaceSize;

    public:
        inline auto first() -> address_region_t * { return _first; }
        inline auto last() -> address_region_t * { return _last; }

        address_space_t(uintptr_t LowestAddress, size_t Size);

        auto find_region_containing(uintptr_t address) -> _<address_region_t*>;

        /// Creates a region with the specified size and extent in this address space
        auto define_region(uintptr_t base, size_t extent) -> address_region_t*;
    };
}
