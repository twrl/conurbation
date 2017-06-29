#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/tables/system.hh"

namespace ll::UEFI::Protocols {

    struct loaded_image_p;

    typedef status_t(efiabi image_unload_f)(handle_t imageHandle);

    struct loaded_image_p {
        uint32_t Revision;
        handle_t ParentHandle;
        Tables::system_table_t* SystemTable;
        handle_t DeviceHandle;
        device_path_p* FilePath;
        void* Reserved;
        uint32_t LoadOptionsSize;
        void* LoadOptions;
        void* ImageBase;
        uint64_t ImageSize;
        memory_type_t ImageCodeType;
        memory_type_t ImageDataType;
        image_unload_f* Unload;
    };

    typedef status_t (efiabi efi_entry_point_f)(handle_t, Tables::system_table_t);

}

template <> constexpr guid_t ll::UEFI::protocol_guid_v<ll::UEFI::Protocols::loaded_image_p> = "5b1b31a1-9562-11d2-8e3f-00a0c969723b"_guid;
