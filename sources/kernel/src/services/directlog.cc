#include "conurbation/services/logging.hh"
#include "conurbation/services/diag_console.hh"

namespace Conurbation::Services::Logging
{

    class direct_log_service_t : public logging_service_p {
    public:
        virtual auto log(Logging::log_severity_t severity, const string_t& source, const string_t& message)
            -> logging_service_p& override
        {
            Console::ega_colours_t _c;
            switch (severity) {
                case log_severity_t::panic:
                    _c = Console::ega_colours_t::red;
                    break;
                case log_severity_t::error:
                    _c = Console::ega_colours_t::lightred;
                    break;
                case log_severity_t::warning:
                    _c = Console::ega_colours_t::yellow;
                    break;
                case log_severity_t::info:
                    _c = Console::ega_colours_t::white;
                    break;
                case log_severity_t::debug:
                    _c = Console::ega_colours_t::darkgrey;
                    break;
                case log_severity_t::trace:
                    _c = Console::ega_colours_t::lightgrey;
                    break;
            }

            locator_p::get_locator().diagnostic_console().foreground_colour(_c).write_line(
                u"[{}]\t{}", source, message);

            return *this;
        }
    };
}

namespace {

    [[gnu::constructor(20)]] auto direct_log_init() -> void
    {
        auto _log = new Conurbation::Services::Logging::direct_log_service_t();
        Conurbation::Services::locator_p::get_locator().logging(*_log);
    }
}
