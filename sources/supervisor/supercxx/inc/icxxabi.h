#pragma once

#include "types.h"

#define ATEXIT_MAX_FUNCS 128

struct atexit_func_entry_t {
    void    (*dtor)(void*);
    void*   object;
    void*   dso_handle;
};

extern "C" int __cxa_atexit(void (*f)(void*), void* o, void* dso);
extern "C" void __cxa_finalize(void *f);

/*namespace __cxxabiv1 {

    extern "C" int __cxa_guard_acquire (int64_t *);
    extern "C" void __cxa_guard_release (int64_t *);
	extern "C" void __cxa_guard_abort (int64_t *);
	
}*/

