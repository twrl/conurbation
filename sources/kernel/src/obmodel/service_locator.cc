#include "conurbation/obmodel/service.hh"

namespace Conurbation {

    service_locator_p* service_locator_p::default_ = nullptr;

    auto service_locator_t::get(guid_t type) -> _<service_p*>
    {
        svcs_t* current = services_;
        while (true) {
            if (current->type == type)
                return current->service;

            if (current->next)
                current = current->next;
            else
                return status_t::ServiceNotFound;
        }
    };

    auto service_locator_t::set(service_p& service) -> service_locator_t &
    {
        svcs_t* current = services_;
        while (true) {
            if (current->type == service.service_type()) {
                current->service = &service;
                return *this;
            }

            if (current->next)
                current = current->next;
            else {
                current->next = new svcs_t{ nullptr, service.service_type(), &service };
                return *this;
            }
        }
    };
}
