#pragma once

#include "uefi/efitypes.h"
#include "uefi/tables.h"
#include "uefi/protocol/device_path.h"

extern "C" {
    typedef efi_status_t (efi_image_unload_f)(efi_handle_t imageHandle);
}

struct efi_loaded_image_p {
            uint32_t                Revision;
            efi_handle_t            ParentHandle;
            efi_system_table_t*     SystemTable;
            efi_handle_t            DeviceHandle;
            efi_device_path_p*      FilePath;
            void*                   Reserved;
            uint32_t                LoadOptionsSize;
            void*                   LoadOptions;
            void*                   ImageBase;
            uint64_t                ImageSize;
            efi_memory_type_t       ImageCodeType;
            efi_memory_type_t       ImageDataType;
    efiapi  efi_image_unload_f*     Unload;
};

