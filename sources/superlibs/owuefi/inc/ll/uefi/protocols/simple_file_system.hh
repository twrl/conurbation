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

template <> constexpr guid_t ll::UEFI::protocol_guid_v<ll::UEFI::Protocols::simple_file_system_p> = "964e5b22-6459-11d2-8e39-00a0c969723b"_guid;
//"964e5b22-6459-11d2-8e39-00a0c969723b"_guid;
