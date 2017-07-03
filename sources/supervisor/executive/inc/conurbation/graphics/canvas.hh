#pragma once

#include "conurbation/graphics/primitives.hh"
#include "conurbation/graphics/raster_surface.hh"

namespace Conurbation::Graphics {

    class canvas_t {

    public:
        auto surface() -> raster_surface_t&;

        inline auto point(point_t point, colour_t colour) -> canvas_t& {
            surface().setPixel(point, colour);
            return *this;
        };

        inline auto line(point_t start, point_t end, colour_t colour) -> canvas_t& {
            line_t _line;
            _line.colour(colour).start(start).end(end).draw(surface());
            return *this;
        };


        auto quadBezier(point_t start, point_t control, point_t end, colour_t colour) -> canvas_t& {
            quad_bezier_t _bez;
            _bez.colour(colour).start(start).control1(control).end(end).draw(surface());
            return *this;
        };

        auto cubeBezier(point_t start, point_t control1, point_t control2, point_t end, colour_t colour) -> canvas_t {
            cubic_bezier_t _bez;
            _bez.colour(colour).start(start).control1(control1).control2(control2).end(end).draw(surface());
            return *this;
        };


    };

}
