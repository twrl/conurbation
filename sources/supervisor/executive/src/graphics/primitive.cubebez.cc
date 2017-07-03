#include "conurbation/graphics/primitives.hh"

namespace Conurbation::Graphics {

    auto cubic_bezier_t::at(float64_t parameter) -> point_t {
        return (float64x2_t{parameter * parameter * parameter, parameter * parameter * parameter} * start_)
             + (float64x2_t{3 * parameter * parameter * (1-parameter), 3 * parameter * parameter * (1-parameter)} * control1_)
             + (float64x2_t{3 * parameter * (1-parameter) * (1-parameter), 3 * parameter * (1-parameter) * (1-parameter)} * control2_)
             + (float64x2_t{(1 - parameter) * (1 - parameter) * (1-parameter), (1 - parameter) * (1 - parameter) * (1-parameter)} * end_);
    }

    namespace {

        auto maxnorm(point_t a, point_t b) -> int64_t {
            auto v = b - a;
            return __builtin_abs(v[0]) > __builtin_abs(v[1]) ? __builtin_abs(v[0]) : __builtin_abs(v[1]);
        }

        auto trisect(cubic_bezier_t& bez, raster_surface_t& surface, float64_t p0, float64_t p1, float64_t p2) -> void {
            auto x0 = bez.at(p0);
            auto x1 = bez.at(p1);
            auto x2 = bez.at(p2);

            if (maxnorm((x0 + x2) / point_t{2,2}, x1) < 1) {
                line_t line;
                line.colour(bez.primitive_t<cubic_bezier_t>::colour()).start(x0).end(x2).draw(surface);
            } else {
                trisect(bez, surface, p0, (p0 + p1)/2, p1);
                trisect(bez, surface, p1, (p1 + p2)/2, p2);
            }

        }

    }

    auto cubic_bezier_t::draw(Conurbation::Graphics::raster_surface_t& surface) -> cubic_bezier_t& {
        trisect(*this, surface, 0.0, 0.5, 1.0);
        return *this;
    };

}
