#pragma once

#include "stringbuilder.hh"
#include "numeric_types.hh"
#include "conurbation/ecs/typeid.hh"

namespace Conurbation::ECS
{

    class entity_t;

    class component_t {
        friend class entity_t;

    private:
        entity_t* entity_;
        component_t* next_in_entity_;
        component_t* next_in_class_;
        typeid_t typeid_;

    public:
        virtual ~component_t();
    };
}
