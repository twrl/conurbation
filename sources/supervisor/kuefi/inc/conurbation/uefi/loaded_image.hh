#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/guid.hh"
#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/tables.hh"

namespace Conurbation::UEFI
{

    struct efi_loaded_image_p;

    typedef status_t(efiabi efi_image_unload_f)(handle_t imageHandle);

    struct efi_loaded_image_p {
        uint32_t Revision;
        handle_t ParentHandle;
        efi_system_table_t* SystemTable;
        handle_t DeviceHandle;
        efi_device_path_p* FilePath;
        void* Reserved;
        uint32_t LoadOptionsSize;
        void* LoadOptions;
        void* ImageBase;
        uint64_t ImageSize;
        memory_type_t ImageCodeType;
        memory_type_t ImageDataType;
        efi_image_unload_f* Unload;
    };


}
