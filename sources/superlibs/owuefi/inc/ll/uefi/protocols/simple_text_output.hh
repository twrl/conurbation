#pragma once

#include "ll/uefi/abi.hh"

namespace ll::UEFI::Protocols {

    struct simple_text_output_p;

    typedef status_t(efiabi text_reset_f)(simple_text_output_p * _this, bool_t extendedVerification);
    typedef status_t(efiabi text_string_f)(simple_text_output_p * _this, const char16_t* string);
    typedef status_t(efiabi text_test_string_f)(simple_text_output_p * _this, const char16_t* string);
    typedef status_t(efiabi text_query_mode_f)(
        simple_text_output_p * _this, uintptr_t modeNumber, uintptr_t * columns, uintptr_t * rows);
    typedef status_t(efiabi text_set_mode_f)(simple_text_output_p * _this, uintptr_t modeNumber);
    typedef status_t(efiabi text_set_attribute_f)(simple_text_output_p * _this, uintptr_t attribute);
    typedef status_t(efiabi text_clear_screen_f)(simple_text_output_p * _this);
    typedef status_t(efiabi text_set_cursor_position_f)(
        simple_text_output_p * _this, uintptr_t column, uintptr_t row);
    typedef status_t(efiabi text_enable_cursor_f)(simple_text_output_p * _this, bool_t * enabled);

    struct simple_text_output_mode_t {
        uint32_t MaxMode;
        uint32_t Mode;
        uint32_t Attribute;
        uint32_t CursorColumn;
        uint32_t CursorRow;
        bool_t CursorVisible;
    };

    struct simple_text_output_p {
        text_reset_f* Reset;
        text_string_f* OutputString;
        text_test_string_f* TestString;
        text_query_mode_f* QueryMode;
        text_set_mode_f* SetMode;
        text_set_attribute_f* SetAttribute;
        text_clear_screen_f* ClearScreen;
        text_set_cursor_position_f* SetCursorPosition;
        text_enable_cursor_f* EnableCursor;
        simple_text_output_mode_t* Mode;
    };

}
