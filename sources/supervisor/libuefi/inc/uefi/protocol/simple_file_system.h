#pragma once

#include "uefi/efitypes.h"
#include "uefi/protocol/file.h"

struct efi_simple_file_system_p;

extern "C" typedef efi_status_t (efi_simple_file_sysem_protocol_open_volume_f)(efi_simple_file_system_p* this, efi_file_p** root);

struct efi_simple_file_system_p {
    uint64_t        Revision;
    efiapi efi_simple_file_sysem_protocol_open_volume_f* OpenVolume;
};
