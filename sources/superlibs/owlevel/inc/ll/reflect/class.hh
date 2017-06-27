#pragma once

#include "ll/reflect/type.hh"
#include "ll/reflect/class_builder.hh"

namespace ll::Reflect {

    class class_t : public type_t {

    public:

        template <typename T>
        static auto declare(cstring8_t) -> class_builder_t<T>&;

    };



}
