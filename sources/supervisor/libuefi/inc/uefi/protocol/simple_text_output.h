#pragma once

#include "uefi/efitypes.h"

struct efi_simple_text_output_p;

extern "C" {
    typedef efi_status_t (efi_text_reset_f)(efi_simple_text_output_p* _this, bool_t extendedVerification);
    typedef efi_status_t (efi_text_string_f)(efi_simple_text_output_p* _this, char16_t* string);
    typedef efi_status_t (efi_text_test_string_f)(efi_simple_text_output_p* _this, char16_t* string);
    typedef efi_status_t (efi_text_query_mode_f)(efi_simple_text_output_p* _this, uintptr_t modeNumber, uintptr_t* columns, uintptr_t* rows);
    typedef efi_status_t (efi_text_set_mode_f)(efi_simple_text_output_p* _this, uintptr_t modeNumber);
    typedef efi_status_t (efi_text_set_attribute_f)(efi_simple_text_output_p* _this, uintptr_t attribute);
    typedef efi_status_t (efi_text_clear_screen_f)(efi_simple_text_output_p* _this);
    typedef efi_status_t (efi_text_set_cursor_position_f)(efi_simple_text_output_p* _this, uintptr_t column, uintptr_t row);
    typedef efi_status_t (efi_text_enable_cursor_f)(efi_simple_text_output_p* _this, bool_t* enabled);
}

struct efi_simple_text_output_mode_t {
    uint32_t                        MaxMode;
    uint32_t                        Mode;
    uint32_t                        Attribute;
    uint32_t                        CursorColumn;
    uint32_t                        CursorRow;
    bool_t                          CursorVisible;
};

struct efi_simple_text_output_p {
    efiapi  efi_text_reset_f*               Reset;
    efiapi  efi_text_string_f*              OutputString;
    efiapi  efi_text_test_string_f*         TestString;
    efiapi  efi_text_query_mode_f*          QueryMode;
    efiapi  efi_text_set_mode_f*            SetMode;
    efiapi  efi_text_set_attribute_f*       SetAttribute;
    efiapi  efi_text_clear_screen_f*        ClearScreen;
    efiapi  efi_text_set_cursor_position_f* SetCursorPosition;
    efiapi  efi_text_enable_cursor_f*       EnableCursor;
            efi_simple_text_output_mode_t*  Mode;
};
