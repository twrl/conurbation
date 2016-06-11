#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"
#include "char_types.hh"
#include "variadic.hh"
#include "uefi/tables.h"
#include "conurbation/obmodel/service.hh"

namespace Conurbation {

    enum class log_level_t { panic, error, warn, info, trace, debug };

    class logging_p;
    template <> constexpr guid_t service_type_v<logging_p> = "7eb6332e-5fe5-497f-ab69-56161ccd1b56"_guid;

    class logging_p : public service_p {
    public:
        inline virtual auto service_type() -> guid_t const final { return service_type_v<logging_p>; };

        virtual auto begin_group(const char16_t* title) -> logging_p& = 0;
        virtual auto end_group() -> logging_p& = 0;
        virtual auto log(log_level_t level, const char16_t* source, const char16_t* message, va_list args) -> logging_p& = 0;
        virtual auto log(log_level_t level, const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;

        virtual auto debug(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
        virtual auto trace(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
        virtual auto info(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
        virtual auto warn(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
        virtual auto error(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
        virtual auto panic(const char16_t* source, const char16_t* message, ...) -> logging_p& = 0;
    };

    class logging_t : public logging_p {

    private:
        log_level_t current_log_level_ = log_level_t::info;
        UEFI::efi_simple_text_output_p* stop_;
        uint16_t group_lvl_ = 0;

    public:
        logging_t(UEFI::efi_system_table_t* st)
            : stop_(st->ConOut)
        {
        }

        virtual auto begin_group(const char16_t* title) -> logging_t&;
        virtual auto end_group() -> logging_t&;
        virtual auto log(log_level_t level, const char16_t* source, const char16_t* message, va_list args) -> logging_t&;

        virtual inline auto log(log_level_t level, const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(level, source, message, args);
            va_end(args);
            return *this;
        }

        virtual inline auto debug(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::debug, source, message, args);
            va_end(args);
            return *this;
        }
        virtual inline auto trace(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::trace, source, message, args);
            va_end(args);
            return *this;
        }
        virtual inline auto info(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::info, source, message, args);
            va_end(args);
            return *this;
        }
        virtual inline auto warn(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::warn, source, message, args);
            va_end(args);
            return *this;
        }
        virtual inline auto error(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::error, source, message, args);
            va_end(args);
            return *this;
        }
        virtual inline auto panic(const char16_t* source, const char16_t* message, ...) -> logging_t& final
        {
            va_list args;
            va_start(args, message);
            log(log_level_t::panic, source, message, args);
            va_end(args);
            return *this;
        }
    };
}
