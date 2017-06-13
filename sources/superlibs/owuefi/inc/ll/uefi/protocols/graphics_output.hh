#pragma once

namespace ll::UEFI::Protocols {

    struct graphics_output_p;

    enum graphics_pixel_format_t {
        PixelRedGreenBlueReserved8BitPerColor,
        PixelBlueGreenRedReserved8BitPerColor,
        PixelBitMask,
        PixelBltOnly,
        PixelFormatMax
    };

    struct pixel_bitmask_t {
        uint32_t RedMask;
        uint32_t GreenMask;
        uint32_t BlueMask;
        uint32_t ReservedMask;
    };

    struct graphics_output_mode_information_t {
        uint32_t Version;
        uint32_t HorizontalResolution;
        uint32_t VerticalResolution;
        graphics_pixel_format_t PixelFormat;
        pixel_bitmask_t PixelInformation;
        uint32_t PixelsPerScanLine;
    };

    struct graphics_output_blt_pixel_t {
        uint8_t Blue;
        uint8_t Green;
        uint8_t Red;
        uint8_t Reserved;
    };

    enum graphics_output_blt_operation_t {
        EfiBltVideoFill,
        EfiBltVideoToBltBuffer,
        EfiBltBufferToVideo,
        EfiBltVideoToVideo,
        EfiGraphicsOutputBltOperationMax
    };

    struct graphics_output_protocol_mode_t {
        uint32_t MaxMode;
        uint32_t Mode;
        graphics_output_mode_information_t* Info;
        uintptr_t SizeOfInfo;
        uintptr_t FramebufferBase;
        uintptr_t FramebufferSize;
    };

    typedef status_t(efiabi graphics_output_protocol_query_mode_f)(graphics_output_p * self,
        uint32_t modeNumber, uintptr_t * sizeOfInfo, graphics_output_mode_information_t * *info);
    typedef status_t(efiabi graphics_output_protocol_set_mode_f)(graphics_output_p * self, uint32_t modeNumber);
    typedef status_t(efiabi graphics_output_protocol_blt_f)(graphics_output_p * self,
        graphics_output_blt_pixel_t * bltBuffer, graphics_output_blt_operation_t bltOperation,
        uintptr_t sourceX, uintptr_t sourceY, uintptr_t destinationX, uintptr_t destinationY, uintptr_t width,
        uintptr_t height, uintptr_t delta);

    struct graphics_output_p {
        graphics_output_protocol_query_mode_f* QueryMode;
        graphics_output_protocol_set_mode_f* SetMode;
        graphics_output_protocol_blt_f* Blt;
        graphics_output_protocol_mode_t* Mode;
    };

}
