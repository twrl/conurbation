#pragma once

#include "numeric_types.hh"
#include "guid.h"
#include "conurbation/status.hh"

namespace Conurbation {

    enum class service_type_t { unknown, service_locator, logging, rng };

    class service_p {
    public:
        virtual auto service_type() -> guid_t const = 0;
    };

    template <typename T> constexpr guid_t service_type_v = "00000000-0000-0000-0000000000000000"_guid;

    class service_locator_p;
    template <> constexpr guid_t service_type_v<service_locator_p> = "87125296-7798-4856-8a88-3b966c5e6642"_guid;

    class service_locator_p : public service_p {
    protected:
        static service_locator_p* default_;

    public:
        static inline auto default_locator() -> service_locator_p & { return *default_; }

        inline virtual auto service_type() -> guid_t const final { return service_type_v<service_locator_p>; };
        virtual auto get(guid_t type) -> _<service_p*> = 0;

        template <typename T> inline auto get() -> _<T*>
        {
            return static_cast<T*>(static_cast<service_p*>(get(service_type_v<T>)));
        };

        virtual auto set(service_p& service) -> service_locator_p& = 0;
    };

    class service_locator_t : public service_locator_p {
        struct svcs_t {
            svcs_t* next;
            guid_t type;
            service_p* service;
        };

    private:
        svcs_t* services_;

    public:
        service_locator_t()
        {
            services_ = new svcs_t{ nullptr, service_type_v<service_locator_p>, this };
            service_locator_p::default_ = this;
        }

        virtual auto get(guid_t type) -> _<service_p*>;

        virtual auto set(service_p& service) -> service_locator_t&;
    };
}
