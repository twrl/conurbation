#pragma once

#include "numeric_types.hh"
#include "conurbation/status.hh"

namespace Conurbation {

    enum class service_type_t { unknown, service_locator, logging };

    class service_p {
    public:
        virtual auto service_type() -> service_type_t = 0;
    };

    template <typename T> constexpr service_type_t service_type_v = service_type_t::unknown;

    class service_locator_p;
    template <> constexpr service_type_t service_type_v<service_locator_p> = service_type_t::service_locator;

    class service_locator_p : public service_p {
    public:
        inline virtual auto service_type() -> service_type_t final { return service_type_v<service_locator_p>; };
        virtual auto get(service_type_t type) -> _<service_p*> = 0;

        template <typename T> inline auto get() -> _<T*>
        {
            return static_cast<T*>(static_cast<service_p*>(get(service_type_v<T>)));
        };

        virtual auto set(service_p& service) -> service_locator_p& = 0;
    };

    class service_locator_t : public service_locator_p {
        struct svcs_t {
            svcs_t* next;
            service_type_t type;
            service_p* service;
        };

    private:
        svcs_t* services_;

    public:
        service_locator_t() { services_ = new svcs_t{ nullptr, service_type_t::service_locator, this }; }

        virtual auto get(service_type_t type) -> _<service_p*>;

        virtual auto set(service_p& service) -> service_locator_t&;
    };
}
