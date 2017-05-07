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
        uint16_t Length;
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

    struct efi_file_media_device_path_t {
        efi_device_path_p Header;
    };

    struct efi_vendor_device_path_t {
        efi_device_path_p Header;
        guid_t Guid;
    };

    struct efi_controller_device_path_t {
        efi_device_path_p Header;
        uint32_t Controller;
    };

    typedef uintptr_t(efiabi efi_device_path_utils_get_device_path_size_f)(const efi_device_path_p* DevicePath);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_dup_device_path_f)(const efi_device_path_p* DevicePath);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_append_path_f)(const efi_device_path_p* src1, const efi_device_path_p* src2);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_append_node_f)(const efi_device_path_p* DevicePath, const efi_device_path_p* DeviceNode);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_append_instance_f)(const efi_device_path_p* DevicePath, const efi_device_path_p* DevicePathInstance);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_get_next_instance_f)(efi_device_path_p** DevicePathInstance, uintptr_t* DevicePathInstanceSize);
    typedef efi_device_path_p*(efiabi efi_device_path_utils_create_node_f)(uint8_t nodeType, uint8_t nodeSubtype, uint16_t nodeLength);
    typedef bool_t(efiabi efi_device_path_utils_is_multi_instance_f)(const efi_device_path_p* DevicePath);

    struct efi_device_path_utilities_p {
        efi_device_path_utils_get_device_path_size_f* GetDevicePathSize;
        efi_device_path_utils_dup_device_path_f* DuplicateDevicePath;
        efi_device_path_utils_append_path_f* AppendDevicePath;
        efi_device_path_utils_append_node_f* AppendDeviceNode;
        efi_device_path_utils_append_instance_f* AppendDevicePathInstance;
        efi_device_path_utils_get_next_instance_f* GetNextDevicePathInstance;
        efi_device_path_utils_is_multi_instance_f* IsDevicePathMultiInstance;
        efi_device_path_utils_create_node_f* CreateDeviceNode;
    };
}
