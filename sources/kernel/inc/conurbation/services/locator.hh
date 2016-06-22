#pragma once

namespace Conurbation::Services
{

    class logging_service_p;
    class firmware_service_p;
    class clock_service_p;
    class diagnostic_console_service_p;
    class page_allocator_p;

    // Service locator is trivially simple at the moment - add logic later
    class locator_p {
    public:
        // Singleton getter
        static auto get_locator() -> locator_p&;

        virtual auto logging() -> logging_service_p& = 0;
        virtual auto logging(logging_service_p&) -> locator_p& = 0;

        virtual auto firmware() -> firmware_service_p& = 0;
        virtual auto firmware(firmware_service_p&) -> locator_p& = 0;

        virtual auto clock() -> clock_service_p& = 0;
        virtual auto clock(clock_service_p&) -> locator_p& = 0;

        virtual auto diagnostic_console() -> diagnostic_console_service_p& = 0;
        virtual auto diagnostic_console(diagnostic_console_service_p&) -> locator_p& = 0;

        virtual auto page_allocator() -> page_allocator_p& = 0;
        virtual auto page_allocator(page_allocator_p&) -> locator_p& = 0;
    };
}
