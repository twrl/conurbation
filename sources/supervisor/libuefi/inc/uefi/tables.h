#pragma once

#include "uefi/efitypes.h"

enum class efi_variable_attributes_t: uint32_t {
    nonVolatile = 0x00000001,
    bootServiceAccess = 0x00000002,
    runtimeAccess = 0x00000004,
    hardwareErrorRecord = 0x00000008,
    authenticatedWriteAccess = 0x00000010
    
}

// Table Header

struct efi_table_header_t {
    uint64_t                        signature;
    uint32_t                        revision;
    uint32_t                        headerSize;
    uint32_t                        crc32;
    uint32_t                        reserved;
};

// Runtime Services

#undef efiapi
#define efiapi 

extern "C" {
    typedef efi_status_t (efiapi efi_get_next_variable_name_f)(uintptr_t* variableNameSize, char16_t* variableName, guid_t* vendorGuid);
    typedef efi_status_t (efiapi efi_get_variable_f)(char16_t* variableName, guid_t* vendorGuid, efi_variable_attributes_t* attributes, uintptr_t* dataSize, void* data);
    typedef efi_status_t (efiapi efi_set_variable_f)(char16_t* variableName, guid_t* vendorGuid, efi_variable_attributes_t attributes, uintptr_t dataSize, void* data);
    typedef efi_status_t (efiapi efi_set_virtual_address_map_f)(uintptr_t memoryMapSize, uintptr_t descriptorSize, uint32_t descriptorVersion, memory_descriptor_t* virtualMap);
    typedef efi_status_t (efiapi efi_get_time_f)(efi_time_t* time, efi_time_capabilities_t* timeCapabilities);
    typedef efi_status_t (efiapi efi_set_time_f)(efi_time_t* time);
    typedef efi_status_t (efiapi efi_get_wakeup_time_f)(bool_t* enabled, bool_t* pending, efi_time_t* time);
    typedef efi_status_t (efiapi efi_set_wakeup_time_f)(bool_t enable, efi_time_t* time);
    typedef efi_status_t (efiapi efi_convert_pointer_f)(uintptr_t debugDisposition, void** address);
    typedef void (efiapi efi_reset_system_f [[gnu::noreturn]])(efi_reset_type_t resetType, efi_status_t resetStatus, uintptr_t dataSize, void* resetData);
    typedef efi_status_t (efiapi efi_get_next_high_mono_count_f)(uint32_t* highCount);
    typedef efi_status_t (efiapi efi_update_capsule_f)(efi_capsule_header_t** capsuleHeaderArray, uintptr_t capsuleCount, paddr_t scatterGatherList);
    typedef efi_status_t (efiapi efi_query_capsule_capabilities_f)(efi_capsule_header_t** capsuleHeaderArray, uintptr_t capsuleCount, uint64_t* maximumCapsuleSize, efi_reset_type_t* resetType);
    typedef efi_status_t (efiapi efi_query_variable_info_f)(efi_variable_attributes_t attributes, uint64_t* maximumVariableStorageSize, uint64_t* remainingVariableStorageSize, uint64_t* maximumVariableSize);
};

#undef efiapi
#define efiapi __attribute__((ms_abi))

struct efi_runtime_services_t {
    efi_table_header_t              Hdr;
    
    efiapi efi_get_time_f*                 GetTime;
    efi_set_time_f*                 SetTime;
    efi_get_wakeup_time_f*          GetWakeupTime;
    efi_set_wakeup_time_f*          SetWakeupTime;
    efi_set_virtual_address_map_f*  SetVirtualAddressMap;
    efi_convert_pointer_f*          ConvertPointer;
    efi_get_variable_f*             GetVariable;
    efi_get_next_variable_name_f*   GetNextVariableName;
    efi_set_variable_f*             SetVariable;
    efi_get_next_high_mono_count_f* GetNextHighMonotonicCount;
    efi_reset_system_f*             ResetSystem;
    efi_update_capsule_f*           UpdateCapsule;
    efi_query_capsule_capabilities_f* QueryCapsuleCapabilities;
    efi_query_variable_info_f*      QueryVariableInfo;
};

// Boot Services

struct efi_boot_services_t {
    
    
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

