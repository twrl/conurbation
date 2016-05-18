#include "conurbation/graphics/canvas.hh"

namespace Conurbation::Graphics
{

    namespace {

        uint64_t euclidean_distance(uint64x2_t a, uint64x2_t b) { return (a - b) * (a - b); }
    }

    auto canvas_p::drawLine(uint64x2_t p0, uint64x2_t p1)->canvas_p *
    {
        if (euclidean_distance(p0, p1) <= 1) {
            drawPixel(p0);
            drawPixel(p1);
        }
        else {
            uint64x2_t m = (p0 + p1) / 2UL;
            drawLine(p0, m);
            drawLine(m, p1);
        }
        return this;
    }

    auto canvas_p::drawQuadBezier(uint64x2_t p0, uint64x2_t p1, uint64x2_t p2)->canvas_p *
    {
        if (euclidean_distance(p0, p2) <= 1) {
            drawPixel(p0);
            drawPixel(p2);
        }
        else {
            uint64x2_t m = (p0 / 4) + (p1 / 2) + (p2 / 4);
            drawQuadBezier(p0, m);
            drawQuadBezier(m, p1);
        }
        return this;
    }

    auto canvas_p::drawCubeBezier(uint64x2 p0, uint64x2_t p1, uint64x2_t p2, uint64x2_t p3)->canvas_p *
    {
        if (euclidean_distance(p0, p3) <= 1) {
            drawPixel(p0);
            drawPixel(p3);
        }
        else {
            uint64x2_t m = (p0 / 8) + (3 * p1 / 8) + (3 * p2 / 8) + (p3 / 8);
            drawCubeBezier(p0, m);
            drawCubeBezier(m, p1);
        }
        return this;
    }
}
