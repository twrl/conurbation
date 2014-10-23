#pragma once

#ifdef _LP64
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

// TODO: Deal with _LLP64, etc

typedef uint64_t uintptr_t;
typedef int64_t intptr_t;

#endif