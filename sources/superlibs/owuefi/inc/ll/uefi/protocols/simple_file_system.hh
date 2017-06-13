#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/file.hh"

namespace ll::UEFI::Protocols {

    struct simple_file_system_p;

    typedef status_t(efiabi simple_file_sysem_protocol_open_volume_f)(
        simple_file_system_p* _this, file_p** root);

    struct simple_file_system_p {
        uint64_t Revision;
        simple_file_sysem_protocol_open_volume_f* OpenVolume;
    };

}
