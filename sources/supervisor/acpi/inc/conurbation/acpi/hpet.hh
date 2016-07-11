#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "conurbation/acpi/tables.hh"

namespace Conurbation::ACPI
{

    struct hpet_table_t : acpi_sdt_header_t {
        uint8_t hardware_revision;
        uint8_t num_comparators : 4;
        uint8_t counter_size : 1;
        uint8_t : 1;
        uint8_t legacy_replacement : 1;
        uint16_t pci_vendor;
        generic_address_t address;
        uint8_t hpet_number;
        uint16_t min_tick;
        uint8_t page_protection;
    } __attribute__((packed));
}
