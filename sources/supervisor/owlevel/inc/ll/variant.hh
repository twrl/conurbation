#pragma once

#include "ll/storage.hh"
#include "ll/templ.hh"
#include "ll/_traits_internal.hh"
#include "traits.hh"

namespace ll {

    template <class T, class... Types>
    struct variant_traits {
        typedef T type;
    };

    template <typename ...Types>
    class variant_t {
    private:

        static constexpr size_t data_size = max<_traits_internal::size_of_t, Types...>::value;
        static constexpr size_t data_align = max<_traits_internal::align_of_t, Types...>::value;

        using storage = aligned_storage_t<data_size, data_align>;
        using first_type = typename first<Types...>::type;

        storage data_;



    public:

        variant_t() {
            new (&data_) first_type();
        };

        template <class T, class Traits = variant_traits<T, Types...> >
        variant_t(T& value) {
            // Must be copy constructable
            new (&data_) typename Traits::type(value);
        };

        template <class T, class Traits = variant_traits<T, Types...>>
        variant_t(T&& value) {
            // Must be move constructable
            new (&data_) typename Traits::type(value);
        };

        template <class T>
        auto get_unsafe() -> T& {
            return *reinterpret_cast<T*>(&data_);
        }

    };

}
