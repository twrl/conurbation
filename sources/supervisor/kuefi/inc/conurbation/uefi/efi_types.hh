#pragma once

#include "conurbation/numeric_types.hh"
#include "conurbation/char_types.hh"
#include "conurbation/guid.hh"

namespace Conurbation::UEFI
{

    typedef void* handle_t;
    typedef void* event_t;

    typedef uintptr_t tpl_t;

    typedef uintptr_t physaddr_t;
    typedef uintptr_t virtaddr_t;

    enum class variable_attributes_t : uint32_t {
        nonVolatile = 0x00000001,
        bootServiceAccess = 0x00000002,
        runtimeAccess = 0x00000004,
        hardwareErrorRecord = 0x00000008,
        authenticatedWriteAccess = 0x00000010

    };

    enum struct status_t : int32_t { // intptr_t {
        Success = 0,
        LoadError = 1,
        InvalidParameter = 2,
        Unsupported = 3,
        BadBufferSize = 4,
        BufferTooSmall = 5,
        NotReady = 6,
        DeviceError = 7,
        WriteProtected = 8,
        OutOfResources = 9,
        VolumeCorrupted = 10,
        VolumeFull = 11,
        NoMedia = 12,
        MediaChanged = 13,
        NotFound = 14,
        AccessDenied = 15,
        NoResponse = 16,
        NoMapping = 17,
        Timeout = 18,
        NotStarted = 19,
        AlreadyStarted = 20,
        Aborted = 21,
        ICMPError = 22,
        TFTPError = 23,
        ProtocolError = 24,
        IncompatibleVersion = 25,
        SecurityViolation = 26,
        CRCError = 27,
        EndOfMedia = 28,
        EndOfFile = 31,

        WarnUnknownGlyph = 1,
        WarnDeleteFailure = 2,
        WarnWriteFailure = 3,

    };

    __attribute__((pure)) const char16_t * efiStatusToString(status_t status);

    enum class memory_type_t : uint32_t {
        EfiReservedMemoryType,
        EfiLoaderCode,
        EfiLoaderData,
        EfiBootServicesCode,
        EfiBootServicesData,
        EfiRuntimeServicesCode,
        EfiRuntimeServicesData,
        EfiConventionalMemory,
        EfiUnusableMemory,
        EfiACPIReclaimMemory,
        EfiACPIMemoryNVS,
        EfiMemoryMappedIO,
        EfiMemoryMappedIOPortSpace,
        EfiPalCode,
        EfiMaxMemoryType,

        OsCode = 0x80000000,
        OsData
    };

    __attribute__((pure)) const char16_t * efiMemoryTypeToString(memory_type_t type);

    struct memory_descriptor_t {
        memory_type_t Type;
        uint64_t PhysicalStart;
        uint64_t VirtualStart;
        uint64_t NumberOfPages;
        uint64_t Attribute;
    };

    struct time_t {
        uint16_t Year;
        uint8_t Month;
        uint8_t Day;
        uint8_t Hour;
        uint8_t Minute;
        uint8_t Second;
        uint8_t Pad1;
        uint32_t Nanosecond;
        int16_t Timezone;
        uint8_t Daylight;
        uint8_t Pad2;
    };

    struct time_capabilities_t {
        uint32_t Resolution;
        uint32_t Accuracy;
        bool_t SetsToZero;
    };

    enum reset_type_t { EfiResetCold, EfiResetWarm, EfiResetShutdown };

    struct capsule_header_t {
        guid_t CapsuleGuid;
        uint32_t HeaderSize;
        uint32_t Flags;
        uint32_t CapsuleImageSize;
    };

    enum class allocate_type_t { AllocateAnyPages, AllocateMaxAddress, AllocateAddress, MaxAllocateType };

    typedef void(event_notify_f)(event_t event, void* context);

    enum interface_type_t { EFI_NATIVE_INTERFACE };

    enum locate_search_type_t { AllHandles, ByRegisterNotify, ByProtocol };

    struct open_protocol_information_entry_t {
        handle_t AgentHandle;
        handle_t ControllerHandle;
        uint32_t Attributes;
        uint32_t OpenCount;
    };

    struct input_key_t {
        uint16_t ScanCode;
        char16_t UnicodeChar;
    };

    enum timer_delay_t { TimerCancel, TimerPeriodic, TimerRelative };
}
