#pragma once

#include "conurbation/graphics/raster_surface.hh"

namespace Conurbation {

    class system_environment_t {
    private:
        Conurbation::Graphics::raster_surface_t* framebuffer_;
    public:
        // auto topology() -> topology_t&;
        //
        // auto physical_memory() -> address_space_t&;
        //
        // auto pci_config_space() -> address_space_t&;
        //
        // auto port_space() -> address_space_t&;
        //
        // auto event_router() -> event_router_t&;
        //
        // auto random() -> ll::rng_t&;
        //
        // auto time() -> timesource_t&;

        inline auto framebuffer() -> Conurbation::Graphics::raster_surface_t& { return *framebuffer_; }
        inline auto framebuffer(Conurbation::Graphics::raster_surface_t& value) -> system_environment_t& { framebuffer_ = &value; return *this; }

    };

}
