#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

namespace Conurbation {
    
    template <typename TReturn, typename ... TArgs>
    class callable_p<TReturn(TArgs...)> {
        
    };
    
}