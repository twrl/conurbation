#pragma once

/// \file
/// Provides some primitives for temple metaprogramming
///

#include "numeric_types.hh"

namespace ll {

    ///
    /// Sums a predicate over some type parameter pack
    ///
    template <template<class> class Pred, class THead, class... TTail>
    struct sum {
        static constexpr auto value = Pred<THead>::value + sum<Pred, TTail...>::value;
    };

    template <template<class> class Pred, class TLast>
    struct sum<Pred, TLast> {
        static constexpr auto value = Pred<TLast>::value;
    };

    ///
    /// Finds the maximum value of a predicate over some type parameter pack
    template <template<class> class Pred, class THead, class... TTail>
    struct max {
        static constexpr auto value = Pred<THead>::value > max<Pred, TTail...>::value ? Pred<THead>::value : max<Pred, TTail...>::value;
    };

    template <template<class> class Pred, class TLast>
    struct max<Pred, TLast> {
        static constexpr auto value = Pred<TLast>::value;
    };

    ///
    /// Finds the minimum value of a preciate over some type parameter pack
    ///
    template <template<class> class Pred, class THead, class... TTail>
    struct min {
        static constexpr auto value = Pred<THead>::value < min<Pred, TTail...>::value ? Pred<THead>::value : min<Pred, TTail...>::value;
    };

    template <template<class> class Pred, class TLast>
    struct min<Pred, TLast> {
        static constexpr auto value = Pred<TLast>::value;
    };

}
