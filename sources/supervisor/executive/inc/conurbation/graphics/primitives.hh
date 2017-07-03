#pragma once

#include "vector_types.hh"
#include "ll/result.hh"

namespace Conurbation::Graphics {

    using colour_t = float32x4_t;
    using point_t = int64x2_t;
    class raster_surface_t;

    template <class T>
    class primitive_t {
    private:

    protected:
        colour_t colour_;
        primitive_t(){};
    public:
        virtual auto draw(raster_surface_t&) -> T& = 0;

        [[gnu::pure]]
        virtual auto at(float64_t) -> point_t = 0;

        [[gnu::pure]]
        inline virtual auto colour() -> colour_t const { return colour_; }

        virtual auto colour(colour_t col) -> T& = 0;
    };

    class line_t: public primitive_t<line_t> {
    private:
        float64x2_t start_, end_;
    public:
        virtual auto draw(raster_surface_t&) -> line_t& override;
        inline virtual auto colour(colour_t col) -> line_t& override { colour_ = col; return *this; }

        [[gnu::pure]]
        virtual auto at(float64_t) -> point_t override;

        [[gnu::pure]]
        inline auto start() -> point_t const { return vector_cast<point_t>(start_); }
        auto start(point_t value) -> line_t& { start_ = vector_cast<float64x2_t>(value); return *this; }

        [[gnu::pure]]
        auto end() -> point_t const { return vector_cast<point_t>(end_); }
        auto end(point_t value) -> line_t& { end_ = vector_cast<float64x2_t>(value); return *this; }

        [[gnu::pure]]
        inline auto midpoint() -> point_t const { return at(0.5); }

        [[gnu::pure]]
        auto gradient() -> float64_t const;
    };

    class quad_bezier_t: public primitive_t<quad_bezier_t> {
    private:
        float64x2_t start_, control1_, end_;
    public:
        virtual auto draw(raster_surface_t&) -> quad_bezier_t& override;

        inline virtual auto colour(colour_t col) -> quad_bezier_t& override { colour_ = col; return *this; }

        [[gnu::pure]]
        virtual auto at(float64_t) -> point_t override;

        auto start() -> point_t const;
        auto start(point_t) -> quad_bezier_t&;

        auto control1() -> point_t const;
        auto control1(point_t) -> quad_bezier_t&;

        auto end() -> point_t const;
        auto end(point_t) -> quad_bezier_t&;

        auto secant() -> line_t&;
    };

    class cubic_bezier_t: public primitive_t<cubic_bezier_t> {
    private:
        float64x2_t start_, control1_, control2_, end_;
    public:
        virtual auto draw(raster_surface_t&) -> cubic_bezier_t& override;

        inline virtual auto colour(colour_t col) -> cubic_bezier_t& override { colour_ = col; return *this; }

        [[gnu::pure]]
        virtual auto at(float64_t) -> point_t override;

        auto start() -> point_t const;
        auto start(point_t) -> cubic_bezier_t&;

        auto control1() -> point_t const;
        auto control1(point_t) -> cubic_bezier_t&;

        auto control2() -> point_t const;
        auto control2(point_t) -> cubic_bezier_t&;

        auto end() -> point_t const;
        auto end(point_t) -> cubic_bezier_t&;

        auto secant() -> line_t&;
    };



}
