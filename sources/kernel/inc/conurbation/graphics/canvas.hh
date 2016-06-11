#pragma once

#include "numeric_types.hh"
#include "vector_types.hh"

namespace Conurbation::Graphics
{

    class canvas_p {

    public:
        virtual auto width() -> uint64_t = 0;
        virtual auto height() -> uint64_t = 0;

        virtual auto colour() -> uint32x4_t = 0;
        virtual auto colour(uint32x4_t) -> canvas_p* = 0;

        virtual auto drawPixel(uint64_t x, uint64_t y) -> canvas_p* = 0;
        virtual auto drawPixel(uint64x2_t point) -> canvas_p* = 0;

        virtual auto drawLine(uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1) -> canvas_p*;
        virtual auto drawLine(uint64x2_t p0, uint64x2_t p1) -> canvas_p*;
        virtual auto drawQuadBezier(uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2) -> canvas_p*;
        virtual auto drawQuadBezier(uint64x2_t p0, uint64x2_t p1, uint64x2_t p2) -> canvas_p*;
        virtual auto drawCubeBezier(uint64_t x0, uint64_t y0, uint64_t x1, uint64_t y1, uint64_t x2, uint64_t y2, uint64_t x3,
            uint64_t y3) -> canvas_p*;
        virtual auto drawCubeBezier(uint64x2_t p0, uint64x2_t p1, uint64x2_t p2, uint64x2_t p3) -> canvas_p*;
    };
}
