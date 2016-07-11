#include "conurbation/services/locator.hh"

namespace Conurbation::Services
{

    class static_locator_t : public locator_p {
    private:
        logging_service_p* logging_ = nullptr;
        firmware_service_p* firmware_ = nullptr;
        clock_service_p* clock_ = nullptr;
        diagnostic_console_service_p* diagnostic_console_ = nullptr;
        page_allocator_p* page_allocator_ = nullptr;

    public:
        virtual auto logging() -> logging_service_p& override { return *logging_; };
        virtual auto logging(logging_service_p& value) -> locator_p& override
        {
            logging_ = &value;
            return *this;
        }

        virtual auto firmware() -> firmware_service_p& override { return *firmware_; };
        virtual auto firmware(firmware_service_p& value) -> locator_p& override
        {
            firmware_ = &value;
            return *this;
        };

        virtual auto clock() -> clock_service_p& override { return *clock_; }
        virtual auto clock(clock_service_p& value) -> locator_p& override
        {
            clock_ = &value;
            return *this;
        }

        virtual auto diagnostic_console() -> diagnostic_console_service_p& override { return *diagnostic_console_; }
        virtual auto diagnostic_console(diagnostic_console_service_p& value) -> locator_p& override
        {
            diagnostic_console_ = &value;
            return *this;
        }

        virtual auto page_allocator() -> page_allocator_p& override { return *page_allocator_; }
        virtual auto page_allocator(page_allocator_p& value) -> locator_p& override
        {
            page_allocator_ = &value;
            return *this;
        }
    };

    namespace {
        locator_p* global_service_locator = nullptr;
    }

    auto locator_p::get_locator()->locator_p &
    {
        if (!global_service_locator)
            global_service_locator = new static_locator_t();
        return *global_service_locator;
    }
}
