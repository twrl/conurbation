#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/loaded_image.hh"
#include "ll/uefi/protocols/simple_file_system.hh"
#include "ll/elf64.hh"
#include "ll/memory.hh"

#define _cat(a, b) a ## b
#define _loc2(X) _cat(u, #X)
#define LOC(F, L) _cat(u, F) u":" _loc2(L)

using namespace ll::UEFI;

typedef status_t (efiabi efi_entry_point_f)(handle_t, Tables::system_table_t*);

auto status_check(status_t status, const char16_t* supp, handle_t ImageHandle, Tables::system_table_t* SystemTable) -> void {
    if (status != status_t::Success) {
        const char16_t* msg;
        switch (status) {
        case status_t::LoadError:
            msg = u"Load Error";
            break;
        case status_t::InvalidParameter:
            msg = u"Invalid Parameter";
            break;
        case status_t::Unsupported:
            msg = u"Unsupported";
            break;
        case status_t::BadBufferSize:
            msg = u"Bad Buffer Size";
            break;
        case status_t::BufferTooSmall:
            msg = u"Buffer Too Small";
            break;
        case status_t::NotFound:
            msg = u"Not Found";
            break;
        case status_t::Aborted:
            msg = u"Aborted";
            break;
        default:
            msg = u"Unknown Error";
            break;
        }
        SystemTable->console_out->OutputString(SystemTable->console_out, u"ERROR: ");
        SystemTable->console_out->OutputString(SystemTable->console_out, msg);
        SystemTable->console_out->OutputString(SystemTable->console_out, u" <");
        SystemTable->console_out->OutputString(SystemTable->console_out, supp);
        SystemTable->console_out->OutputString(SystemTable->console_out, u">\r\n");
        SystemTable->BootServices->Exit(ImageHandle, status, 0, nullptr);
    }
}

efiabi extern "C" auto efi_main(handle_t ImageHandle, Tables::system_table_t* SystemTable) -> status_t {

    status_t _r;
    Protocols::loaded_image_p* LoadedImage;
    Protocols::simple_file_system_p* FileSystem;
    Protocols::file_p* FsRoot;
    Protocols::file_p* KernelFile;

    elf64_ehdr_t ElfHeader;
    elf64_phdr_t* SegmentHeaders;



    _r = SystemTable->BootServices->HandleProtocol(ImageHandle, &protocol_guid_v<Protocols::loaded_image_p>, reinterpret_cast<void**>(&LoadedImage));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &protocol_guid_v<Protocols::simple_file_system_p>, reinterpret_cast<void**>(&FileSystem));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    //  _r = SystemTable->BootServices->LocateProtocol(&protocol_guid_v<Protocols::simple_file_system_p>, nullptr, reinterpret_cast<void**>(&FileSystem));
    //  status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = FileSystem->OpenVolume(FileSystem, &FsRoot);
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = FsRoot->Open(FsRoot, &KernelFile, u"\\EFI\\Conurbation\\kernel.sys", 1, 0);
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = KernelFile->SetPosition(KernelFile, 0);
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    auto ehdr_size = sizeof(elf64_ehdr_t);

    _r = KernelFile->Read(KernelFile, &ehdr_size, reinterpret_cast<void*>(&ElfHeader));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    // FIXME: Perform assorted checks to make sure the ELF header is good and that we're behaving appropriately...
    // For now, we assume that it's a valid ELF64 and load according to the PHDRS

    _r = KernelFile->SetPosition(KernelFile, ElfHeader.e_phoff);
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    uintptr_t phdrs_size = ElfHeader.e_phentsize * ElfHeader.e_phnum;

    _r = SystemTable->BootServices->AllocatePool(memory_type_t::EfiLoaderData, phdrs_size, reinterpret_cast<void**>(&SegmentHeaders));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = KernelFile->Read(KernelFile, &phdrs_size, reinterpret_cast<void*>(SegmentHeaders));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    // FIXME: Don't assume that PHDRS are sizeof(elf64_phdr_t) - they will be, but the spec implies otherwise

    for (auto i = 0; i < ElfHeader.e_phnum; ++i)
    {
        uintptr_t pagesToAlloc;

        switch (SegmentHeaders[i].p_type) {
        case 1:
            SegmentHeaders[i].p_vaddr += 1_MiB;
            pagesToAlloc = (SegmentHeaders[i].p_memsz + 4095) >> 12;
            _r = SystemTable->BootServices->AllocatePages(allocate_type_t::AllocateAddress, memory_type_t::OsCode, pagesToAlloc, &(SegmentHeaders[i].p_vaddr));
            status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

            _r = KernelFile->SetPosition(KernelFile, SegmentHeaders[i].p_offset);
            status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

            _r = KernelFile->Read(KernelFile, &SegmentHeaders[i].p_filesz, reinterpret_cast<void*>(SegmentHeaders[i].p_vaddr));
            status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);
            break;
        default:
            break;
        }
    }

    efi_entry_point_f* target_main = reinterpret_cast<efi_entry_point_f*>(ElfHeader.e_entry + 1_MiB);

    SystemTable->console_out->OutputString(SystemTable->console_out, u"Ready to start kernel...\r\n");

    Protocols::loaded_image_p ChildLoadedImage{
        0x1000,
        ImageHandle,
        SystemTable,
        LoadedImage->DeviceHandle,
        nullptr, // FIXME: FilePath
        nullptr,
        0,
        nullptr,
        reinterpret_cast<void*>(1_MiB),
        0, // FIXME: ImageSize
        memory_type_t::OsCode,
        memory_type_t::OsData,
        nullptr // FIXME: Unload
    };

    handle_t ChildHandle = nullptr;

    _r = SystemTable->BootServices->InstallProtocolInterface(&ChildHandle, &protocol_guid_v<Protocols::loaded_image_p>, interface_type_t::EFI_NATIVE_INTERFACE, reinterpret_cast<void*>(&ChildLoadedImage));
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    _r = target_main(ChildHandle, SystemTable);
    status_check(_r, LOC(__FILE__, __LINE__), ImageHandle, SystemTable);

    return status_t::Success;

}
