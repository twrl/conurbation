#pragma once

#include "uefi/efitypes.h"

enum class efi_variable_attributes_t: uint32_t {
    nonVolatile = 0x00000001,
    bootServiceAccess = 0x00000002,
    runtimeAccess = 0x00000004,
    hardwareErrorRecord = 0x00000008,
    authenticatedWriteAccess = 0x00000010
    
};

// Table Header

struct efi_table_header_t {
    uint64_t                        signature;
    uint32_t                        revision;
    uint32_t                        headerSize;
    uint32_t                        crc32;
    uint32_t                        reserved;
};

// Runtime Services

extern "C" {
    typedef efi_status_t (efi_get_next_variable_name_f)(uintptr_t* variableNameSize, char16_t* variableName, guid_t* vendorGuid);
    typedef efi_status_t (efi_get_variable_f)(char16_t* variableName, guid_t* vendorGuid, efi_variable_attributes_t* attributes, uintptr_t* dataSize, void* data);
    typedef efi_status_t (efi_set_variable_f)(char16_t* variableName, guid_t* vendorGuid, efi_variable_attributes_t attributes, uintptr_t dataSize, void* data);
    typedef efi_status_t (efi_set_virtual_address_map_f)(uintptr_t memoryMapSize, uintptr_t descriptorSize, uint32_t descriptorVersion, efi_memory_descriptor_t* virtualMap);
    typedef efi_status_t (efi_get_time_f)(efi_time_t* time, efi_time_capabilities_t* timeCapabilities);
    typedef efi_status_t (efi_set_time_f)(efi_time_t* time);
    typedef efi_status_t (efi_get_wakeup_time_f)(bool_t* enabled, bool_t* pending, efi_time_t* time);
    typedef efi_status_t (efi_set_wakeup_time_f)(bool_t enable, efi_time_t* time);
    typedef efi_status_t (efi_convert_pointer_f)(uintptr_t debugDisposition, void** address);
    typedef void (efi_reset_system_f)(efi_reset_type_t resetType, efi_status_t resetStatus, uintptr_t dataSize, void* resetData);
    typedef efi_status_t (efi_get_next_high_mono_count_f)(uint32_t* highCount);
    typedef efi_status_t (efi_update_capsule_f)(efi_capsule_header_t** capsuleHeaderArray, uintptr_t capsuleCount, paddr_t scatterGatherList);
    typedef efi_status_t (efi_query_capsule_capabilities_f)(efi_capsule_header_t** capsuleHeaderArray, uintptr_t capsuleCount, uint64_t* maximumCapsuleSize, efi_reset_type_t* resetType);
    typedef efi_status_t (efi_query_variable_info_f)(efi_variable_attributes_t attributes, uint64_t* maximumVariableStorageSize, uint64_t* remainingVariableStorageSize, uint64_t* maximumVariableSize);
}


struct efi_runtime_services_t {
            efi_table_header_t              Hdr;
    
    efiapi  efi_get_time_f*                 GetTime;
    efiapi  efi_set_time_f*                 SetTime;
    efiapi  efi_get_wakeup_time_f*          GetWakeupTime;
    efiapi  efi_set_wakeup_time_f*          SetWakeupTime;
    efiapi  efi_set_virtual_address_map_f*  SetVirtualAddressMap;
    efiapi  efi_convert_pointer_f*          ConvertPointer;
    efiapi  efi_get_variable_f*             GetVariable;
    efiapi  efi_get_next_variable_name_f*   GetNextVariableName;
    efiapi  efi_set_variable_f*             SetVariable;
    efiapi  efi_get_next_high_mono_count_f* GetNextHighMonotonicCount;
    efiapi  efi_reset_system_f*             ResetSystem;
    efiapi  efi_update_capsule_f*           UpdateCapsule;
    efiapi  efi_query_capsule_capabilities_f* QueryCapsuleCapabilities;
    efiapi  efi_query_variable_info_f*      QueryVariableInfo;
};

