#include "conurbation/numeric_types.hh"

extern "C" {

    uintptr_t __stack_chk_guard = 0x595e9fbd94fda766;

    [[gnu::noreturn]]
    void __stack_chk_fail() {
        asm volatile ("cli; hlt;");
        __builtin_unreachable();
    }

}
