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

enum elf_x64_relocation_type_t: uint64_t {
    x86_64_none         = 0,
    x86_64_64           = 1,
    x86_64_pc32         = 2,
    x86_64_got32        = 3,
    x86_64_plt32        = 4,
    x86_64_copy         = 5,
    x86_64_glob_dat     = 6,
    x86_64_jump_slot    = 7,
    x86_64_relative     = 8,
    x86_64_gotpcrel     = 9,
    x86_64_32           = 10,
    x86_64_32S          = 11,
    x86_64_16           = 12,
    x86_64_pc16         = 13,
    x86_64_8            = 14,
    x86_64_pc8          = 15,
    x86_64_dtpmod64     = 16,
    x86_64_dtpoff64     = 17,
    x86_64_tpoff64      = 18,
    x86_64_tlsgd        = 19,
    x86_64_tlsld        = 20,
    x86_64_dtpoff32     = 21,
    x86_64_gottpoff     = 22,
    x86_64_tpoff32      = 23,
    x86_64_pc64         = 24,
    x86_64_gotoff64     = 25,
    x86_64_gotpc32      = 26,
    x86_64_got64        = 27,
    x86_64_gotpcrel64   = 28,
    x86_64_gotpc64      = 29,
    x86_64_gotplt64     = 30,
    x86_64_pltoff64     = 31,
    x86_64_size32       = 32,
    x86_64_size64       = 33,
    x86_64_gotpc32_tlsdesc = 34,
    x86_64_tlsdesc_call = 35,
    x86_64_tlsdesc      = 36,
    x86_64_irelative    = 37
    
};

struct elf64_rel_t {
    uint64_t            r_offset;
    uint64_t            r_info;
    
    uint32_t getSymbol() const { return (r_info >> 32); }
    elf_x64_relocation_type_t getType() const { return (elf_x64_relocation_type_t)(r_info & 0xffffffffL); }
};

struct elf64_rela_t {
    uint64_t            r_offset;
    uint64_t            r_info;
    int64_t             r_addend;
    
    uint32_t getSymbol() const { return (r_info >> 32); }
    elf_x64_relocation_type_t getType() const { return (elf_x64_relocation_type_t)(r_info & 0xffffffffL); }
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

enum elf64_dyn_tag_t: int64_t {
    DT_NULL             = 0,
    DT_NEEDED           = 1
};

struct elf64_dyn_t {
    int64_t             d_tag;
    uint64_t            d_val;
};
