#pragma once

#include "uefi/efitypes.h"

struct efi_simple_text_input_p;

extern "C" {
    typedef efi_status_t (efiapi efi_input_reset_f)(efi_simple_text_input_p* this, bool_t exendedVerification);
    typedef efi_status_t (efiapi efi_input_read_key_f)(efi_simple_text_input_p* this, efi_input_key_t* key);
}

struct efi_simple_text_input_p {
    efi_input_reset_f*          Reset;
    efi_input_read_key_f*       ReadKeyStroke;
    efi_event_t                 WaitForKey;
};

