#pragma once

#include "stdint.h"
#include "stddef.h"

struct guid_t {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
};

typedef bool bool_t;

// typedef uint16_t            char16_t;

typedef uintptr_t paddr_t;
typedef uintptr_t vaddr_t;

struct chunk_t {
    void* base;
    size_t size;
};
