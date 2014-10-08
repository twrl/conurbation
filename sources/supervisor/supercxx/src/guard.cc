#include "icxxabi.h"

namespace __cxxabiv1 {
    
    extern "C" int __cxa_guard_acquire (int64_t *) {
        return 0;
    }
    
    extern "C" void __cxa_guard_release (int64_t *) {
        
    }
    
	extern "C" void __cxa_guard_abort (int64_t *) {
	    
	}
    
}