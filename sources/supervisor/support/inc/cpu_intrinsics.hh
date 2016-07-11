#pragma once

#ifndef __cplusplus
#error "Cannot include pure C++ header in C code"
#endif

#include "numeric_types.hh"

#define intrinsic extern "C" inline auto __attribute__((__always_inline__))

intrinsic __readeflags()->uint64_t { return __builtin_ia32_readeflags_u64(); }
intrinsic __writeeflags(uint64_t _f)->void { __builtin_ia32_writeeflags_u64(_f); }

intrinsic __rdpmc(int32_t _a)->uint64_t { return __builtin_ia32_rdpmc(_a); }
intrinsic __rdtsc()->uint64_t { return __builtin_ia32_rdtsc(); }
intrinsic __rdtscp(uint32_t* _a)->uint64_t { return __builtin_ia32_rdtscp(_a); }

#undef intrinsic
