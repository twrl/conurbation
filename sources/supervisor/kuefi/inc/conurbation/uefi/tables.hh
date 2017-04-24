#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"
#include "conurbation/uefi/device_path.hh"
#include "conurbation/uefi/simple_text_input.hh"
#include "conurbation/uefi/simple_text_output.hh"

namespace Conurbation::UEFI
{

    struct efi_table_header_t {
        uint64_t signature;
        uint32_t revision;
        uint32_t headerSize;
        uint32_t crc32;
        uint32_t reserved;
    };

    // Runtime services function types
    typedef status_t(efiabi efi_get_next_variable_name_f)(
        uintptr_t * variableNameSize, char16_t* variableName, guid_t* vendorGuid);
    typedef status_t(efiabi efi_get_variable_f)(
        char16_t* variableName, guid_t* vendorGuid, variable_attributes_t* attributes, uintptr_t* dataSize, void* data);
    typedef status_t(efiabi efi_set_variable_f)(
        char16_t* variableName, guid_t* vendorGuid, variable_attributes_t attributes, uintptr_t dataSize, void* data);
    typedef status_t(efiabi efi_set_virtual_address_map_f)(uintptr_t memoryMapSize, uintptr_t descriptorSize,
        uint32_t descriptorVersion, memory_descriptor_t * virtualMap);
    typedef status_t(efiabi efi_get_time_f)(time_t * time, time_capabilities_t * timeCapabilities);
    typedef status_t(efiabi efi_set_time_f)(time_t * time);
    typedef status_t(efiabi efi_get_wakeup_time_f)(bool_t * enabled, bool_t * pending, time_t * time);
    typedef status_t(efiabi efi_set_wakeup_time_f)(bool_t enable, time_t * time);
    typedef status_t(efiabi efi_convert_pointer_f)(uintptr_t debugDisposition, void** address);
    typedef void(efi_reset_system_f)(reset_type_t resetType, status_t resetStatus, uintptr_t dataSize, void* resetData);
    typedef status_t(efiabi efi_get_next_high_mono_count_f)(uint32_t * highCount);
    typedef status_t(efiabi efi_update_capsule_f)(
        capsule_header_t * *capsuleHeaderArray, uintptr_t capsuleCount, uint64_t scatterGatherList);
    typedef status_t(efiabi efi_query_capsule_capabilities_f)(capsule_header_t * *capsuleHeaderArray,
        uintptr_t capsuleCount, uint64_t * maximumCapsuleSize, reset_type_t * resetType);
    typedef status_t(efiabi efi_query_variable_info_f)(variable_attributes_t attributes,
        uint64_t * maximumVariableStorageSize, uint64_t * remainingVariableStorageSize, uint64_t * maximumVariableSize);

    struct efi_runtime_services_t {
        efi_table_header_t Hdr;

        efi_get_time_f* GetTime;
        efi_set_time_f* SetTime;
        efi_get_wakeup_time_f* GetWakeupTime;
        efi_set_wakeup_time_f* SetWakeupTime;
        efi_set_virtual_address_map_f* SetVirtualAddressMap;
        efi_convert_pointer_f* ConvertPointer;
        efi_get_variable_f* GetVariable;
        efi_get_next_variable_name_f* GetNextVariableName;
        efi_set_variable_f* SetVariable;
        efi_get_next_high_mono_count_f* GetNextHighMonotonicCount;
        efi_reset_system_f* ResetSystem;
        efi_update_capsule_f* UpdateCapsule;
        efi_query_capsule_capabilities_f* QueryCapsuleCapabilities;
        efi_query_variable_info_f* QueryVariableInfo;
    };

    // Boot services function types

