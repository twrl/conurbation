#include "conurbation/hwres/addrspace.h"

namespace Conurbation::HwRes
{

    address_region_t::address_region_t(address_space_t * Space, uintptr_t Base, size_t Extent)
        : _address_space(Space)
        , _base(Base)
        , _extent(Extent)
    {
    }

    address_space_t::address_space_t(uintptr_t LowestAddress, size_t Size)
        : _lowestAddress(LowestAddress)
        , _spaceSize(Size)
        , _first(nullptr)
        , _last(nullptr)
    {
        address_region_t* region = new address_region_t(this, LowestAddress, Size);
        this->_first = region;
        this->_last = region;
    }

    auto address_space_t::find_region_containing(uintptr_t address)->_<address_region_t*>
    {
        address_region_t* current = this->_first;

        while (true) {
            if (current->base() <= address && current->limit() > address)
                return current;
            if (current == _last)
                return status_t::NotFound;
            current = current->next();
        }
    }

    auto address_space_t::define_region(uintptr_t base, size_t extent)->address_region_t *
    {

        // Most general case: base and limit of the new region are currently in two (possibly) different regions, with 0 or
        // more regions in between
        //_<address_region_t*> sr;
        address_region_t* base_region;
        address_region_t* limit_region;

        _<address_region_t*> sr = find_region_containing(base);
        if (!sr)
            return nullptr; ///(do something else)
        base_region = static_cast<address_region_t*>(sr);

        if (base_region->base() != base) {
            address_region_t* nr = new address_region_t(this, base, 0);
            nr->limit(base_region->limit());
            nr->backing_mode(base_region->backing_mode())
                ->backing_region(base_region->backing_region())
                ->reclaim_policy(base_region->reclaim_policy())
                ->usage(base_region->usage());
            nr->_prev = base_region;
            nr->_next = base_region->_next;
            base_region->limit(base - 1);
            base_region->_next = nr;
            base_region = nr;
        }

        sr = find_region_containing(base + extent);
        if (!sr)
            return nullptr; /// (do something else)
        limit_region = static_cast<address_region_t*>(sr);

        if (limit_region->limit() != base + extent) {
            address_region_t* nr = new address_region_t(this, base + extent, 0);
            nr->limit(limit_region->limit());
            nr->backing_mode(limit_region->backing_mode())
                ->backing_region(limit_region->backing_region())
                ->reclaim_policy(limit_region->reclaim_policy())
                ->usage(limit_region->usage());
            nr->_prev = limit_region;
            nr->_next = limit_region->_next;
            limit_region->limit(base + extent - 1);
            limit_region->_next = nr;
        }

        while (base_region->extent() < extent) {
            address_region_t* nr = base_region->next();
            base_region->limit(nr->limit());
            base_region->_next = nr->_next;
            base_region->_next->_prev = base_region;
            delete nr;
        }

        return base_region;
    }
}
