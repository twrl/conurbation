#pragma once

#include "numeric_types.hh"
#include "ll/parse.hh"

struct guid_t {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];

    constexpr guid_t(const char*);
    constexpr bool operator==(const guid_t&);
};

constexpr guid_t::guid_t(const char* string)
    : data1((ll::Parse::hton(string[0]) << 28) + (ll::Parse::hton(string[1]) << 24) + (ll::Parse::hton(string[2]) << 20) + (ll::Parse::hton(string[3]) << 16)
          + (ll::Parse::hton(string[4]) << 12) + (ll::Parse::hton(string[5]) << 8) + (ll::Parse::hton(string[6]) << 4) + (ll::Parse::hton(string[7])))
    , data2(static_cast<uint16_t>(
          (ll::Parse::hton(string[9]) << 12) + (ll::Parse::hton(string[10]) << 8) + (ll::Parse::hton(string[11]) << 4) + (ll::Parse::hton(string[12]))))
    , data3(static_cast<uint16_t>(
          (ll::Parse::hton(string[14]) << 12) + (ll::Parse::hton(string[15]) << 8) + (ll::Parse::hton(string[16]) << 4) + (ll::Parse::hton(string[17]))))
    , data4{ static_cast<uint8_t>((ll::Parse::hton(string[19]) << 4) + ll::Parse::hton(string[20])),
        static_cast<uint8_t>((ll::Parse::hton(string[21]) << 4) + ll::Parse::hton(string[22])),
        static_cast<uint8_t>((ll::Parse::hton(string[24]) << 4) + ll::Parse::hton(string[25])),
        static_cast<uint8_t>((ll::Parse::hton(string[26]) << 4) + ll::Parse::hton(string[27])),
        static_cast<uint8_t>((ll::Parse::hton(string[28]) << 4) + ll::Parse::hton(string[29])),
        static_cast<uint8_t>((ll::Parse::hton(string[30]) << 4) + ll::Parse::hton(string[31])),
        static_cast<uint8_t>((ll::Parse::hton(string[32]) << 4) + ll::Parse::hton(string[33])),
        static_cast<uint8_t>((ll::Parse::hton(string[34]) << 4) + ll::Parse::hton(string[35])) }
{
}

constexpr bool guid_t::operator==(const guid_t& that)
{
    return this->data1 == that.data1 && this->data2 == that.data2 && this->data3 == that.data3
        && this->data4[0] == that.data4[0] && this->data4[1] == that.data4[1] && this->data4[2] == that.data4[2]
        && this->data4[3] == that.data4[3] && this->data4[4] == that.data4[4] && this->data4[5] == that.data4[5]
        && this->data4[6] == that.data4[6] && this->data4[7] == that.data4[7];
}

constexpr guid_t operator""_guid(const char* lit, size_t sz) { return guid_t(lit); };
