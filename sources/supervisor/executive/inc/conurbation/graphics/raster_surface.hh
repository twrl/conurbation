#pragma once

#include "vector_types.hh"
#include "ll/result.hh"
#include "conurbation/graphics/primitives.hh"

namespace Conurbation::Graphics {

    class raster_surface_t {

    public:
        auto width() -> uint64_t;
        auto height() -> uint64_t;

        virtual auto setPixel(point_t coords, colour_t colour) -> raster_surface_t& = 0;
        virtual auto getPixel(point_t coords) -> _<colour_t> = 0;

    };

}
