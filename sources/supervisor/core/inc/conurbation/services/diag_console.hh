#pragma once

#include "conurbation/services/locator.hh"
#include "numeric_types.hh"
#include "string.hh"
#include "stringbuilder.hh"

namespace Conurbation::Services
{

    namespace Console {
        enum class ega_colours_t : uint8_t {
            black = 0,
            blue,
            green,
            cyan,
            red,
            magenta,
            brown,
            lightgrey,
            darkgrey,
            lightblue,
            lightgreen,
            lightcyan,
            lightred,
            lightmagenta,
            yellow,
            white
        };
    };

    // Diagnostic console is a primitive (VGA-style) text console
    class diagnostic_console_service_p {
    public:
        virtual ~diagnostic_console_service_p() = default;

        virtual auto clear_screen() -> diagnostic_console_service_p& = 0;

        virtual auto background_colour() -> Console::ega_colours_t = 0;
        virtual auto background_colour(Console::ega_colours_t) -> diagnostic_console_service_p& = 0;

        virtual auto foreground_colour() -> Console::ega_colours_t = 0;
        virtual auto foreground_colour(Console::ega_colours_t) -> diagnostic_console_service_p& = 0;

        virtual auto width() -> uint16_t = 0;
        virtual auto height() -> uint16_t = 0;

        virtual auto write(const string_t&) -> diagnostic_console_service_p& = 0;
        virtual auto write_line() -> diagnostic_console_service_p& = 0;
        virtual auto write_line(const string_t&) -> diagnostic_console_service_p& = 0;

        template <typename... T> inline auto write(const string_t& fmt, T... args) -> diagnostic_console_service_p &
        {
            return write(format(fmt, args...));
        }

        template <typename... T>
        inline auto write_line(const string_t& fmt, T... args) -> diagnostic_console_service_p &
        {
            return write_line(format(fmt, args...));
        }
    };
}
