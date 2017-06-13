#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/runtime_services.hh"
#include "ll/uefi/tables/boot_services.hh"
#include "ll/uefi/tables/configuration.hh"
#include "ll/uefi/protocols/simple_text_input.hh"
#include "ll/uefi/protocols/simple_text_output.hh"

namespace ll::UEFI::Tables {

    struct system_table_t: table_header_t {

        char16_t* firmware_vendor;
        uint32_t firmware_revision;

        handle_t console_in_handle;
        Protocols::simple_text_input_p* console_in;
        handle_t console_out_handle;
        Protocols::simple_text_output_p* console_out;
        handle_t stderr_handle;
        Protocols::simple_text_output_p* std_error;

        runtime_services_t* runtime_services;
        boot_services_t* BootServices;

        uintptr_t num_config_entries;
        configuration_t* configuration_table;

    };

}
