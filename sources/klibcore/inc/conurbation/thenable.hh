#pragma once 

#include "conurbation/callable.hh"

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

namespace Conurbation {
    
    template <typename TSuccess>
    class thenable_p {
        public:
            template <typename TRet>
            virtual auto then(callable_p<thenable_p<TRet>(TSuccess)> onSuccess) -> thenable_p<TRet> = 0;
            
            template <typename TRet>
            virtual auto then(callable_p<thenable_p<TRet>(TSuccess)> onSuccess, callable_p<thenable_p<TRet>(status_t)> onFail) -> thenable_p<TRet> = 0;
            
    };
    
}