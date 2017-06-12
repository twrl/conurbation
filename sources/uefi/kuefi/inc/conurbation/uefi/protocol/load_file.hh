#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/protocol/device_path.hh"

namespace Conurbation::UEFI
{

    struct efi_load_file_p;

    typedef status_t(efiabi efi_load_file_f)(efi_load_file_p* _this, efi_device_path_p* FilePath, bool_t BootPolicy, uintptr_t BufferSize, void* Buffer);

    struct efi_load_file_p {
        efi_load_file_f* LoadFile;
    };

}