// Boot Services

#include "uefi/protocol/device_path.h"


extern "C" {
    typedef efi_status_t (efi_allocate_pages_f)(efi_allocate_type_t type, efi_memory_type_t memoryType, uintptr_t pages, paddr_t* memory);
    typedef efi_status_t (efi_allocate_pool_f)(efi_memory_type_t poolType, uintptr_t size, void** buffer);
    typedef efi_status_t (efi_calculate_crc32_f)(void* data, uintptr_t dataSize, uint32_t* crc32);
    typedef efi_status_t (efi_close_event_f)(efi_event_t event);
    typedef efi_status_t (efi_close_protocol_f)(efi_handle_t handle, guid_t* protocol, efi_handle_t agentHandle, efi_handle_t controllerHandle);
    typedef void (efi_copy_mem_f)(void* destination, void* source, uintptr_t length);
    typedef efi_status_t (efi_create_event_f)(uint32_t type, efi_tpl_t notifyTpl, efi_event_notify_t notifyFunction, void* notifyContext, efi_event_t* event);
    typedef efi_status_t (efi_create_event_ex_f)(uint32_t type, efi_tpl_t notifyTpl, efi_event_notify_t notifyFunction, const void* notifyContext, const guid_t* eventGroup, efi_event_t* event);
    typedef efi_status_t (efi_exit_f)(efi_handle_t imageHandle, efi_status_t exitStatus, uintptr_t exitDataSize, char16_t* exitData);
    typedef efi_status_t (efi_exit_boot_services_f)(efi_handle_t imageHandle, uintptr_t mapKey);
    typedef efi_status_t (efi_free_pages_f)(paddr_t memory, uintptr_t pages);
    typedef efi_status_t (efi_free_pool_t)(void* buffer);
    typedef efi_status_t (efi_get_memory_map_f)(uintptr_t* memoryMapSize, efi_memory_descriptor_t* memoryMap, uintptr_t* mapKey, uintptr_t* descriptorSize, uint32_t* descriptorVersion);
    typedef efi_status_t (efi_get_next_monotonic_count_f)(uint64_t* count);
    typedef efi_status_t (efi_handle_protocol_f)(efi_handle_t handle, guid_t* protocol, void** interface);
    typedef efi_status_t (efi_install_configuration_table_f)(guid_t* guid, void* table);
    typedef efi_status_t (efi_install_protocol_interface_f)(efi_handle_t* handle, guid_t* protocol, efi_interface_type_t interfaceType, void* interface);
    typedef efi_status_t (efi_load_image_f)(bool_t bootPolicy, efi_handle_t parentImageHandle, efi_device_path_p* devicePath, void* sourcebuffer, uintptr_t sourceSize, efi_handle_t imageHandle);
    typedef efi_status_t (efi_locate_device_path_f)(guid_t* protocol, efi_device_path_p** devicePath, efi_handle_t* device);
    typedef efi_status_t (efi_locate_handle_f)(efi_locate_search_type_t searchType, guid_t* protocol, void* searchKey, uintptr_t* bufferSize, efi_handle_t* buffer);
    typedef efi_status_t (efi_locate_protocol_f)(guid_t* protocol, void* registration, void** interface);
    typedef efi_status_t (efi_open_protocol_f)(efi_handle_t handle, guid_t* protocol, void** interface, efi_handle_t agentHandle, efi_handle_t controllerHandle, uint32_t attributes);
    typedef efi_status_t (efi_open_protocol_information_f)(efi_handle_t handle, guid_t* protocol, efi_open_protocol_information_entry_t** entryBuffer, uintptr_t* entryCount);
    typedef efi_tpl_t (efi_raise_tpl_f)(efi_tpl_t newTpl);
    typedef void (efi_restore_tpl_f)(efi_tpl_t oldTpl);
    typedef efi_status_t (efi_reinstall_protocol_interface_f)(efi_handle_t handle, guid_t* protocol, void* oldInterface, void* newInterface);
    typedef efi_status_t (efi_register_protocol_notify_f)(guid_t* protocol, efi_event_t event, void** registration);
    typedef void (efi_set_mem_f)(void* buffer, uintptr_t size, uint8_t value);
    // set_event
    typedef efi_status_t (efi_set_timer_f)(efi_event_t event, efi_timer_delay_t type, uint64_t triggerTime);
    typedef efi_status_t (efi_set_watchdog_timer_f)(uintptr_t timeout, uint64_t watchdogCode, uintptr_t dataSize, char16_t* watchdogData);
    typedef efi_status_t (efi_signal_event_f)(efi_event_t event);
    typedef efi_status_t (efi_stall_f)(uintptr_t microseconds);
    typedef efi_status_t (efi_start_image_f)(efi_handle_t imageHandle, uintptr_t* exitDataSize, char16_t** exitData);
    typedef efi_status_t (efi_uninstall_protocol_interface_f)(efi_handle_t handle, guid_t* protocol, void* interface);
    typedef efi_status_t (efi_wait_for_event_f)(uintptr_t numberOfEvents, efi_event_t* event, uintptr_t* index);
    
    typedef efi_status_t (efi_check_event_f)(efi_event_t event);
    typedef efi_status_t (efi_unload_image_f)(efi_handle_t imageHandle);
    //typedef EFI_STATUS(EFIAPI * EFI_CONNECT_CONTROLLER)(IN EFI_HANDLE ControllerHandle, IN EFI_HANDLE *DriverImageHandle, OPTIONAL IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, OPTIONAL IN BOOLEAN Recursive)
    typedef efi_status_t (efi_connect_controller_f)(efi_handle_t ControllerHandle, efi_handle_t* driverImageHandle, efi_device_path_p* remainingDevicePath, bool_t recursive);
    //typedef EFI_STATUS(EFIAPI * EFI_DISCONNECT_CONTROLLER)(IN EFI_HANDLE ControllerHandle, IN EFI_HANDLE DriverImageHandle, OPTIONAL IN EFI_HANDLE ChildHandle OPTIONAL)
    typedef efi_status_t (efi_disconnect_controller_f)(efi_handle_t ControllerHandle, efi_handle_t driverImageHandle, efi_handle_t ChildHandle);
    //typedef EFI_STATUS(EFIAPI * EFI_PROTOCOLS_PER_HANDLE)(IN EFI_HANDLE Handle, OUT EFI_GUID ***ProtocolBuffer, OUT UINTN *ProtocolBufferCount)
    typedef efi_status_t (efi_protocols_per_handle_f)(efi_handle_t handle, guid_t*** protocolBuffer, uintptr_t* protocolBufferCount);
    //typedef EFI_STATUS(EFIAPI * EFI_LOCATE_HANDLE_BUFFER)(IN EFI_LOCATE_SEARCH_TYPE SearchType, IN EFI_GUID *Protocol, OPTIONAL IN VOID *SearchKey, OPTIONAL IN OUT UINTN *NoHandles, OUT EFI_HANDLE **Buffer)
    typedef efi_status_t (efi_locate_handle_buffer_f)(efi_locate_search_type_t searchType, guid_t* protocol, void* searchKey, uintptr_t* noHandles, efi_handle_t** buffer);
    typedef efi_status_t (efi_install_multiple_protocol_interfaces_f)(efi_handle_t* handle, ...);
    typedef efi_status_t (efi_uninstall_multiple_protocol_interfaces_f)(efi_handle_t* handle, ...);
    
}

