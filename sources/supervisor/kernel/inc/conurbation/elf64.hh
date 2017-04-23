#pragma once

#include "conurbation/numeric_types.hh"

struct elf64_ehdr_t {

    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;

};

struct elf64_shdr_t {

    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;

};

struct elf64_sym_t{

    uint32_t st_name;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t st_shndx;
    uint64_t st_value;
    uint64_t st_size;

};

struct elf64_rel_t {
    uint64_t r_offset;
    uint64_t r_info;

    inline auto symbol() -> const uint32_t { return (r_info >> 32); }
    inline auto symbol(const uint32_t s) -> elf64_rel_t& { r_info = ((uint64_t)s << 32) + (type() & 0xFFFFFFFFL); return *this; }
    inline auto type() -> const uint32_t { return (uint32_t)(r_info & 0xFFFFFFFFL); }
    inline auto type(const uint32_t t) -> elf64_rel_t& { r_info = ((uint64_t)symbol() << 32) + (t & 0xFFFFFFFFL); return *this; }
};

struct elf64_rela_t {
    uint64_t r_offset;
    uint64_t r_info;
    int64_t r_addend;

    inline auto symbol() -> const uint32_t { return (r_info >> 32); }
    inline auto symbol(const uint32_t s) -> elf64_rela_t& { r_info = ((uint64_t)s << 32) + (type() & 0xFFFFFFFFL); return *this; }
    inline auto type() -> const uint32_t { return (uint32_t)(r_info & 0xFFFFFFFFL); }
    inline auto type(const uint32_t t) -> elf64_rela_t& { r_info = ((uint64_t)symbol() << 32) + (t & 0xFFFFFFFFL); return *this; }
};

#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i)&0xffffffffL)
#define ELF64_R_INFO(s, t) (((s) << 32) + ((t)&0xffffffffL))

struct elf64_phdr_t {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
};

enum class elf_dynamic_tag_t : int64_t {
    Null = 0,
    Needed = 1,
    PltRelSz = 2,
    PltGot = 3,
    Hash = 4,
    Strtab = 5,
    Symtab = 6,
    Rela = 7,
    RelaSz = 8,
    RelaEnt = 9,
    StrSz = 10,
    SymEnt = 11,
    Init = 12,
    Fini = 13,
    Soname = 14,
    Rpath = 15,
    Symbolic = 16,
    Rel = 17,
    RelSz = 18,
    RelEnt = 19,
    PltRel = 20,
    Debug = 21,
    TextRel = 22,
    JmpRel = 23,
    BindNow = 24,
    InitArray = 25,
    FiniArray = 26,
    InitArraySz = 27,
    FiniArraySz = 28,
    Runpath = 29,
    Flags = 30,
    PreinitArray = 32,
    PreinitArraySz = 33,

    Auxiliary = 0x7FFFFFFD,
    Filter = 0x7FFFFFFF
};

struct elf64_dyn_t {
    elf_dynamic_tag_t d_tag;
    union {
        uint64_t d_val;
        uint64_t d_ptr;
    } d_un;
};
