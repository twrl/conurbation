#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Tables {

    typedef status_t(efiabi allocate_pages_f)(
        allocate_type_t type, memory_type_t memoryType, uintptr_t pages, uint64_t * memory);
    typedef status_t(efiabi allocate_pool_f)(memory_type_t poolType, uintptr_t size, void** buffer);
    typedef status_t(efiabi calculate_crc32_f)(void* data, uintptr_t dataSize, uint32_t* crc32);
    typedef status_t(efiabi close_event_f)(event_t event);
    typedef status_t(efiabi close_protocol_f)(
        handle_t handle, const guid_t * protocol, handle_t agentHandle, handle_t controllerHandle);
    typedef void(efiabi copy_mem_f)(void* destination, void* source, uintptr_t length);
    typedef status_t(efiabi create_event_f)(
        uint32_t type, tpl_t notifyTpl, event_notify_f * notifyFunction, void* notifyContext, event_t* event);
    typedef status_t(efiabi create_event_ex_f)(uint32_t type, tpl_t notifyTpl, event_notify_f * notifyFunction,
        const void* notifyContext, const guid_t* eventGroup, event_t* event);
    typedef status_t(efiabi exit_f)(
        handle_t imageHandle, status_t exitStatus, uintptr_t exitDataSize, char16_t* exitData);
    typedef status_t(efiabi exit_boot_services_f)(handle_t imageHandle, uintptr_t mapKey);
    typedef status_t(efiabi free_pages_f)(uint64_t memory, uintptr_t pages);
    typedef status_t(efiabi free_pool_t)(void* buffer);
    typedef status_t(efiabi get_memory_map_f)(uintptr_t * memoryMapSize, memory_descriptor_t * memoryMap,
        uintptr_t * mapKey, uintptr_t * descriptorSize, uint32_t * descriptorVersion);
    typedef status_t(efiabi get_next_monotonic_count_f)(uint64_t * count);
    typedef status_t(efiabi handle_protocol_f)(handle_t handle, const guid_t * protocol, void** interface);
    typedef status_t(efiabi install_configuration_table_f)(const guid_t * guid, void* table);
    typedef status_t(efiabi install_protocol_interface_f)(
        handle_t * handle, const guid_t * protocol, interface_type_t interfaceType, void* interface);
    typedef status_t(efiabi load_image_f)(bool_t bootPolicy, handle_t parentImageHandle,
        Protocols::device_path_p * devicePath, void* sourcebuffer, uintptr_t sourceSize, handle_t* imageHandle);
    typedef status_t(efiabi locate_device_path_f)(
        const guid_t * protocol, Protocols::device_path_p * *devicePath, handle_t * device);
    typedef status_t(efiabi locate_handle_f)(
        locate_search_type_t searchType, const guid_t * protocol, void* searchKey, uintptr_t* bufferSize, handle_t* buffer);
    typedef status_t(efiabi locate_protocol_f)(const guid_t * protocol, void* registration, void** interface);
    typedef status_t(efiabi open_protocol_f)(handle_t handle, const guid_t * protocol, void** interface,
        handle_t agentHandle, handle_t controllerHandle, uint32_t attributes);
    typedef status_t(efiabi open_protocol_information_f)(
        handle_t handle, const guid_t * protocol, open_protocol_information_entry_t * *entryBuffer, uintptr_t * entryCount);
    typedef tpl_t(efiabi raise_tpl_f)(tpl_t newTpl);
    typedef void(efiabi restore_tpl_f)(tpl_t oldTpl);
    typedef status_t(efiabi reinstall_protocol_interface_f)(
        handle_t handle, const guid_t * protocol, void* oldInterface, void* newInterface);
    typedef status_t(efiabi register_protocol_notify_f)(const guid_t * protocol, event_t event, void** registration);
    typedef void(efiabi set_mem_f)(void* buffer, uintptr_t size, uint8_t value);
    // set_event
    typedef status_t(efiabi set_timer_f)(event_t event, timer_delay_t type, uint64_t triggerTime);
    typedef status_t(efiabi set_watchdog_timer_f)(
        uintptr_t timeout, uint64_t watchdogCode, uintptr_t dataSize, char16_t* watchdogData);
    typedef status_t(efiabi signal_event_f)(event_t event);
    typedef status_t(efiabi stall_f)(uintptr_t microseconds);
    typedef status_t(efiabi start_image_f)(handle_t imageHandle, uintptr_t * exitDataSize, char16_t** exitData);
    typedef status_t(efiabi uninstall_protocol_interface_f)(handle_t handle, const guid_t * protocol, void* interface);
    typedef status_t(efiabi wait_for_event_f)(uintptr_t numberOfEvents, event_t * event, uintptr_t * index);

    typedef status_t(efiabi check_event_f)(event_t event);
    typedef status_t(efiabi unload_image_f)(handle_t imageHandle);
    // typedef STATUS(EFIAPI * CONNECT_CONTROLLER)(IN HANDLE ControllerHandle, IN HANDLE
    // *DriverImageHandle, OPTIONAL IN Protocols::device_path_pROTOCOL *RemainingDevicePath, OPTIONAL IN
    // BOOLEAN Recursive)
    typedef status_t(efiabi connect_controller_f)(handle_t ControllerHandle, handle_t * driverImageHandle,
        Protocols::device_path_p * remainingDevicePath, bool_t recursive);
    // typedef STATUS(EFIAPI * DISCONNECT_CONTROLLER)(IN HANDLE ControllerHandle, IN
    // HANDLE DriverImageHandle, OPTIONAL IN HANDLE ChildHandle OPTIONAL)
    typedef status_t(efiabi disconnect_controller_f)(
        handle_t ControllerHandle, handle_t driverImageHandle, handle_t ChildHandle);
    // typedef STATUS(EFIAPI * PROTOCOLS_PER_HANDLE)(IN HANDLE Handle, OUT GUID
    // ***ProtocolBuffer, OUT UINTN *ProtocolBufferCount)
    typedef status_t(efiabi protocols_per_handle_f)(
        handle_t handle, const guid_t * **protocolBuffer, uintptr_t * protocolBufferCount);
    // typedef STATUS(EFIAPI * LOCATE_HANDLE_BUFFER)(IN LOCATE_SEARCH_TYPE SearchType, IN
    // GUID *Protocol, OPTIONAL IN VOID *SearchKey, OPTIONAL IN OUT UINTN *NoHandles, OUT HANDLE
    // **Buffer)
    typedef status_t(efiabi locate_handle_buffer_f)(
        locate_search_type_t searchType, const guid_t * protocol, void* searchKey, uintptr_t* noHandles, handle_t** buffer);
    typedef status_t(efiabi install_multiple_protocol_interfaces_f)(handle_t * handle, ...);
    typedef status_t(efiabi uninstall_multiple_protocol_interfaces_f)(handle_t * handle, ...);

    struct boot_services_t: table_header_t {

        raise_tpl_f* RaiseTPL;
        restore_tpl_f* RestoreTPL;
        allocate_pages_f* AllocatePages;
        free_pages_f* FreePages;
        get_memory_map_f* GetMemoryMap;
        allocate_pool_f* AllocatePool;
        free_pool_t* FreePool;
        create_event_f* CreateEvent;
        set_timer_f* SetTimer;
        wait_for_event_f* WaitForEvent;
        signal_event_f* SignalEvent;
        close_event_f* CloseEvent;
        check_event_f* CheckEvent; //?
        install_protocol_interface_f* InstallProtocolInterface;
        reinstall_protocol_interface_f* ReinstallProtocolInterface;
        uninstall_protocol_interface_f* UninstallProtocolInterface;
        handle_protocol_f* HandleProtocol;
        void* _reserved;
        register_protocol_notify_f* RegisterProtocolNotify;
        locate_handle_f* LocateHandle;
        locate_device_path_f* LocateDevicePath;
        install_configuration_table_f* InstallConfigurationTable;
        load_image_f* LoadImage;
        start_image_f* StartImage;
        exit_f* Exit;
        unload_image_f* UnloadImage; //?
        exit_boot_services_f* ExitBootServices;
        get_next_monotonic_count_f* GetNextMonotonicCount;
        stall_f* Stall;
        set_watchdog_timer_f* SetWatchdogTimer;
        connect_controller_f* ConnectController; //?
        disconnect_controller_f* DisconnectController; //?
        open_protocol_f* OpenProtocol;
        close_protocol_f* CloseProtocol;
        open_protocol_information_f* OpenProtocolInformation;
        protocols_per_handle_f* ProtocolsPerHandle; //?
        locate_handle_buffer_f* LocateHandleBuffer; //?
        locate_protocol_f* LocateProtocol;
        install_multiple_protocol_interfaces_f* InstallMultipleProtocolInterfaces; //?
        uninstall_multiple_protocol_interfaces_f* UninstallMultipleProtocolInterfaces; //?
        calculate_crc32_f* CalculateCrc32;
        copy_mem_f* CopyMem;
        set_mem_f* SetMem;
        create_event_ex_f* CreateEventEx;
    };

}
