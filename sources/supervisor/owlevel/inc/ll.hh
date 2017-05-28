#pragma once

/// \file
/// This file sets up the general programming model for using -lowlevel
/// You can opt out of the convenience macros for various subsystems by defining libowlevel_except_* preprocessor symbols

/// Define `libowlevel_except_primitives` to not auto-include definitions of primitive types
#ifndef libowlevel_except_primitives
#include "numeric_types.hh"
#include "char_types.hh"
#include "atomic_types.hh"
#include "vector_types.hh"
#include "guid.hh"
#endif

/// Define `libowlevel_except_results` to not include or set aliases for -lowlevel's result handling
#ifndef libowlevel_except_results
#include "ll/result.hh"

template <typename T>
using _ = ll::result_t<T>;
#endif

#ifndef libowlevel_except_variant

#include "ll/variant.hh"
#endif

/// Define `libowlevel_except_reflection` to not include or set aliases for -lowlevel's reflection subsystem
#ifndef libowlevel_except_reflection

#endif


/// Define `libowlevel_except_logging` to not include logging
#ifndef libowlevel_except_logging

#endif


#ifndef libowlevel_except_memory
#include "ll/memory.hh"

using ll::operator""_KiB;
using ll::operator""_MiB;
using ll::operator""_GiB;

#endif
