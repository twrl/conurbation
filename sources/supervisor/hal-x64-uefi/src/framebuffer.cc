#include "conurbation/hal/x64_uefi/framebuffer.hh"

using namespace Conurbation::Graphics;

namespace Conurbation::HAL::x64_uefi {

    auto framebuffer_t::getPixel(point_t coords) -> _<colour_t> {

    };

    auto framebuffer_t::setPixel(point_t coords, colour_t colour) -> raster_surface_t& {

        return *this;
    }

}
