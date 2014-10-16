#include "uefi/efitypes.h"
#include "elf.h"

extern "C" efi_status_t _self_relocate(uintptr_t loadBase, elf64_dyn_t* dynamic) {
    
}

static void _apply_rel(uintptr_t loadBase, elf64_rel_t* rel) {
    elf_x64_relocation_type_t rel_type = rel->getType();
    
    switch (rel_type) {
        case x86_64_none:
            break;
        case x86_64_relative:
            *(uintptr_t*)(loadBase + rel->r_offset) += loadBase;
            break;
        default:
            break;
    }
}

static void _apply_rela(uintptr_t loadBase, elf64_rela_t* rela) {
    elf_x64_relocation_type_t rela_type = rela->getType();
    
    switch (rela_type) {
        case x86_64_none:
            break;
        case x86_64_relative:
            *(uintptr_t*)(loadBase + rela->r_offset) += loadBase + rela->r_addend;
            break;
        default:
            break;
    }
}