#pragma once

#include "guid.h"

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
        guid_t entity_id_;

    public:
        inline auto entity_id() -> guid_t const { return entity_id_; }
    };

    class component_t {
        friend class entity_t;

    private:
        component_t* next_in_entity_;
        guid_t component_id_;
        entity_t* entity_;

    public:
        inline auto virtual component_id() -> guid_t const final { return component_id_; }
        inline auto virtual component_type() -> guid_t const = 0;
        inline auto virtual entity() -> entity_t& final { return *entity_; }
    };
}