    typedef status_t(efiabi efi_allocate_pages_f)(
        allocate_type_t type, memory_type_t memoryType, uintptr_t pages, uint64_t * memory);
    typedef status_t(efiabi efi_allocate_pool_f)(memory_type_t poolType, uintptr_t size, void** buffer);
    typedef status_t(efiabi efi_calculate_crc32_f)(void* data, uintptr_t dataSize, uint32_t* crc32);
    typedef status_t(efiabi efi_close_event_f)(event_t event);
    typedef status_t(efiabi efi_close_protocol_f)(
        handle_t handle, const guid_t * protocol, handle_t agentHandle, handle_t controllerHandle);
    typedef void(efiabi efi_copy_mem_f)(void* destination, void* source, uintptr_t length);
    typedef status_t(efiabi efi_create_event_f)(
        uint32_t type, tpl_t notifyTpl, event_notify_f * notifyFunction, void* notifyContext, event_t* event);
    typedef status_t(efiabi efi_create_event_ex_f)(uint32_t type, tpl_t notifyTpl, event_notify_f * notifyFunction,
        const void* notifyContext, const guid_t* eventGroup, event_t* event);
    typedef status_t(efiabi efi_exit_f)(
        handle_t imageHandle, status_t exitStatus, uintptr_t exitDataSize, char16_t* exitData);
    typedef status_t(efiabi efi_exit_boot_services_f)(handle_t imageHandle, uintptr_t mapKey);
    typedef status_t(efiabi efi_free_pages_f)(uint64_t memory, uintptr_t pages);
    typedef status_t(efiabi efi_free_pool_t)(void* buffer);
    typedef status_t(efiabi efi_get_memory_map_f)(uintptr_t * memoryMapSize, memory_descriptor_t * memoryMap,
        uintptr_t * mapKey, uintptr_t * descriptorSize, uint32_t * descriptorVersion);
    typedef status_t(efiabi efi_get_next_monotonic_count_f)(uint64_t * count);
    typedef status_t(efiabi efi_handle_protocol_f)(handle_t handle, const guid_t * protocol, void** interface);
    typedef status_t(efiabi efi_install_configuration_table_f)(const guid_t * guid, void* table);
    typedef status_t(efiabi efi_install_protocol_interface_f)(
        handle_t * handle, const guid_t * protocol, interface_type_t interfaceType, void* interface);
    typedef status_t(efiabi efi_load_image_f)(bool_t bootPolicy, handle_t parentImageHandle,
        efi_device_path_p * devicePath, void* sourcebuffer, uintptr_t sourceSize, handle_t* imageHandle);
    typedef status_t(efiabi efi_locate_device_path_f)(
        const guid_t * protocol, efi_device_path_p * *devicePath, handle_t * device);
    typedef status_t(efiabi efi_locate_handle_f)(
        locate_search_type_t searchType, const guid_t * protocol, void* searchKey, uintptr_t* bufferSize, handle_t* buffer);
    typedef status_t(efiabi efi_locate_protocol_f)(const guid_t * protocol, void* registration, void** interface);
    typedef status_t(efiabi efi_open_protocol_f)(handle_t handle, const guid_t * protocol, void** interface,
        handle_t agentHandle, handle_t controllerHandle, uint32_t attributes);
    typedef status_t(efiabi efi_open_protocol_information_f)(
        handle_t handle, const guid_t * protocol, open_protocol_information_entry_t * *entryBuffer, uintptr_t * entryCount);
    typedef tpl_t(efiabi efi_raise_tpl_f)(tpl_t newTpl);
    typedef void(efiabi efi_restore_tpl_f)(tpl_t oldTpl);
    typedef status_t(efiabi efi_reinstall_protocol_interface_f)(
        handle_t handle, const guid_t * protocol, void* oldInterface, void* newInterface);
    typedef status_t(efiabi efi_register_protocol_notify_f)(const guid_t * protocol, event_t event, void** registration);
    typedef void(efiabi efi_set_mem_f)(void* buffer, uintptr_t size, uint8_t value);
    // set_event
    typedef status_t(efiabi efi_set_timer_f)(event_t event, timer_delay_t type, uint64_t triggerTime);
    typedef status_t(efiabi efi_set_watchdog_timer_f)(
        uintptr_t timeout, uint64_t watchdogCode, uintptr_t dataSize, char16_t* watchdogData);
    typedef status_t(efiabi efi_signal_event_f)(event_t event);
    typedef status_t(efiabi efi_stall_f)(uintptr_t microseconds);
    typedef status_t(efiabi efi_start_image_f)(handle_t imageHandle, uintptr_t * exitDataSize, char16_t** exitData);
    typedef status_t(efiabi efi_uninstall_protocol_interface_f)(handle_t handle, const guid_t * protocol, void* interface);
    typedef status_t(efiabi efi_wait_for_event_f)(uintptr_t numberOfEvents, event_t * event, uintptr_t * index);

