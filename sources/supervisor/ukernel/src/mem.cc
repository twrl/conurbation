#include "types.h"

extern "C" void* memset [[gnu::weak]] (void *s, uint8_t v, size_t n) {
    
    uint8_t* dst = reinterpret_cast<uint8_t*>(s);
    for (n--; n--; n >= 0) dst[n] = v;
    
    return dst;
}

