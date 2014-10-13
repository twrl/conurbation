#include "types.h"

struct elf64_header_t {
    uint8_t             e_ident[16];
    uint16_t            e_type;
    uint16_t            e_machine;
    uint32_t            e_version;
    uint64_t            e_entry;
    uint64_t            e_phoff;
    uint64_t            e_shoff;
    uint32_t            e_flags;
    uint16_t            e_ehsize;
    uint16_t            e_phentsize;
    uint16_t            e_phnum;
    uint16_t            e_shentsize;
    uint16_t            e_shnum;
    uint16_t            e_shstrndx;
};

enum elf_section_type_t : uint32_t {
    SHT_NULL            = 0,
    SHT_PROGBITS        = 1,
    SHT_SYMTAB          = 2,
    SHT_STRTAB          = 3,
    SHT_RELA            = 4,
    SHT_HASH            = 5,
    SHT_DYNAMIC         = 6,
    SHT_NOTE            = 7,
    SHT_NOBITS          = 8,
    SHT_REL             = 9,
    SHT_SHLIB           = 10,
    SHT_DYNSYM          = 11,
    SHT_NUM             = 12,
    
    SHT_LOOS            = 0x60000000,
    SHT_LOSUNW          = 0x6ffffffb,
    SHT_SUNW_COMDAT     = 0x6ffffffb,
    SHT_SUNW_syminfo    = 0x6ffffffc,
    SHT_GNU_verdef      = 0x6ffffffd,
    SHT_GNU_verneed     = 0x6ffffffe,
    SHT_GNU_versym      = 0x6fffffff,
    SHT_HISUNW          = 0x6fffffff,
    SHT_HIOS            = 0x6fffffff,
    
    SHT_LOPROC          = 0x70000000,
    SHT_HIPROC          = 0x7fffffff,
    
    SHT_LOUSER          = 0x80000000,
    SHT_HIUSER          = 0x8fffffff
};

struct elf64_sectionheader_t {
    uint32_t            sh_name;
    elf_section_type_t  sh_type;
    uint64_t            sh_flags;
    uint64_t            sh_addr;
    uint64_t            sh_offset;
    uint64_t            sh_size;
    uint32_t            sh_link;
    uint32_t            sh_info;
    uint64_t            sh_addralign;
    uint64_t            sh_entsize;
};


struct elf64_sym_t {
    uint32_t            st_name;
    uint8_t             st_info;
    uint8_t             st_other;
    uint16_t            st_shndx;
    uint64_t            st_value;
    uint64_t            st_size;
};


struct elf64_rel_t {
    uint64_t            r_offset;
    uint64_t            r_info;
};

struct elf64_rela_t {
    uint64_t            r_offset;
    uint64_t            r_info;
    int64_t             r_addend;
};



enum elf_segment_type_t : uint32_t {
    PT_NULL             = 0,
    PT_LOAD             = 1,
    PT_DYNAMIC          = 2,
    PT_INTERP           = 3,
    PT_NOTE             = 4,
    PT_SHLIB            = 5,
    PT_PHDR             = 6,
    PT_NUM              = 7,
    
    PT_LOOS             = 0x60000000,
    PT_HIOS             = 0x6fffffff,
    
    PT_LOPROC           = 0x70000000,
    PT_HIPROC           = 0x7fffffff
};

struct elf64_phdr_t {
    elf_segment_type_t  p_type;
    uint32_t            p_flags;
    uint64_t            p_offset;
    uint64_t            p_vaddr;
    uint64_t            p_paddr;
    uint64_t            p_filesz;
    uint64_t            p_memsz;
    uint64_t            p_align;
};

