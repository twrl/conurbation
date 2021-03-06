#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/file.hh"
#include "jones/jones_loader.hh"
#include "jones/jones_loadable.hh"
#include "ll/elf64.hh"

using namespace ll::UEFI;

extern handle_t ImageHandle;
extern Tables::system_table_t* SystemTable;

namespace Jones {

    namespace {

        struct loadable_t {
            jones_loadable_p loadable;
            handle_t thisHandle;
            handle_t loadedHandle;
        };

        efiabi auto load_image_elf64(jones_loadable_p* ld)-> status_t {
            loadable_t* loadable = reinterpret_cast<loadable_t*>(ld);
            return status_t::NotStarted;
        }

        efiabi auto can_load_elf64(jones_loader_p* loader, Protocols::file_p* file) -> status_t {

            elf64_ehdr_t elf_;

            file->SetPosition(file, 0UL);
            uintptr_t r = sizeof(elf64_ehdr_t);
            file->Read(file, &r, reinterpret_cast<void*>(&elf_));

            // Check the header to confirm that we are ELF64, little-endian, machine x86_64, and executable or dynamic
            if (elf_.e_ident[0] == 0x7f &&
            elf_.e_ident[1] == 0x45 &&
            elf_.e_ident[2] == 0x4c &&
            elf_.e_ident[3] == 0x46 &&
            elf_.e_ident[4] == 2 &&
            elf_.e_ident[5] == 1 &&
            (elf_.e_type == 2 || elf_.e_type == 3) &&
            elf_.e_machine == 0x3e) return status_t::Success;
            else return status_t::LoadError;

        }

        efiabi auto prepare_load_elf64(jones_loader_p* loader, handle_t fileHandle, Protocols::file_p* file, jones_loadable_p** loadable) -> status_t {
            loadable_t* ld;

            if (can_load_elf64(loader, file) == status_t::LoadError) return status_t::LoadError;

            SystemTable->BootServices->AllocatePool(memory_type_t::EfiBootServicesData, sizeof(loadable_t), reinterpret_cast<void**>(&ld));
            // Initialize ld

            ld->loadable.Load = &load_image_elf64;
            ld->thisHandle = fileHandle;
            ld->loadedHandle = nullptr;

            // Install LD to handle
            SystemTable->BootServices->InstallProtocolInterface(&fileHandle, &protocol_guid_v<jones_loadable_p>, interface_type_t::EFI_NATIVE_INTERFACE, reinterpret_cast<void**>(&ld));
            *loadable = &(ld->loadable);
            return status_t::Success;
        }

        jones_loader_p loader_ = { &can_load_elf64, &prepare_load_elf64 };
        handle_t loader_handle_ = nullptr;

    }

    auto register_loader_elf64() {

        SystemTable->BootServices->InstallProtocolInterface(&loader_handle_, &protocol_guid_v<jones_loader_p>, interface_type_t::EFI_NATIVE_INTERFACE, reinterpret_cast<void**>(&loader_));


    }

}
