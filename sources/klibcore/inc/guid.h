#pragma once

#include "stdint.h"
#include "stddef.h"

struct guid_t {
    std::uint32_t data1;
    std::uint16_t data2;
    std::uint16_t data3;
    std::uint8_t data4[8];

    constexpr guid_t(const char*);
    constexpr bool operator==(guid_t&);
};

// Hex-digit to integer helper func
inline static constexpr std::uint32_t hton(const char c)
{
    // static_assert(c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c ==
    // '5' | c == '6' | c
    // == '7' | c == '8' | c == '9' | c == 'a' | c == 'b' | c == 'c' | c == 'd' |
    // c == 'e' | c ==
    // 'f', "Is valid hex character");
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'a':
        case 'A':
            return 10;
        case 'b':
        case 'B':
            return 11;
        case 'c':
        case 'C':
            return 12;
        case 'd':
        case 'D':
            return 13;
        case 'e':
        case 'E':
            return 14;
        case 'f':
        case 'F':
            return 15;
        default:
            return 0;
    }
}

constexpr guid_t::guid_t(const char* string)
    : data1((hton(string[0]) << 28) + (hton(string[1]) << 24) + (hton(string[2]) << 20) + (hton(string[3]) << 16)
          + (hton(string[4]) << 12) + (hton(string[5]) << 8) + (hton(string[6]) << 4) + (hton(string[7])))
    , data2(static_cast<std::uint16_t>(
          (hton(string[9]) << 12) + (hton(string[10]) << 8) + (hton(string[11]) << 4) + (hton(string[12]))))
    , data3(static_cast<std::uint16_t>(
          (hton(string[14]) << 12) + (hton(string[15]) << 8) + (hton(string[16]) << 4) + (hton(string[17]))))
    , data4{ static_cast<std::uint8_t>((hton(string[19]) << 4) + hton(string[20])),
        static_cast<std::uint8_t>((hton(string[21]) << 4) + hton(string[22])),
        static_cast<std::uint8_t>((hton(string[24]) << 4) + hton(string[25])),
        static_cast<std::uint8_t>((hton(string[26]) << 4) + hton(string[27])),
        static_cast<std::uint8_t>((hton(string[28]) << 4) + hton(string[29])),
        static_cast<std::uint8_t>((hton(string[30]) << 4) + hton(string[31])),
        static_cast<std::uint8_t>((hton(string[32]) << 4) + hton(string[33])),
        static_cast<std::uint8_t>((hton(string[34]) << 4) + hton(string[35])) }
{
}

constexpr bool guid_t::operator==(guid_t& that)
{
    return this->data1 == that.data1 && this->data2 == that.data2 && this->data3 == that.data3
        && this->data4[0] == that.data4[0] && this->data4[1] == that.data4[1] && this->data4[2] == that.data4[2]
        && this->data4[3] == that.data4[3] && this->data4[4] == that.data4[4] && this->data4[5] == that.data4[5]
        && this->data4[6] == that.data4[6] && this->data4[7] == that.data4[7];
}

constexpr guid_t operator""_guid(const char* lit, std::size_t sz) { return guid_t(lit); };

namespace UEFI {
    template <typename T> constexpr guid_t protocol_guid_v = "00000000-0000-0000-0000000000000000"_guid;
}