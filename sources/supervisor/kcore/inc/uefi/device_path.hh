#pragma once

#include "conurbation/uefi/efi_types.hh"

namespace Conurbation::UEFI
{

    enum efi_device_path_type_t : uint8_t {
        hardware = 1,
        acpi = 2,
        messaging = 3,
        media = 4,
        bbs = 5,

        END = 0x7f

    };

    struct efi_device_path_p {
        efi_device_path_type_t Type;
        uint8_t Subtype;
        uint8_t Length[2];
    };

    struct efi_pci_device_path_t {
        efi_device_path_p Header;
        uint8_t Function;
        uint8_t Device;
    };

    struct efi_pccard_device_path_t {
        efi_device_path_p Header;
        uint8_t FunctionNumber;
    };

    struct efi_memmap_device_path_t {
        efi_device_path_p Header;
        memory_type_t MemoryType;
        uint64_t StartingAddress;
        uint64_t EndingAddress;
    };

    struct efi_vendor_device_path_t {
        efi_device_path_p Header;
        guid_t Guid;
    };

    struct efi_controller_device_path_t {
        efi_device_path_p Header;
        uint32_t Controller;
    };
}
