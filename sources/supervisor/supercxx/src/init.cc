#include "types.h"

typedef void(vfunc)();

extern "C" vfunc* __init_array_start;
extern "C" vfunc* __init_array_end;

extern "C" void process_init_array() {
    int initializer_count = (&__init_array_end - &__init_array_start) / sizeof(void*);
}
