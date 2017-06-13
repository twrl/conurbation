#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/device_path.hh"

namespace ll::UEFI::Protocols {

    typedef uintptr_t(efiabi device_path_utils_get_device_path_size_f)(const device_path_p* DevicePath);
    typedef device_path_p*(efiabi device_path_utils_dup_device_path_f)(const device_path_p* DevicePath);
    typedef device_path_p*(efiabi device_path_utils_append_path_f)(const device_path_p* src1, const device_path_p* src2);
    typedef device_path_p*(efiabi device_path_utils_append_node_f)(const device_path_p* DevicePath, const device_path_p* DeviceNode);
    typedef device_path_p*(efiabi device_path_utils_append_instance_f)(const device_path_p* DevicePath, const device_path_p* DevicePathInstance);
    typedef device_path_p*(efiabi device_path_utils_get_next_instance_f)(device_path_p** DevicePathInstance, uintptr_t* DevicePathInstanceSize);
    typedef device_path_p*(efiabi device_path_utils_create_node_f)(uint8_t nodeType, uint8_t nodeSubtype, uint16_t nodeLength);
    typedef bool_t(efiabi device_path_utils_is_multi_instance_f)(const device_path_p* DevicePath);

    struct device_path_utilities_p {
        device_path_utils_get_device_path_size_f* GetDevicePathSize;
        device_path_utils_dup_device_path_f* DuplicateDevicePath;
        device_path_utils_append_path_f* AppendDevicePath;
        device_path_utils_append_node_f* AppendDeviceNode;
        device_path_utils_append_instance_f* AppendDevicePathInstance;
        device_path_utils_get_next_instance_f* GetNextDevicePathInstance;
        device_path_utils_is_multi_instance_f* IsDevicePathMultiInstance;
        device_path_utils_create_node_f* CreateDeviceNode;
    };

}
