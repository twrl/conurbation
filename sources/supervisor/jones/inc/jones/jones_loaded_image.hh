#pragma once

#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/tables.hh"
#include "conurbation/uefi/device_path.hh"

namespace Jones {

    struct jones_loaded_image_p;

    struct jones_loaded_image_p {
        Conurbation::UEFI::efi_system_table_t* SystemTable;
        Conurbation::UEFI::handle_t* ImageHandle;
        Conurbation::UEFI::handle_t* ParentHandle;
        Conurbation::UEFI::efi_device_path_p* ImageFilePath;

        uintptr_t BeginLoadHeaders;
        size_t SizeLoadHeaders;
        size_t CountLoadHeaders;


    };

}

//extern template <> guid_t Conurbation::UEFI::protocol_guid_v<Jones::jones_loaded_image_p>;
