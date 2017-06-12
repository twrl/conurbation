#pragma once

#include "conurbation/uefi/protocol/device_path.hh"
#include "conurbation/uefi/tables.hh"

namespace Conurbation::UEFI {

    class device_path_builder_t {

    public:
        device_path_builder_t(device_path_p* rootPath);
        device_path_builder_t(handle_t devicehandle, efi_system_table_t* SystemTable);

        auto File(const char16_t* path) -> device_path_builder_t&;


    }

}
