#pragma once

#include "numeric_types.hh"
#include "ll/storage.hh"
#include "ll/memory.hh"
#include "ll/templ.hh"
#include "ll/_traits_internal.hh"
#include "traits.hh"
#include "ll/result.hh"

namespace ll {

    template <class T, class... Types>
    struct variant_traits {
        typedef T type;
    };

    template <class T, class THead, class... TTail>
    struct variant_type_idx {
        static constexpr size_t index = is_same_v<T, THead> ? sizeof...(TTail) : variant_type_idx<T, TTail...>::index;
    };

    template <class T>
    struct variant_type_idx <T, T> {
        static constexpr size_t index = 0;
    };

    template <class T, class U>
    struct variant_type_idx <T, U> {
        static constexpr size_t index = -1;
    };

    template <typename ...Types>
    class variant_t {
    private:

        static constexpr size_t data_size = max<_traits_internal::size_of_t, Types...>::value;
        static constexpr size_t data_align = max<_traits_internal::align_of_t, Types...>::value;

        using storage = aligned_storage_t<data_size, data_align>;
        using first_type = typename first<Types...>::type;

        storage data_;
        size_t index_;


    public:

        variant_t() {
            new (&data_) first_type();
            index_ = variant_type_idx<first_type, Types...>::index;
        };

        template <class T, class Traits = variant_traits<T, Types...> >
        variant_t(T& value) {
            // Must be copy constructable
            new (&data_) typename Traits::type(value);
            index_ = variant_type_idx<T, Types...>::index;
        };

        template <class T, class Traits = variant_traits<T, Types...>>
        variant_t(T&& value) {
            // Must be move constructable
            new (&data_) typename Traits::type(value);
            index_ = variant_type_idx<T, Types...>::index;
        };

        template <class T>
        auto get_unsafe() -> T& {
            return *reinterpret_cast<T*>(&data_);
        };

        template <class T>
        auto get() -> _<T&> {
            return (variant_type_idx<T, Types...>::inedx == index_) ? get_unsafe<T>() : status_t::type_mismatch;
        };

    };

    using any_intergal_t = variant_t<bool_t, uint8_t, int8_t, uint16_t, int16_t, uint32_t, int32_t, uint64_t, int64_t, char16_t, char32_t>;


}
