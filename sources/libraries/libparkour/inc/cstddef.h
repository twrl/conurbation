#pragma once

#include "stddef.h"

namespace std {
    using ::size_t;
    using ::ptrdiff_t;
    
    typedef decltype(nullptr) nullptr_t;
    
}

#define NULL nullptr
