#pragma once

#include "types.h"

namespace Conurbation {

    struct opaque_info_t {
        void* data;
        size_t size;
        contextid_t context;
    };

    class opaque_manager_t { public: }
}