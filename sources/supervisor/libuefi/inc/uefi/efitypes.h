#pragma once

#include "types.h"

//define efiapi [[gnu::ms_abi]]
#define efiapi __attribute__((ms_abi))

typedef void*       efi_handle_t;
typedef void*       efi_event_t;

typedef uintptr_t   efi_tpl_t;

enum efi_status_t: intptr_t {
    Success             = 0,
    LoadError           = 1,
    InvalidParameter    = 2,
    Unsupported         = 3,
    BadBufferSize       = 4,
    BufferTooSmall      = 5,
    NotReady            = 6,
    DeviceError         = 7,
    WriteProtected      = 8,
    OutOfResources      = 9,
    VolumeCorrupted     = 10,
    VolumeFull          = 11,
    NoMedia             = 12,
    MediaChanged        = 13,
    NotFound            = 14,
    AccessDenied        = 15,
    NoResponse          = 16,
    NoMapping           = 17,
    Timeout             = 18,
    NotStarted          = 19,
    AlreadyStarted      = 20,
    Aborted             = 21,
    ICMPError           = 22,
    TFTPError           = 23,
    ProtocolError       = 24,
    IncompatibleVersion = 25,
    SecurityViolation   = 26,
    CRCError            = 27,
    EndOfMedia          = 28,
    EndOfFile           = 31,
    
    WarnUnknownGlyph    = 1,
    WarnDeleteFailure   = 2,
    WarnWriteFailure    = 3,
    
};

static inline const char16_t* efiStatusToString(efi_status_t status) {
    switch (status) {
        case Success:
            return u"Success";
        case LoadError:
            return u"Load Error";
        case InvalidParameter:
            return u"Invalid Parameter";
        case Unsupported:
            return u"Unsupported";
        case BadBufferSize:
            return u"Bad Buffer Size";
        case BufferTooSmall:
            return u"Buffer Too Small";
        case NotReady:
            return u"Not Ready";
            
        default:
            return u"Unknown Error";
    }
}

struct efi_memory_descriptor_t {
    uint32_t            Type;
    paddr_t             PhysicalStart;
    vaddr_t             VirtualStart;
    uint64_t            NumberOfPages;
    uint64_t            Attribute;
};

struct efi_time_t {
    uint16_t            Year;
    uint8_t             Month;
    uint8_t             Day;
    uint8_t             Hour;
    uint8_t             Minute;
    uint8_t             Second;
    uint8_t             Pad1;
    uint32_t            Nanosecond;
    int16_t             Timezone;
    uint8_t             Daylight;
    uint8_t             Pad2;
};

struct efi_time_capabilities_t {
    uint32_t            Resolution;
    uint32_t            Accuracy;
    bool_t              SetsToZero;
};

enum efi_reset_type_t {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown
};

struct efi_capsule_header_t {
    guid_t              CapsuleGuid;
    uint32_t            HeaderSize;
    uint32_t            Flags;
    uint32_t            CapsuleImageSize;
};

enum efi_memory_type_t {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiVootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiMaxMemoryType
};

