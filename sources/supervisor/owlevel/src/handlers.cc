#include "handlers.hh"

namespace {
    
    template <typename HandlerFnType, HandlerFnType* Var>
    auto get() -> HandlerFnType* {
        return Var;
    }
    
    template <typename HandlerFnType, HandlerFnType* Var>
    auto set(HandlerFnType* fn) -> void {
        Var = fn;
    }
    
    debug_get_char_f* debug_get_char_;
    debug_put_char_f* debug_put_char_;
}

[[gnu::flatten]]
auto set_debug_get_char(debug_get_char_f* fn) -> void {
    set<debug_get_char_f, debug_get_char_>(fn);
}

[[gnu::flatten]]
auto set_debug_put_char(debug_put_char_f* fn) -> void {
    set<debug_put_char_f, debug_put_char_>(fn);
}

[[gnu::flatten]]
auto get_debug_get_char() -> debug_get_char_f* {
    return get<debug_get_char_f, debug_get_char_>();
}

[[gnu::flatten]]
auto get_debug_put_char() -> debug_put_char_f* {
    return get<debug_put_char_f, debug_put_char_>();
}