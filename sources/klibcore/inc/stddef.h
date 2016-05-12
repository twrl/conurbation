#pragma once

#include "_superapi.h"

_libsuper_begin_capi

    typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __SIZE_TYPE__ size_t;

#ifdef __cplusplus
typedef decltype(nullptr) nullptr_t;
#define NULL nullptr
#else
typedef void* nullptr_t;
#define NULL (nullptr_t)0
#define nullptr NULL
#endif

#define offsetof(type, member) ((std::size_t) & (((type*)0)->member))

typedef long double max_align_t;

_libsuper_end_capi