#pragma once

#include "types.h"

#define efiapi [[gnu::ms_abi]]
//define efiapi __attribute__((ms_abi))

typedef void*       efi_handle_t;
typedef void*       efi_event_t;

enum class efi_status_t: intptr_t {
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
    
    static inline char16_t* toString(efi_status_t status) {
        switch (status) {
            case Success:
                return L"Success";
            case LoadError:
                return L"Load Error";
            case InvalidParameter:
                return L"Invalid Parameter";
            case Unsupported:
                return L"Unsupported";
            case BadBufferSize:
                return L"Bad Buffer Size";
            case BufferTooSmall:
                return L"Buffer Too Small";
            case NotReady:
                return L"Not Ready";
                
            default:
                return L"Unknown Error";
        }
    }
    
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
