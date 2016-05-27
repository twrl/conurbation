#pragma once

#ifndef _VA_LIST
typedef __builtin_va_list va_list;
#endif

#define va_start(a, b) __builtin_va_start(a, b)
#define va_end(a) __builtin_va_end(a)
#define va_arg(a, type) __builtin_va_arg(a, type)
#define va_copy(d, s) __builtin_va_copy(d, s)
