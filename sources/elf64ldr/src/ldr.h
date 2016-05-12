#ifndef LDR_H
#define LDR_H

typedef struct {
    CHAR16* elf_image_name;
    EFI_FILE_HANDLE elf_file;
} e64l_load_info;

typedef EFI_STATUS(EFIAPI efi_main_f)(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);

efi_main_f* load_image(e64l_load_info* loaderInfo);

#endif /* end of include guard: LDR_H */
