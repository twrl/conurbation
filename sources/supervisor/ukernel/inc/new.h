#pragma once

#include "stdlib.h"

void* operator new(size_t size) {
    return malloc(size);
}
void operator delete(void* ptr) noexcept {
    free(ptr);
}