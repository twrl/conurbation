#pragma once

#include "time.hh"

namespace Conurbation::Services
{

    class clock_service_p {
    public:
        virtual auto this_instant() const -> instant_t = 0;
    };
}
