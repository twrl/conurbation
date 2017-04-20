#include "conurbation/elf64.hh"
#include "conurbation/kdso.hh"

//extern "C" Elf64_Dyn* _DYNAMIC;

namespace {

  Conurbation::kdso_t core;

  [[gnu::section(".text.startup")]]
  auto parse_dynamic(elf64_dyn_t* dynamic, Conurbation::kdso_t* dso) -> void {
    while (dynamic->d_tag != elf_dynamic_tag_t::Null) {
      switch (dynamic->d_tag) {
        case elf_dynamic_tag_t::Soname:
          dso->soname = reinterpret_cast<cstring8_t>(dynamic->d_un.d_val);
          break;
      }
      dynamic++;
    }
  }

}

[[gnu::weak]]
extern "C" elf64_dyn_t* _DYNAMIC;

[[gnu::section(".text.startup")]]
extern "C" auto _start () -> void {
    parse_dynamic(_DYNAMIC, &core);
}
