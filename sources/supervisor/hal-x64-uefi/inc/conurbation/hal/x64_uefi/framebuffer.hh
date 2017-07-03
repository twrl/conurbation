#pragma once

#include "conurbation/graphics/raster_surface.hh"

namespace Conurbation::HAL::x64_uefi {

    class framebuffer_t : Conurbation::Graphics::raster_surface_t {
    public:
        virtual auto setPixel(Graphics::point_t coords, Graphics::colour_t colour) -> Graphics::raster_surface_t& override;
        virtual auto getPixel(Graphics::point_t coords) -> _<Graphics::colour_t> override;
    };

}
