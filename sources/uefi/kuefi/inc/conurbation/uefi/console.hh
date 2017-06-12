#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/tables.hh"
#include "conurbation/uefi/protocol/simple_text_output.hh"

namespace Conurbation::UEFI {

    class console_logging_t {

    private:
        efi_simple_text_output_p* ConOut_;

    public:

        console_logging_t(efi_simple_text_output_p*);

        auto error(const char16_t* Message) -> console_logging_t*;
        auto warn(const char16_t* Message) -> console_logging_t*;
        auto info(const char16_t* Message) -> console_logging_t*;
        auto debug(const char16_t* Message) -> console_logging_t*;


        static auto operator new (size_t size, efi_system_table_t* SystemTable) -> void*;
        static auto operator delete (void* ptr, efi_system_table_t* SystemTable) -> void;
    };

}
