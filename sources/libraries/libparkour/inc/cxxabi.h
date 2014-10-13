namespace std {
    
    class type_info;
    
}

namespace __cxxabiv1 {
    extern "C" {
        typedef void (*unexpected_handler)();
        typedef void (*terminate_handler)();
        
        struct __cxa_exception {
#ifdef __LP64
            uintptr_t           referenceCount;
#endif
            std::type_info*     exceptionType;
            unexpected_handler* unexpectedHandler;
            terminate_handler*  terminateHandler;
            __cxa_exception*    nextException;
            int                 handlerCount;
            int                 handlerSwitchValue;
            const char*         actionRecord;
            const char*         languageSpecificData;
            void*               catchTemp;
#ifndef __LP64
            uintptr_t           referenceCount
#endif
            _Unwind_Exception   unwindHeader;
        }
        
    }
}