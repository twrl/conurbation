#pragma once

#include "conurbation/mem/pagealloc.hh"

namespace Conurbation::ObModel
{

    class service_locator_t {

    private:
        static Mem::page_alloc_service_p* page_alloc_service_;

    public:
        static inline auto page_alloc_service() -> Mem::page_alloc_service_p * { return page_alloc_service_; }
        static inline auto page_alloc_service(Mem::page_alloc_service_p* svc) -> void { page_alloc_service_ = svc; }
    };
}
