#pragma once 

#include "char_types.hh"

// icxxabi handlers



// Debug IO for LLDB/GDB stub support

typedef void (debug_put_char_f)(char8_t);
typedef char8_t (debug_get_char_f)();

auto set_debug_put_char(debug_put_char_f*) -> void;
auto get_debug_put_char() -> debug_get_char_f*;

auto set_debug_get_char(debug_get_char_f*) -> void;
auto get_debug_get_char() -> debug_get_char_f*;

