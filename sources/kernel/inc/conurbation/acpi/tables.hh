#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "conurbation/numeric_types.hh"
#include "conurbation/char_types.hh"

namespace Conurbation::ACPI
{

    struct generic_address_t {
        uint8_t address_space_id; // 0 - system memory, 1 - system I/O
        uint8_t register_bit_width;
        uint8_t register_bit_offset;
        uint8_t reserved;
        uint64_t address;
    };

    struct acpi_sdt_header_t {
        char8_t signature[4];
        uint32_t length;
        uint8_t revision;
        uint8_t checksum;
        char8_t oemid[6];
        char8_t oem_table_id[8];
        uint32_t oem_revision;
        uint32_t creator_id;
        uint32_t creator_revision;
    } __attribute__((packed));

    struct rsdt_table_t : acpi_sdt_header_t {
        uint32_t ptrs[];
    };

    struct xsdt_table_t : acpi_sdt_header_t {
        acpi_sdt_header_t* ptrs[];
    } __attribute__((packed));

    struct root_pointer_t {
        char8_t signature[8];
        uint8_t checksum;
        char8_t oemid[6];
        uint8_t revision;
        uint32_t rsdt_address;
        uint32_t length;
        xsdt_table_t* xsdt_address;
        uint8_t extended_checksum;
        uint8_t reserved[3];
    };
}
