#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"

namespace Conurbation::UEFI
{

    struct efi_simple_text_input_p;

    typedef status_t(efiabi efi_input_reset_f)(efi_simple_text_input_p * _this, bool_t exendedVerification);
    typedef status_t(efiabi efi_input_read_key_f)(efi_simple_text_input_p * _this, input_key_t * key);

    struct efi_simple_text_input_p {
        efi_input_reset_f* Reset;
        efi_input_read_key_f* ReadKeyStroke;
        event_t WaitForKey;
    };

    template <> constexpr guid_t protocol_guid_v<efi_simple_text_input_p> = "387477c1-69c7-11d2-8e39-00a0c969723b"_guid;
}
