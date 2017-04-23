#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

typedef char char8_t;
#ifndef __cpp_unicode_characters
#ifdef __cpp_unicode_literals
typedef decltype(u'a') char16_t;
typedef decltype(U'a') char32_t;
#else
#include "conurbation/numeric_types.hh"
typedef uint16_t char16_t;
typedef uint32_t char32_t;
#endif
#endif


typedef const char8_t* cstring8_t;
typedef const char16_t* cstring16_t;
typedef const char32_t* cstring32_t;
