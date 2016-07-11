#pragma once

#include "numeric_types.hh"
#include "stringbuilder.hh"
#include "conurbation/object_traits.hh"
#include "conurbation/ecs/component.hh"
#include "conurbation/ecs/typeid.hh"

namespace Conurbation::ECS

{

    class entity_t {

    public:
        virtual ~entity_t();

        template <typename T, typename... Args> auto addComponent(Args&&... args) -> T &
        {
            static_assert(is_base_of_v<component_t, T>, "Cannot add a non-component class to entity");
            auto _component = new T{ args... };
            addComponent(_component, TypeId::get_typeid<T>());
            return *_component;
        }

        template <typename T> auto removeComponent() -> void
        {
            static_assert(is_base_of_v<component_t, T>, "Cannot remove non-component class from entity");
            removeComponent(TypeId::get_typeid<T>());
        }

        template <typename T> auto getComponent() -> T &
        {
            static_assert(is_base_of_v<component_t, T>, "Cannot retrieve non-component class from entity");
            return static_cast<T&>(*getComponent(TypeId::get_typeid<T>()));
        }

        template <typename T> auto hasComponent() -> bool_t
        {
            static_assert(is_base_of_v<component_t, T>, "Cannot query non-component class in entity");
            return hasComponent(TypeId::get_typeid<T>());
        }

    protected:
        virtual auto addComponent(component_t* component, typeid_t tid) -> void;
        virtual auto removeComponent(typeid_t tid) -> void;
        virtual auto getComponent(typeid_t tid) -> component_t*;
        virtual auto hasComponent(typeid_t tid) -> bool_t;

    private:
        uintptr_t entity_id_;
        component_t* components_;
    };
}
