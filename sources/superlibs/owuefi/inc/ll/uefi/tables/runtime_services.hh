#pragma once

#include "ll/uefi/abi.hh"
#include "ll/uefi/protocols/device_path.hh"

namespace ll::UEFI::Tables {

    // Runtime services function types
    typedef status_t(efiabi get_next_variable_name_f)(
        uintptr_t * variableNameSize, char16_t* variableName, guid_t* vendorGuid);
    typedef status_t(efiabi get_variable_f)(
        char16_t* variableName, guid_t* vendorGuid, variable_attributes_t* attributes, uintptr_t* dataSize, void* data);
    typedef status_t(efiabi set_variable_f)(
        char16_t* variableName, guid_t* vendorGuid, variable_attributes_t attributes, uintptr_t dataSize, void* data);
    typedef status_t(efiabi set_virtual_address_map_f)(uintptr_t memoryMapSize, uintptr_t descriptorSize,
        uint32_t descriptorVersion, memory_descriptor_t * virtualMap);
    typedef status_t(efiabi get_time_f)(time_t * time, time_capabilities_t * timeCapabilities);
    typedef status_t(efiabi set_time_f)(time_t * time);
    typedef status_t(efiabi get_wakeup_time_f)(bool_t * enabled, bool_t * pending, time_t * time);
    typedef status_t(efiabi set_wakeup_time_f)(bool_t enable, time_t * time);
    typedef status_t(efiabi convert_pointer_f)(uintptr_t debugDisposition, void** address);
    typedef void(reset_system_f)(reset_type_t resetType, status_t resetStatus, uintptr_t dataSize, void* resetData);
    typedef status_t(efiabi get_next_high_mono_count_f)(uint32_t * highCount);
    typedef status_t(efiabi update_capsule_f)(
        capsule_header_t * *capsuleHeaderArray, uintptr_t capsuleCount, uint64_t scatterGatherList);
    typedef status_t(efiabi query_capsule_capabilities_f)(capsule_header_t * *capsuleHeaderArray,
        uintptr_t capsuleCount, uint64_t * maximumCapsuleSize, reset_type_t * resetType);
    typedef status_t(efiabi query_variable_info_f)(variable_attributes_t attributes,
        uint64_t * maximumVariableStorageSize, uint64_t * remainingVariableStorageSize, uint64_t * maximumVariableSize);

    struct runtime_services_t: table_header_t {

        get_time_f* GetTime;
        set_time_f* SetTime;
        get_wakeup_time_f* GetWakeupTime;
        set_wakeup_time_f* SetWakeupTime;
        set_virtual_address_map_f* SetVirtualAddressMap;
        convert_pointer_f* ConvertPointer;
        get_variable_f* GetVariable;
        get_next_variable_name_f* GetNextVariableName;
        set_variable_f* SetVariable;
        get_next_high_mono_count_f* GetNextHighMonotonicCount;
        reset_system_f* ResetSystem;
        update_capsule_f* UpdateCapsule;
        query_capsule_capabilities_f* QueryCapsuleCapabilities;
        query_variable_info_f* QueryVariableInfo;
    };

}
