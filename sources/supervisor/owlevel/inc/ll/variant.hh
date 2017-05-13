#pragma once

#include "ll/storage.hh"
#include "ll/templ.hh"
#include "ll/_traits_internal.hh"
#include "traits.hh"

namespace ll {

    template <typename ...Types>
    class variant_t {
    private:

        static constexpr size_t data_size = max<_traits_internal::size_of_t, Types...>::value;
        static constexpr size_t data_align = max<_traits_internal::align_of_t, Types...>::value;

        using storage = aligned_storage_t<data_size, data_align>;

        storage data_;



    public:

        template <class T>
        variant_t() {
            // Must be default constructable
            new (&data_) T();
        };

        template <class T>
        variant_t(T& value) {
            // Must be copy constructable
            new (&data_) T(value);
        };

        template <class t>
        variant_t(T&& value) {
            // Must be move constructable
            new (&data_) T(value);
        };

    };

}
