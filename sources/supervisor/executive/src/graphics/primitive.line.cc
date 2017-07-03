#include "conurbation/graphics/primitives.hh"
#include "conurbation/graphics/raster_surface.hh"

namespace Conurbation::Graphics {


    auto line_t::gradient() -> float64_t const {
        point_t vec = end_ - start_;
        return vec[1] / vec[0];
    };

    auto line_t::at(float64_t parameter) -> point_t {
        float64x2_t p_ = {parameter, parameter};
        return start_ + (p_ * (end_ - start_));
    };

    namespace {

        auto findOctant(point_t vector) {
            return static_cast<uint64_t>((__builtin_atan2(vector[1], vector[0]) + __builtin_atan2(-1.0, 1.0/-0.0)) * 4. / __builtin_atan2(1.0, 1.0/-0.0)) % 8;
        };

        auto toZeroOctant(uint64_t sourceOctant, point_t pt) -> point_t {
            switch (sourceOctant) {
            case 0:
                return pt;
            case 1:
                return { pt[1], pt[0] };
            case 2:
                return { pt[1], -pt[0] };
            case 3:
                return { -pt[0], pt[1] };
            case 4:
                return { -pt[0], -pt[1] };
            case 5:
                return { -pt[1], -pt[0] };
            case 6:
                return { -pt[1], pt[0] };
            case 7:
                return { pt[0], -pt[1] };
            }
        };

        auto fromZeroOctant(uint64_t sourceOctant, point_t pt) -> point_t {
            switch (sourceOctant) {
            case 0:
                return pt;
            case 1:
                return { pt[1], pt[0] };
            case 2:
                return { -pt[1], pt[0] };
            case 3:
                return { -pt[0], pt[1] };
            case 4:
                return { -pt[0], -pt[1] };
            case 5:
                return { -pt[1], -pt[0] };
            case 6:
                return { pt[1], -pt[0] };
            case 7:
                return { pt[0], -pt[1] };
            }
        };

    };

    // This uses Bresenham's algorithm to draw a line on a surface
    auto line_t::draw(Conurbation::Graphics::raster_surface_t& surface) -> line_t& {
        auto vec = end_ - start_;
        auto octant = findOctant(vec);

        auto startp = toZeroOctant(octant, start_);
        auto endp = toZeroOctant(octant, end_);

        auto dx = static_cast<int64_t>((endp - startp)[0]);
        auto dy = static_cast<int64_t>((endp - startp)[1]);
        auto D = 2*dy - dx;
        auto y = static_cast<int64_t>(startp[1]);

        for (auto x = static_cast<int64_t>(startp[0]); x <= static_cast<int64_t>(endp[0]); ++x)
        {
            surface.setPixel(fromZeroOctant(octant, point_t{x, y}), primitive_t<line_t>::colour());
            if (D > 0) {
                ++y;
                D -= 2*dx;
            }
            D += 2*dy;
        }

        return *this;
    };

}
