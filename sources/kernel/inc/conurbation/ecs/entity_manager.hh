#pragma once

#include "conurbation/services/locator.hh"

#include "conurbation/ecs/component.hh"
#include "conurbation/ecs/entity.hh"

namespace Conurbation::ECS
{

    class entity_manager_p {
    public:
        virtual ~entity_manager_p(){};

        virtual auto get_entity(uintptr_t entity_id) -> entity_t&;

        virtual auto create_entity() -> entity_t&;

        virtual auto remove_entity(uintptr_t entity_id) -> void;

        virtual auto has_entity(uintptr_t entity_id) -> void;
    };
}
