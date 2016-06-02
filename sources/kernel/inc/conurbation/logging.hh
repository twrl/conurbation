#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"
#include "char_types.hh"
#include "variadic.hh"
#include "uefi/tables.h"

namespace Conurbation {

    enum class log_level_t { panic, error, warn, info, trace, debug };

    class logging_t {

    private:
        log_level_t current_log_level_ = log_level_t::info;
        UEFI::efi_simple_text_output_p* stop_;
        uint16_t group_lvl_ = 0;

    public:
        logging_t(UEFI::efi_system_table_t* st)
            : stop_(st->ConOut)
        {
        }

        auto begin_group(const char16_t* title) -> logging_t&;
        auto end_group() -> logging_t&;
        auto log(log_level_t level, const char16_t* source, const char16_t* message, va_list args) -> logging_t&;

        inline auto log(log_level_t level, const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(level, source, message, args);
            va_end(args);
            return *this;
        }

        inline auto debug(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::debug, source, message, args);
            va_end(args);
            return *this;
        }
        inline auto trace(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::trace, source, message, args);
            va_end(args);
            return *this;
        }
        inline auto info(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::info, source, message, args);
            va_end(args);
            return *this;
        }
        inline auto warn(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::warn, source, message, args);
            va_end(args);
            return *this;
        }
        inline auto error(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::error, source, message, args);
            va_end(args);
            return *this;
        }
        inline auto panic(const char16_t* source, const char16_t* message, ...) -> logging_t &
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::panic, source, message, args);
            va_end(args);
            return *this;
        }
    };
}
