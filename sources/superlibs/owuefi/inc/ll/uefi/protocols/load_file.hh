#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Protocols {

    struct load_file_p;

    typedef status_t(efiabi load_file_f)(load_file_p* _this, device_path_p* FilePath, bool_t BootPolicy, uintptr_t BufferSize, void* Buffer);

    struct load_file_p {
        load_file_f* LoadFile;
    };

}