struct efi_boot_services_t {
            efi_table_header_t                  Hdr;
            
    efiapi  efi_raise_tpl_f*                    RaiseTPL;
    efiapi  efi_restore_tpl_f*                  RestoreTPL;
    efiapi  efi_allocate_pages_f*               AllocatePages;
    efiapi  efi_free_pages_f*                   FreePages;
    efiapi  efi_get_memory_map_f*               GetMemoryMap;
    efiapi  efi_allocate_pool_f*                AllocatePool;
    efiapi  efi_free_pool_t*                    FreePool;
    efiapi  efi_create_event_f*                 CreateEvent;
    efiapi  efi_set_timer_f*                    SetTimer;
    efiapi  efi_wait_for_event_f*               WaitForEvent;
    efiapi  efi_signal_event_f*                 SignalEvent;
    efiapi  efi_close_event_f*                  CloseEvent;
    efiapi  efi_check_event_f*                  CheckEvent; //?
    efiapi  efi_install_protocol_interface_f*   InstallProtocolInterface;
    efiapi  efi_reinstall_protocol_interface_f* ReinstallProtocolInterface;
    efiapi  efi_uninstall_protocol_interface_f* UninstallProtocolInterface;
    efiapi  efi_handle_protocol_f*              HandleProtocol;
            void*                               _reserved;
    efiapi  efi_register_protocol_notify_f*     RegisterProtocolNotify;
    efiapi  efi_locate_handle_f*                LocateHandle;
    efiapi  efi_locate_device_path_f*           LocateDevicePath;
    efiapi  efi_install_configuration_table_f*  InstallConfigurationTable;
    efiapi  efi_load_image_f*                   LoadImage;
    efiapi  efi_start_image_f*                  StartImage;
    efiapi  efi_exit_f*                         Exit;
    efiapi  efi_unload_image_f*                 UnloadImage; //?
    efiapi  efi_exit_boot_services_f*           ExitBootServices;
    efiapi  efi_get_next_monotonic_count_f*     GetNextMonotonicCount;
    efiapi  efi_stall_f*                        Stall;
    efiapi  efi_set_watchdog_timer_f*           SetWatchdogTimer;
    efiapi  efi_connect_controller_f*           ConnectController; //?
    efiapi  efi_disconnect_controller_f*        DisconnectController; //?
    efiapi  efi_open_protocol_f*                OpenProtocol;
    efiapi  efi_close_protocol_f*               CloseProtocol;
    efiapi  efi_open_protocol_information_f*    OpenProtocolInformation;
    efiapi  efi_protocols_per_handle_f*         ProtocolsPerHandle; //?
    efiapi  efi_locate_handle_buffer_f*         LocateHandleBuffer; //?
    efiapi  efi_locate_protocol_f*              LocateProtocol;
    efiapi  efi_install_multiple_protocol_interfaces_f* InstallMultipleProtocolInterfaces; //?
    efiapi  efi_uninstall_multiple_protocol_interfaces_f* UninstallMultipleProtocolInterfaces; //?
    efiapi  efi_calculate_crc32_f*              CalculateCrc32;
    efiapi  efi_copy_mem_f*                     CopyMem;
    efiapi  efi_set_mem_f*                      SetMem;
    efiapi  efi_create_event_ex_f*              CreateEventEx;
    
};

// Configuration Tables

struct efi_configuration_t {
    guid_t                          VendorGuid;
    void*                           VendorTable;
};

// System Tables

#include "uefi/protocol/simple_text_input.h"
#include "uefi/protocol/simple_text_output.h"

struct efi_system_table_t {
    efi_table_header_t              Hdr;
    char16_t*                       FirmwareVendor;
    uint32_t                        FirmwareRevision;
    
    efi_handle_t                    ConsoleInHandle;
    efi_simple_text_input_p*        ConIn;
    efi_handle_t                    ConsoleOutHandle;
    efi_simple_text_output_p*       ConOut;
    efi_handle_t                    StandardErrorHandle;
    efi_simple_text_output_p*       StdErr;
    
    efi_runtime_services_t*         RuntimeServices;
    efi_boot_services_t*            BootServices;
    
    uintptr_t                       NumberOfTableEntries;
    efi_configuration_t*            ConfigurationTable;
};

