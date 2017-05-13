#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/result.hh"
#include "conurbation/uefi/efi_types.hh"

namespace Conurbation::Elements {

    enum class address_tag_type_t {
        efiMemoryType
    };

    class address_range_t {

    private:
        uintptr_t start_;
        uintptr_t end_;
        address_tag_type_t tag_type_;
        union {
            Conurbation::UEFI::memory_type_t efi_memory_type;
        };

    public:
        inline auto start() -> uintptr_t const { return start_; }
        inline auto end() -> uintptr_t const { return end_; }
        inline auto tag_type() -> address_tag_type_t const { return tag_type_; }

        inline auto efiMemoryType() -> result_t<Conurbation::UEFI::memory_type_t> const {
            if (tag_type_ == address_tag_type_t::efiMemoryType) return efi_memory_type;
            else return status_t::incorrectSubtype;
        }


    };

    

}
