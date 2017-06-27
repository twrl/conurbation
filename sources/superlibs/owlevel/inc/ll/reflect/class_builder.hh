#pragma once

namespace ll::Reflect {

    template <typename T>
    class class_builder_t {

    public:

        template <typename... TParams>
        auto constructor() -> class_builder_t&;

        template <typename TBase>
        auto inherits() -> class_builder_t&;

        template <typename TProperty>
        auto property(cstring8_t name, TProperty (T::*getter)()) -> class_builder_t&;

        template <typename TProperty>
        auto property(cstring8_t name, T& (T::*setter)(TProperty)) -> class_builder_t&;

        template <typename TProperty>
        auto property(cstring8_t name, TProperty (T::*getter)(), T& (T::*setter)(TProperty)) -> class_builder_t&;

        template <typename TReturn, typename... TParams>
        auto method(cstring8_t name, TReturn (T::*meth)(TParams...)) -> class_builder_t&;

        template <typename TReturn, typename... TParams>
        auto static_method(cstring8_t name, TReturn (*method)(TParams...)) -> class_builder_t&;

        template <typename TValue>
        auto tag(cstring8_t name, const TValue value) -> class_builder_t&;

    };

}
