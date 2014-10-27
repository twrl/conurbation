#include "stdint.h"

constexpr uint32_t hton(const char c) {
    // static_assert(c == '0' | c == '1' | c == '2' | c == '3' | c == '4' | c == '5' | c == '6' | c
    // == '7' | c == '8' | c == '9' | c == 'a' | c == 'b' | c == 'c' | c == 'd' | c == 'e' | c ==
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

struct uuid_t {

    constexpr uuid_t(const char* string)
        : Data1((hton(string[0]) << 28) + (hton(string[1]) << 24) + (hton(string[2]) << 20)
                + (hton(string[3]) << 16) + (hton(string[4]) << 12) + (hton(string[5]) << 8)
                + (hton(string[6]) << 4) + (hton(string[7]))),
          Data2(static_cast<uint16_t>((hton(string[9]) << 12) + (hton(string[10]) << 8)
                                      + (hton(string[11]) << 4) + (hton(string[12])))),
          Data3(static_cast<uint16_t>((hton(string[14]) << 12) + (hton(string[15]) << 8)
                                      + (hton(string[16]) << 4) + (hton(string[17])))),
          Data4{ static_cast<uint8_t>((hton(string[19]) << 4) + hton(string[20])),
                 static_cast<uint8_t>((hton(string[21]) << 4) + hton(string[22])),
                 static_cast<uint8_t>((hton(string[24]) << 4) + hton(string[25])),
                 static_cast<uint8_t>((hton(string[26]) << 4) + hton(string[27])),
                 static_cast<uint8_t>((hton(string[28]) << 4) + hton(string[29])),
                 static_cast<uint8_t>((hton(string[30]) << 4) + hton(string[31])),
                 static_cast<uint8_t>((hton(string[32]) << 4) + hton(string[33])),
                 static_cast<uint8_t>((hton(string[34]) << 4) + hton(string[35])) } {
        // static_assert(string[8] == '-' && string[13] == '-' && string[18] == '-' && string[23] ==
        // '-' && string[36] == '\0', "General format test");
    }

    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
};

constexpr uuid_t operator"" _uuid(const char* literal, unsigned long num_chars) {
    return uuid_t(literal);
};

uuid_t someUUID = "9533bd2a-6206-458e-9725-34e6d6db89d0"_uuid;
uuid_t someOtherUUID = "0550f24f-9c53-47b6-9300-f8b9fa571918"_uuid;
