#include "icxxabi.h"

static atexit_func_entry_t atexit_funcs[ATEXIT_MAX_FUNCS];
static intptr_t atexit_count = 0;

void* __dso_handle = 0;

extern "C" int __cxa_atexit(void (*f)(void*), void* o, void* dso) {
    if (atexit_count >= ATEXIT_MAX_FUNCS)
        return -1;
    else {
        atexit_funcs[atexit_count].dtor = f;
        atexit_funcs[atexit_count].object = o;
        atexit_funcs[atexit_count].dso_handle = dso;
        atexit_count++;
        return 0;
    }
}

extern "C" void __cxa_finalize(void* d) {
    intptr_t i = atexit_count;

    for (; i >= 0; i--) {
        if (atexit_funcs[i].dtor) {
            if (!d || d == atexit_funcs[i].dso_handle) {
                atexit_funcs[i].dtor(atexit_funcs[i].object);
                atexit_funcs[i].dtor = 0;
            }
        }
    }
    // FIXME: Destructor list will gain holes if __cxa_finalize is called for
    // multiple DSOs
}