#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "conurbation/acpi/tables.hh"

namespace Conurbation::ACPI
{

    struct madt_table_t : acpi_sdt_header_t {
        uint32_t local_controller;
        uint32_t flags;
    };

    enum class madt_entry_type_t : uint8_t { local_apic = 0, io_apic = 1, int_src_override = 2 };

    struct madt_entry_header_t {
        madt_entry_type_t entry_type;
        uint8_t entry_length;
    };

    struct madt_entry_lapic_t : madt_entry_header_t {
        uint8_t processor_id;
        uint8_t apic_id;
        uint32_t flags;
    };

    struct madt_entry_ioapic_t {
        uint8_t apic_id;
        uint8_t reservedZ;
        uint32_t ioapic_address;
        uint32_t gsi_base;
    };

    struct madt_entry_isoverride_t : madt_entry_header_t {
        uint8_t bus_source;
        uint8_t irq_source;
        uint32_t gsi;
        uint16_t flags;
    };
};
