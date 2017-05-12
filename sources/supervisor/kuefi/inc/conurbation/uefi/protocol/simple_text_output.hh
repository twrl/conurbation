#pragma once

#include "conurbation/uefi/efi_types.hh"
#include "conurbation/uefi/abi.hh"

namespace Conurbation::UEFI
{

    struct efi_simple_text_output_p;

    typedef status_t(efiabi efi_text_reset_f)(efi_simple_text_output_p * _this, bool_t extendedVerification);
    typedef status_t(efiabi efi_text_string_f)(efi_simple_text_output_p * _this, const char16_t* string);
    typedef status_t(efiabi efi_text_test_string_f)(efi_simple_text_output_p * _this, const char16_t* string);
    typedef status_t(efiabi efi_text_query_mode_f)(
        efi_simple_text_output_p * _this, uintptr_t modeNumber, uintptr_t * columns, uintptr_t * rows);
    typedef status_t(efiabi efi_text_set_mode_f)(efi_simple_text_output_p * _this, uintptr_t modeNumber);
    typedef status_t(efiabi efi_text_set_attribute_f)(efi_simple_text_output_p * _this, uintptr_t attribute);
    typedef status_t(efiabi efi_text_clear_screen_f)(efi_simple_text_output_p * _this);
    typedef status_t(efiabi efi_text_set_cursor_position_f)(
        efi_simple_text_output_p * _this, uintptr_t column, uintptr_t row);
    typedef status_t(efiabi efi_text_enable_cursor_f)(efi_simple_text_output_p * _this, bool_t * enabled);

    struct efi_simple_text_output_mode_t {
        uint32_t MaxMode;
        uint32_t Mode;
        uint32_t Attribute;
        uint32_t CursorColumn;
        uint32_t CursorRow;
        bool_t CursorVisible;
    };

    struct efi_simple_text_output_p {
        efi_text_reset_f* Reset;
        efi_text_string_f* OutputString;
        efi_text_test_string_f* TestString;
        efi_text_query_mode_f* QueryMode;
        efi_text_set_mode_f* SetMode;
        efi_text_set_attribute_f* SetAttribute;
        efi_text_clear_screen_f* ClearScreen;
        efi_text_set_cursor_position_f* SetCursorPosition;
        efi_text_enable_cursor_f* EnableCursor;
        efi_simple_text_output_mode_t* Mode;
    };

    
}
