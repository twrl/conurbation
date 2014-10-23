#pragma once

#include "types.h"

namespace Conurbation {

    struct eventspec_t {
        uintptr_t* vector;
    };

    typedef void(hwevent_f)(void*);

    namespace HAL {

        class hwevent_i {

            public:
            virtual void attachHandler(eventspec_t* event, hwevent_f* handler, void* handlerState)
                = 0;
            virtual void detachHandler(eventspec_t* event, hwevent_f* handler) = 0;
        };
    }
}