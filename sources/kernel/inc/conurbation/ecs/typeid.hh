#pragma once

#include "numeric_types.hh"

namespace Conurbation::ECS
{

    using typeid_t = uintptr_t;

    class TypeId {
    public:
        template <typename T> static auto get_typeid() -> typeid_t
        {
            static const typeid_t _tid = next_typeid__++;
            return _tid;
        }

    private:
        static typeid_t next_typeid__;
    };
}
