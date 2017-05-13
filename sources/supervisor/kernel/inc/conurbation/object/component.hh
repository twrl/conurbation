#pragma once 

namespace Conurbation::Object {

    struct entity_t;
    struct component_t;
    struct system_t;

    struct component_t {
        entity_t* entity;
        system_t* system;
        component_t* nextInEntity;
        component_t* nextInSystem;

        virtual auto update() -> void = 0;

    };

    struct entity_t: component_t {
        guid_t entityId;
        entity_t* leftInSystem;
        size_t componentCount;


    };

}
