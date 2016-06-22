#pragma once

#include "string.hh"
#include "stringbuilder.hh"
#include "time.hh"
#include "conurbation/services/locator.hh"

namespace Conurbation::Services
{

    namespace Logging {

        enum class log_severity_t { panic, error, warning, info, debug, trace };
    }

    class logging_service_p {
    public:
        virtual auto log(Logging::log_severity_t severity, const string_t& source, const string_t& message)
            -> logging_service_p& = 0;

        template <typename... T>
        inline auto log(Logging::log_severity_t severity, const string_t& message_fmt, T... args) -> logging_service_p &
        {
            return log(severity, u"", format(message_fmt, args...));
        }

        template <typename... T>
        inline auto log(Logging::log_severity_t severity, const string_t& source, const string_t& message_fmt,
            T... args) -> logging_service_p &
        {
            return log(severity, source, format(message_fmt, args...));
        }

        template <typename... T>
        inline auto debug(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::debug, source, format(message, args...));
        };
        template <typename... T>
        inline auto trace(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::trace, source, format(message, args...));
        }
        template <typename... T>
        inline auto info(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::info, source, format(message, args...));
        }
        template <typename... T>
        inline auto warn(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::warning, source, format(message, args...));
        }
        template <typename... T>
        inline auto error(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::error, source, format(message, args...));
        }
        template <typename... T>
        inline auto panic(const char16_t* source, const char16_t* message, T... args) -> logging_service_p &
        {
            return log(Logging::log_severity_t::panic, source, format(message, args...));
        }
    };
}
