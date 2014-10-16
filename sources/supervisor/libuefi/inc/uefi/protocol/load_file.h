#pragma once

#include "uefi/efitypes.h"
#include "uefi/protocol/device_path.h"

struct efi_load_file_p;

extern "C" typedef efi_status_t (efi_load_file_f)(efi_load_file_p* this, efi_device_path_p* filePath, bool_t bootPolicy, uintptr_t* bufferSize, void* buffer);

struct efi_load_file_p {
    efiapi efi_load_file_f* LoadFile;
}