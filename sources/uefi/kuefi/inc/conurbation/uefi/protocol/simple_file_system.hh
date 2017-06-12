#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/protocol/file.hh"

namespace Conurbation::UEFI
{

    struct efi_simple_file_system_p;

    typedef status_t(efiabi efi_simple_file_sysem_protocol_open_volume_f)(
        efi_simple_file_system_p* _this, efi_file_p** root);

    struct efi_simple_file_system_p {
        uint64_t Revision;
        efi_simple_file_sysem_protocol_open_volume_f* OpenVolume;
    };


}
