#pragma once 

#include "ll/ucd.hh"

namespace ll::Parse {
    
    struct parse {
        constexpr parse(const char8_t* source, size_t position): source_(source), position_(position) {}
        const char8_t* source_;
        size_t position_;
    };
    
    inline static constexpr uint32_t hton(const char c)
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
    
};