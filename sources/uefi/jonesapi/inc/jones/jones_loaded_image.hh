#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/device_path.hh"

namespace Jones {

    struct jones_loaded_image_p;

    struct jones_loaded_image_p {
        ll::UEFI::Tables::system_table_t* SystemTable;
        ll::UEFI::handle_t* ImageHandle;
        ll::UEFI::handle_t* ParentHandle;
        ll::UEFI::Protocols::device_path_p* ImageFilePath;

        uintptr_t BeginLoadHeaders;
        size_t SizeLoadHeaders;
        size_t CountLoadHeaders;


    };

}

//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loaded_image_p>;
