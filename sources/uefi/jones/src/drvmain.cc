#include "conurbation/uefi/tables.hh"
#include "conurbation/uefi/protocol/file.hh"
#include "jones/jones.hh"
#include "jones/jones_loader.hh"
#include "jones/jones_loadable.hh"

using namespace Conurbation::UEFI;

handle_t ImageHandle;
efi_system_table_t* SystemTable;

namespace Jones {



    efiabi auto get_loader_(efi_device_path_p* image, jones_loadable_p** loadable) -> status_t {

        status_t status;

        uintptr_t numLoaders;
        handle_t* buffer;

        status = SystemTable->BootServices->LocateHandleBuffer(locate_search_type_t::ByProtocol, &protocol_guid_v<jones_loader_p>, nullptr, &numLoaders, &buffer);
        if (status == status_t::NotFound) return status_t::NotStarted;

        jones_loader_p* loader;

        efi_device_path_p* img_path = image;
        handle_t fileHandle;
        efi_file_p* fileProto;

        SystemTable->BootServices->LocateDevicePath(&protocol_guid_v<efi_file_p>, &img_path, &fileHandle);
        SystemTable->BootServices->OpenProtocol(fileHandle, &protocol_guid_v<efi_file_p>, reinterpret_cast<void**>(&fileProto), ImageHandle, nullptr, 2);

        for (size_t i = 0; i < numLoaders; i++) {
            status = SystemTable->BootServices->OpenProtocol(buffer[i], &protocol_guid_v<jones_loader_p>, reinterpret_cast<void**>(&loader), ImageHandle, nullptr, 2);
            status = loader->CanLoad(loader, fileProto);
            if (status == status_t::Success) {
                status = loader->PrepareLoad(loader, fileHandle, fileProto, loadable);
                // Should probably deallocate the buffer...
                if (status == status_t::Success) {
                    SystemTable->BootServices->FreePool(buffer);
                    return status_t::Success;
                }
            }
        }

        return status_t::NotFound;

    };

    jones_p loader_ = { &get_loader_ };

    efiabi extern "C" auto efi_main(handle_t imageHandle, efi_system_table_t* systemTable) -> status_t {

        ImageHandle = imageHandle;
        SystemTable = systemTable;

        return SystemTable->BootServices->InstallProtocolInterface(&ImageHandle, &protocol_guid_v<Jones::jones_p>, interface_type_t::EFI_NATIVE_INTERFACE, reinterpret_cast<void**>(&loader_));

    }

}
