#include <efi.h>
#include <efilib.h>
#include "ldr.h"
#include "elf64.h"

Elf64_Ehdr* load_elf_header(e64l_load_info* loaderInfo)
{
    EFI_STATUS status;
    UINTN readsz = sizeof(Elf64_Ehdr);

    Elf64_Ehdr* ehdr;
    status = uefi_call_wrapper(BS->AllocatePool, 3, 2, readsz, &ehdr);

    status = uefi_call_wrapper(loaderInfo->elf_file->SetPosition, 2, loaderInfo->elf_file, 0);
    status = uefi_call_wrapper(loaderInfo->elf_file->Read, 3, loaderInfo->elf_file, &readsz, (void*)(ehdr));

    return ehdr;
}

Elf64_Phdr* load_elf_phdrs(e64l_load_info* loaderInfo, Elf64_Ehdr* elfHeader)
{

    EFI_STATUS status;
    UINTN readsz = elfHeader->e_phnum * elfHeader->e_phentsize;

    Elf64_Phdr* phdr;
    status = uefi_call_wrapper(BS->AllocatePool, 3, 2, readsz, &phdr);

    status = uefi_call_wrapper(loaderInfo->elf_file->SetPosition, 2, loaderInfo->elf_file, elfHeader->e_phoff);
    status = uefi_call_wrapper(loaderInfo->elf_file->Read, 3, loaderInfo->elf_file, &readsz, (void*)(phdr));

    return phdr;
}

void* elf_pt_load(e64l_load_info* loaderInfo, Elf64_Phdr* phdr)
{
    EFI_STATUS status;
    UINTN readsz = phdr->p_filesz;
    UINTN base = phdr->p_vaddr;

    // Num pages to allocate is phdr->p_memsz rounded up to the next 4096
    UINTN num_pages = (phdr->p_memsz + 4095) >> 12;
    void* alloc = (void*)(base & ~0x7FF);
    void* load = (void*)base;
    status = uefi_call_wrapper(BS->AllocatePages, 4, AllocateAddress, 2, num_pages, &alloc);

    // FIXME: Handle allocation issues

    status = uefi_call_wrapper(loaderInfo->elf_file->SetPosition, 2, loaderInfo->elf_file, phdr->p_offset);
    status = uefi_call_wrapper(loaderInfo->elf_file->Read, 3, loaderInfo->elf_file, &readsz, load);

    return load;
}

// void elf_pt_dynamic(e64l_loader_info* loaderInfo, Elf64_Phdr* dynamic, Elf64_Phdr* phdr)
//{
//    UINTN relaBase;
//    UINTN relaNum;
//}

efi_main_f* load_image(e64l_load_info* loaderInfo)
{
    int i;
    Elf64_Ehdr* ehdr = load_elf_header(loaderInfo);

    // Check is ELF64

    Elf64_Phdr* phdr = load_elf_phdrs(loaderInfo, ehdr);

    for (i = 0; i < ehdr->e_phnum; i++) {
        if (phdr[i].p_type == 1) /* PT_LOAD */
            phdr[i].p_paddr = (UINTN)(elf_pt_load(loaderInfo, &phdr[i]));
        // HACK: Since p_addr is reserved unused, we use it internally to store the actual load address, rather than creating a
        // second data structure
    }

    efi_main_f* entry_point = (efi_main_f*)ehdr->e_entry;

    // for (i = 0; i < ehdr->e_phnum; i++) {
    //    if (phdr[i].p_type == PT_DYNAMIC) {
    //    }
    //}

    return entry_point;
}
