#include "stddef.h"
#include "stdbool.h"

typedef void(destructor_f)(void*);

extern "C" void __cxa_pure_virtual(){};
extern "C" void __cxa_deleted_virtual(){};

struct atexit_func_entry_t {
    atexit_func_entry_t* next;
    destructor_f* dtor;
    void* dtor_obj;
    void* dso;
    std::bool_t called;
};

static atexit_func_entry_t* first = nullptr;
static atexit_func_entry_t* last = nullptr;

void* __dso_handle = nullptr;

extern "C" void __cxa_atexit(destructor_f* dtor, void* p, void* d)
{
    atexit_func_entry_t* fun = (atexit_func_entry_t*)(void*)kmalloc(sizeof(atexit_func_entry_t));
    fun->dtor = dtor;
    fun->dtor_obj = p;
    fun->dso = d;
    fun->next = nullptr;
    fun->called = false;
    if (!first) {
        first = fun;
        last = fun;
    }
    else {
        fun->next = first;
        first = fun;
    }
}

extern "C" void __cxa_finalize(void* d)
{
    atexit_func_entry_t* current = first;
    while (current) {
        if (d == nullptr || current->dso == d) {
            if (current->called)
                continue;
            current->dtor(current->dtor_obj);
            current->called = true;
        }
        current = current->next;
    }

    // FIXME: This algorithm is technically correct, but if there are DSOs being finalized it's going to leak memory because it
    // doesn't delete items from the list after they've been called.
}
