#include <efi.h>
#include <efilib.h>
#include <efishellparm.h>
#include "ldr.h"

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_STATUS status;

    InitializeLib(ImageHandle, SystemTable);

    Print(L"Hello World!\n");

    Print(L"Image Handle: %lx\n", (UINTN)ImageHandle);
    Print(L"System Table: %lx\n", (UINTN)SystemTable);

    CHAR16** argv;
    INTN argc = GetShellArgcArgv(ImageHandle, &argv);

    Print(L"%d Parameters:\n", argc);

    for (int i = 0; i < argc; i++) {
        Print(L"%d: %s\n", i, argv[i]);
    }

    Print(L"\n");

    // Get our own EFI_LOADED_IMAGE_PROTOCOL
    EFI_LOADED_IMAGE* thisimage;
    EFI_GUID loaded_image_protocol_guid = LOADED_IMAGE_PROTOCOL;
    status = uefi_call_wrapper(BS->HandleProtocol, 3, ImageHandle, &loaded_image_protocol_guid, (void**)&thisimage);
    Print(L"Got EFI_LOADED_IMAGE_PROTOCOL\n");

    // Get the ESP root directory
    EFI_FILE_HANDLE rootDir;
    rootDir = LibOpenRoot(thisimage->DeviceHandle);
    Print(L"Got Root Directory\n");

    // Load the Kernel

    e64l_load_info loadInfo;
    loadInfo.elf_image_name = argv[1];

    efi_main_f* ep;
    status
        = uefi_call_wrapper(rootDir->Open, 5, rootDir, &(loadInfo.elf_file), loadInfo.elf_image_name, EFI_FILE_MODE_READ, 0);

    Print(L"Opening Kernel (%s): %r\n", loadInfo.elf_image_name, status);
    ep = load_image(&loadInfo);
    Print(L"Kernel entry point at %lx\n", ep);
    status = uefi_call_wrapper(loadInfo.elf_file->Close, 1, loadInfo.elf_file);

    return uefi_call_wrapper(ep, 2, ImageHandle, SystemTable);
}
