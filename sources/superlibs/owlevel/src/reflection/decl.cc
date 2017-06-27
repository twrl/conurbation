#include "ll/reflect/class.hh"

[[gnu::constructor]]
static void decls() {

    ll::Reflect::class_t::declare<ll::Reflect::class_t>("ll::Reflect::class_t");

}
