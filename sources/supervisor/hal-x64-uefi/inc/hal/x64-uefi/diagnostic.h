#pragma once

#include "hal/diagnostic.h"

namespace Conurbation::HAL::x64_uefi {

    class diagnostic_t : public Conurbation::HAL::diagnostic_i {
        public:
        virtual void Write(char* string);
    }
}