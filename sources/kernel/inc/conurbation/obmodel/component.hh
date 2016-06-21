#pragma once

#include "guid.h"
#include "conurbation/obmodel/service.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

namespace Conurbation::ObModel
{

    class entity_t;
    class component_t;

    class entity_t {
    private:
        component_t* components_;
        uintptr_t entity_id_;

    public:
        inline auto entity_id() -> uintptr_t const { return entity_id_; }
    };

    class component_t {
        friend class entity_t;

    private:
        component_t* next_in_entity_;
        uintptr_t component_id_;
        entity_t* entity_;

    public:
        inline auto virtual component_id() -> uintptr_t const final { return component_id_; }
        auto virtual component_type() -> guid_t const = 0;
        inline auto virtual entity() -> entity_t& final { return *entity_; }
        inline auto virtual entity_id() -> uintptr_t const final { return entity_->entity_id(); }
    };
}
