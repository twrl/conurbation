#include "string.h"

extern "C" void* memcpy[[gnu::weak]](void* dest, const void* src, size_t count) {
    size_t i = 0;
    char* s = (char*)src;
    char* d = (char*)dest;
    for (; i < count; i++)
        d[i] = s[i];
    return dest;
}

extern "C" void* memset[[gnu::weak]](void* dest, int ch, size_t count) {
    uint8_t v = (uint8_t)ch;
    size_t i = 0;
    char* d = (char*)dest;
    for (; i < count; i++)
        d[i] = v;
    return dest;
}
