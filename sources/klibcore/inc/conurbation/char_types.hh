#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"

typedef char char8_t;
#ifndef __cpp_unicode_literals
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif

typedef const char8_t* cstring8_t;
typedef const char16_t* cstring16_t;
typedef const char32_t* cstring32_t;

#pragma clang diagnostic pop
