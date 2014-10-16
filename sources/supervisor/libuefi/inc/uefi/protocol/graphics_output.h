#pragma once

#include "uefi/efitypes.h"

struct efi_graphics_output_p;

enum efi_graphics_pixel_format_t {
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
};

struct efi_pixel_bitmask_t {
    uint32_t            RedMask;
    uint32_t            GreenMask;
    uint32_t            BlueMask;
    uint32_t            ReservedMask;
};

struct efi_graphics_output_mode_information_t {
    uint32_t            Version;
    uint32_t            HorizontalResolution;
    uint32_t            VerticalResolution;
    efi_graphics_pixel_format_t PixelFormat;
    efi_pixel_bitmask_t PixelInformation;
    uint32_t            PixelsPerScanLine;
};

struct efi_graphics_output_blt_pixel_t {
    uint8_t             Blue;
    uint8_t             Green;
    uint8_t             Red;
    uint8_t             Reserved;
};

enum efi_graphics_output_blt_operation_t {
    EfiBltVideoFill,
    EfiBltVideoToBltBuffer,
    EfiBltBufferToVideo,
    EfiBltVideoToVideo,
    EfiGraphicsOutputBltOperationMax
};

struct efi_graphics_output_protocol_mode_t {
    uint32_t            MaxMode;
    uint32_t            Mode;
    efi_graphics_output_mode_information_t* Info;
    uintptr_t           SizeOfInfo;
    paddr_t             FramebufferBase;
    paddr_t             FramebufferSize;
};

extern "C" {
    typedef efi_status_t (efi_graphics_output_protocol_query_mode_f)(efi_graphics_output_p* this, uint32_t modeNumber, uintptr_t* sizeOfInfo, efi_graphics_output_mode_information_t** info);
    typedef efi_status_t (efi_graphics_output_protocol_set_mode_f)(efi_graphics_output_p* this, uint32_t modeNumber);
    typedef efi_status_t (efi_graphics_output_protocol_blt_f)(efi_graphics_output_p* this, efi_graphics_output_blt_pixel_t* bltBuffer, efi_graphics_output_blt_operation_t bltOperation, uintptr_t sourceX, uintptr_t sourceY, uintptr_t destinationX, uintptr_t destinationY, uintptr_t width, uintptr_t height, uintptr_t delta);
}

struct efi_graphics_output_p {
    efiapi  efi_graphics_output_protocol_query_mode_f*      QueryMode;
    efiapi  efi_graphics_output_protocol_set_mode_f*        SetMode;
    efiapi  efi_graphics_output_protocol_blt_f*             Blt;
            efi_graphics_output_protocol_mode_t*            Mode;
}