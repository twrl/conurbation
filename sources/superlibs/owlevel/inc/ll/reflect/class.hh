#pragma once

#include "ll/reflect/type.hh"

namespace ll::Reflect {

    class class_t : public type_t {

    public:

        template <typename T>
        static declare(cstring8_t) -> &class_builder_t<T>;

    };



}
