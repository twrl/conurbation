#include "numeric_types.hh"

namespace __cxxabiv1 {
    
    namespace {
        
        using guard_type = uintptr_t;
        
    }
    
    extern "C" auto __cxa_guard_acquire(guard_type* guard) -> int {
        char* init_object_ = reinterpret_cast<char*>(guard);
        return !*init_object_;
    }
    
    extern "C" auto __cxa_guard_release(guard_type* guard) -> void {
        *guard = 0;
        char* init_object_ = reinterpret_cast<char*>(guard);
        *init_object_ = 1;
    }
    
    extern "C" auto __cxa_guard_abort(guard_type* guard) -> void {
        *guard = 0;
    }
    
}