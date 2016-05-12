#pragma once

#include "uefi/efi_types.h"
#include "uefi/abi.h"
#include "uefi/file.h"

namespace UEFI::Protocol
{

    struct efi_simple_file_system_p;

    typedef status_t(efiabi efi_simple_file_sysem_protocol_open_volume_f)(efi_simple_file_system_p * this, efi_file_p * *root);

    struct efi_simple_file_system_p {
        uint64_t Revision;
        efi_simple_file_sysem_protocol_open_volume_f* OpenVolume;
    };

    template <> constexpr guid_t protocol_guid_v<efi_simple_file_system_p> = "0964e5b22-6459-11d2-8e39-00a0c969723b"_guid;
}
