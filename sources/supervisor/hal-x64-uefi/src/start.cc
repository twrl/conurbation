#include "types.h"
#include "uefi/tables.h"

extern "C" void halmain(efi_system_table_t* efiSystemTable);
void iterate_global_fn(void* start, void* end);

extern "C" {
    uintptr_t __preinit_array_start;
    uintptr_t __preinit_array_end;
    uintptr_t __init_array_start;
    uintptr_t __init_array_end;
    uintptr_t __fini_array_start;
    uintptr_t __fini_array_end;
    
}

extern "C" void _start [[gnu::naked]] (efi_system_table_t* efiSystemTable) {
    
    iterate_global_fn(&__preinit_array_start, &__preinit_array_end);
    iterate_global_fn(&__init_array_start, &__init_array_end);
    halmain(efiSystemTable);
    iterate_global_fn(&__fini_array_start, &__fini_array_end);
    asm volatile("cli; hlt;");
    __builtin_unreachable();
    
}

typedef void (vfunc)();

inline void iterate_global_fn(void* start, void* end) {
    uintptr_t _s = reinterpret_cast<uintptr_t>(start);
    uintptr_t _e = reinterpret_cast<uintptr_t>(end);
    uintptr_t _count = (_e - _s) / sizeof(void*);
    
    vfunc** _funcs = reinterpret_cast<vfunc**>(start);
    if (_count > 0) {
        for (int i = 0; i < _count; i++) {
            _funcs[i]();
        }
    }
}