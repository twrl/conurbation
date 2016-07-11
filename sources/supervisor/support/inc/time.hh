#pragma once

#include "numeric_types.hh"

namespace Conurbation {

    // Instant is the Julian Day number represented as float64 (leaving)
    using instant_t = float64_t;

    struct datetime_t {
        datetime_t(float64_t instant) {}
        int16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint32_t nanosecond;
        int16_t timezone;
    };
}
