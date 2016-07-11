#pragma once

#include "time.hh"

namespace Conurbation::Services
{

    // In principle, this is a generic interface to platform firmware. In practice, it's a wrapper around EFI runtime services.
    class firmware_service_p {
    public:
        virtual auto current_time() -> datetime_t = 0;
        virtual auto current_time(datetime_t) -> firmware_service_p& = 0;
    };
}
