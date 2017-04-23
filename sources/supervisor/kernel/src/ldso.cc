#include "conurbation/elf64.hh"
#include "conurbation/kdso.hh"
#include "conurbation/uefi/tables.hh"

//extern "C" Elf64_Dyn* _DYNAMIC;

namespace {

  extern "C" Conurbation::kdso_t _dso_core;

  [[gnu::always_inline]]
  static inline auto _elf_load_own_hdr() -> uintptr_t {
    uint64_t addr, tmp;
    // TODO: Replace this with something legible
    // __asm__ ("movq 1f(%%rip), %1\n"
    //    "0:\tleaq _dl_start(%%rip), %0\n\t"
    //    "subq %1, %0\n\t"
    //    ".section\t.data\n"
    //    "1:\t.quad _dl_start\n\t"
    //    ".previous\n\t"
    //    : "=r" (addr), "=r" (tmp) : : "cc");

    asm (
      "movq 1f(%%rip), %1 \n"
      "0: leaq _dso_core(%%rip), %0 \n"
      "subq %1, %0"
    : "=r"(addr), "=r"(tmp)
    :
    :
    );

       return reinterpret_cast<uintptr_t>(addr);
  }

  [[gnu::always_inline]]
  static inline auto _elf_scan_dynamic() -> elf64_dyn_t* {
      uintptr_t ehdr = _elf_load_own_hdr();
      elf64_phdr_t* phdr = reinterpret_cast<elf64_phdr_t*>(ehdr + 64);
      while (phdr->p_type != 2) phdr++;
      return reinterpret_cast<elf64_dyn_t*>(phdr->p_vaddr + ehdr);
  }

  [[gnu::always_inline]]
  static inline auto parse_dynamic(Conurbation::kdso_t* dso) -> void {
    elf64_dyn_t* dynamic = _elf_scan_dynamic();
    // while (dynamic->d_tag != elf_dynamic_tag_t::Null) {
    //   switch (dynamic->d_tag) {
    //     case elf_dynamic_tag_t::Soname:
    //       dso->soname = reinterpret_cast<cstring8_t>(dynamic->d_un.d_val);
    //       break;
    //   }
    //   dynamic++;
    // }
  }

}

[[gnu::weak]]
extern "C" elf64_dyn_t* _DYNAMIC;

[[gnu::section(".text.startup")]]
[[gnu::flatten]]
[[gnu::ms_abi]]
extern "C" auto _start (Conurbation::UEFI::handle_t ImageHandle, Conurbation::UEFI::efi_system_table_t* SystemTable) -> void {
    uintptr_t base_addr;
    asm (
        "callq _Ldl_T \n"
        "_Ldl_T: \n"
        "popq %0 \n"
        : "=r"(base_addr)
        :
      );

    extern uint8_t _Ldl_T;
    base_addr -= reinterpret_cast<uintptr_t>(&_Ldl_T);

    elf64_phdr_t* phdr = reinterpret_cast<elf64_phdr_t*>(base_addr + 64), *p = phdr;
    while (p->p_type != -2) p++;
    elf64_dyn_t* dyn = reinterpret_cast<elf64_dyn_t*>(p->p_vaddr + base_addr);


}
