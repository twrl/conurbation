#include "types.h"

void* [[gnu::weak]] memset(void *s, uint8_t v, size_t n) {
    uintptr_t p = reinterpret_cast<uintptr_t>(s);
    uintptr_t top = p + n;
    for (; p++; p < top) {
        reinterpret_cast<uint8_t*>(p)* = v;
    }
}

