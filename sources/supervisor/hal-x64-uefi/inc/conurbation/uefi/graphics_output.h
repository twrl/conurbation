#pragma once

#include "conurbation/uefi/abi.h"
#include "conurbation/uefi/efi_types.h"
#include "guid.h"

namespace Conurbation::UEFI
{

    struct efi_graphics_output_p;

    enum efi_graphics_pixel_format_t {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    };

    struct efi_pixel_bitmask_t {
        uint32_t RedMask;
        uint32_t GreenMask;
        uint32_t BlueMask;
        uint32_t ReservedMask;
    };

    struct efi_graphics_output_mode_information_t {
        uint32_t Version;
        uint32_t HorizontalResolution;
        uint32_t VerticalResolution;
        efi_graphics_pixel_format_t PixelFormat;
        efi_pixel_bitmask_t PixelInformation;
        uint32_t PixelsPerScanLine;
    };

    struct efi_graphics_output_blt_pixel_t {
        uint8_t Blue;
        uint8_t Green;
        uint8_t Red;
        uint8_t Reserved;
    };

    enum efi_graphics_output_blt_operation_t {
        EfiBltVideoFill,
        EfiBltVideoToBltBuffer,
        EfiBltBufferToVideo,
        EfiBltVideoToVideo,
        EfiGraphicsOutputBltOperationMax
    };

    struct efi_graphics_output_protocol_mode_t {
        uint32_t MaxMode;
        uint32_t Mode;
        efi_graphics_output_mode_information_t* Info;
        uintptr_t SizeOfInfo;
        uintptr_t FramebufferBase;
        uintptr_t FramebufferSize;
    };

    typedef status_t(efiabi efi_graphics_output_protocol_query_mode_f)(efi_graphics_output_p * self,
        uint32_t modeNumber, uintptr_t * sizeOfInfo, efi_graphics_output_mode_information_t * *info);
    typedef status_t(efiabi efi_graphics_output_protocol_set_mode_f)(efi_graphics_output_p * self, uint32_t modeNumber);
    typedef status_t(efiabi efi_graphics_output_protocol_blt_f)(efi_graphics_output_p * self,
        efi_graphics_output_blt_pixel_t * bltBuffer, efi_graphics_output_blt_operation_t bltOperation,
        uintptr_t sourceX, uintptr_t sourceY, uintptr_t destinationX, uintptr_t destinationY, uintptr_t width,
        uintptr_t height, uintptr_t delta);

    struct efi_graphics_output_p {
        efi_graphics_output_protocol_query_mode_f* QueryMode;
        efi_graphics_output_protocol_set_mode_f* SetMode;
        efi_graphics_output_protocol_blt_f* Blt;
        efi_graphics_output_protocol_mode_t* Mode;
    };

    template <> constexpr guid_t protocol_guid_v<efi_graphics_output_p> = "9042a9de-23dc-4a38-96fb-7aded080516a"_guid;
}