    typedef status_t(efiabi efi_check_event_f)(event_t event);
    typedef status_t(efiabi efi_unload_image_f)(handle_t imageHandle);
    // typedef EFI_STATUS(EFIAPI * EFI_CONNECT_CONTROLLER)(IN EFI_HANDLE ControllerHandle, IN EFI_HANDLE
    // *DriverImageHandle, OPTIONAL IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, OPTIONAL IN
    // BOOLEAN Recursive)
    typedef status_t(efiabi efi_connect_controller_f)(handle_t ControllerHandle, handle_t * driverImageHandle,
        efi_device_path_p * remainingDevicePath, bool_t recursive);
    // typedef EFI_STATUS(EFIAPI * EFI_DISCONNECT_CONTROLLER)(IN EFI_HANDLE ControllerHandle, IN
    // EFI_HANDLE DriverImageHandle, OPTIONAL IN EFI_HANDLE ChildHandle OPTIONAL)
    typedef status_t(efiabi efi_disconnect_controller_f)(
        handle_t ControllerHandle, handle_t driverImageHandle, handle_t ChildHandle);
    // typedef EFI_STATUS(EFIAPI * EFI_PROTOCOLS_PER_HANDLE)(IN EFI_HANDLE Handle, OUT EFI_GUID
    // ***ProtocolBuffer, OUT UINTN *ProtocolBufferCount)
    typedef status_t(efiabi efi_protocols_per_handle_f)(
        handle_t handle, const guid_t * **protocolBuffer, uintptr_t * protocolBufferCount);
    // typedef EFI_STATUS(EFIAPI * EFI_LOCATE_HANDLE_BUFFER)(IN EFI_LOCATE_SEARCH_TYPE SearchType, IN
    // EFI_GUID *Protocol, OPTIONAL IN VOID *SearchKey, OPTIONAL IN OUT UINTN *NoHandles, OUT EFI_HANDLE
    // **Buffer)
    typedef status_t(efiabi efi_locate_handle_buffer_f)(
        locate_search_type_t searchType, const guid_t * protocol, void* searchKey, uintptr_t* noHandles, handle_t** buffer);
    typedef status_t(efiabi efi_install_multiple_protocol_interfaces_f)(handle_t * handle, ...);
    typedef status_t(efiabi efi_uninstall_multiple_protocol_interfaces_f)(handle_t * handle, ...);

    struct efi_boot_services_t {
        efi_table_header_t Hdr;

        efi_raise_tpl_f* RaiseTPL;
        efi_restore_tpl_f* RestoreTPL;
        efi_allocate_pages_f* AllocatePages;
        efi_free_pages_f* FreePages;
        efi_get_memory_map_f* GetMemoryMap;
        efi_allocate_pool_f* AllocatePool;
        efi_free_pool_t* FreePool;
        efi_create_event_f* CreateEvent;
        efi_set_timer_f* SetTimer;
        efi_wait_for_event_f* WaitForEvent;
        efi_signal_event_f* SignalEvent;
        efi_close_event_f* CloseEvent;
        efi_check_event_f* CheckEvent; //?
        efi_install_protocol_interface_f* InstallProtocolInterface;
        efi_reinstall_protocol_interface_f* ReinstallProtocolInterface;
        efi_uninstall_protocol_interface_f* UninstallProtocolInterface;
        efi_handle_protocol_f* HandleProtocol;
        void* _reserved;
        efi_register_protocol_notify_f* RegisterProtocolNotify;
        efi_locate_handle_f* LocateHandle;
        efi_locate_device_path_f* LocateDevicePath;
        efi_install_configuration_table_f* InstallConfigurationTable;
        efi_load_image_f* LoadImage;
        efi_start_image_f* StartImage;
        efi_exit_f* Exit;
        efi_unload_image_f* UnloadImage; //?
        efi_exit_boot_services_f* ExitBootServices;
        efi_get_next_monotonic_count_f* GetNextMonotonicCount;
        efi_stall_f* Stall;
        efi_set_watchdog_timer_f* SetWatchdogTimer;
        efi_connect_controller_f* ConnectController; //?
        efi_disconnect_controller_f* DisconnectController; //?
        efi_open_protocol_f* OpenProtocol;
        efi_close_protocol_f* CloseProtocol;
        efi_open_protocol_information_f* OpenProtocolInformation;
        efi_protocols_per_handle_f* ProtocolsPerHandle; //?
        efi_locate_handle_buffer_f* LocateHandleBuffer; //?
        efi_locate_protocol_f* LocateProtocol;
        efi_install_multiple_protocol_interfaces_f* InstallMultipleProtocolInterfaces; //?
        efi_uninstall_multiple_protocol_interfaces_f* UninstallMultipleProtocolInterfaces; //?
        efi_calculate_crc32_f* CalculateCrc32;
        efi_copy_mem_f* CopyMem;
        efi_set_mem_f* SetMem;
        efi_create_event_ex_f* CreateEventEx;
    };

    struct efi_configuration_t {
        guid_t VendorGuid;
        void* VendorTable;
    };

    struct efi_system_table_t {
        efi_table_header_t Hdr;
        char16_t* FirmwareVendor;
        uint32_t FirmwareRevision;

        handle_t ConsoleInHandle;
        efi_simple_text_input_p* ConIn;
        handle_t ConsoleOutHandle;
        efi_simple_text_output_p* ConOut;
        handle_t StandardErrorHandle;
        efi_simple_text_output_p* StdErr;

        efi_runtime_services_t* RuntimeServices;
        efi_boot_services_t* BootServices;

        uintptr_t NumberOfTableEntries;
        efi_configuration_t* ConfigurationTable;
    };
}
