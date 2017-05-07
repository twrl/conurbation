#include "conurbation/uefi/tables.hh"
#include "conurbation/uefi/loaded_image.hh"
#include "conurbation/uefi/simple_file_system.hh"
#include "jones/jones.hh"
#include "jones/jones_loadable.hh"

using namespace Conurbation::UEFI;

namespace Jones {

    efiabi extern "C" auto efi_main(handle_t ImageHandle, efi_system_table_t* SystemTable) -> status_t {

        status_t status;

        jones_p* jones_;
        jones_loadable_p* loadable_;

        efi_device_path_p* imagePath_;

        efi_loaded_image_p* thisImage_;
        efi_simple_file_system_p* rootDevice_;
        efi_device_path_utilities_p* devpathUtils;

        // status = SystemTable->BootServices->LocateProtocol(&protocol_guid_v<efi_device_path_utilities_p>, nullptr, reinterpret_cast<void**>(&devpathUtils));
        // if (status != status_t::Success) {
        //     SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Device Path Utilities Protocol not available\r\n");
        //     return status_t::Aborted;
        // }


        status = SystemTable->BootServices->HandleProtocol(ImageHandle, &protocol_guid_v<efi_loaded_image_p>, reinterpret_cast<void**>(&thisImage_));
        status = SystemTable->BootServices->HandleProtocol(thisImage_->DeviceHandle, &protocol_guid_v<efi_simple_file_system_p>, reinterpret_cast<void**>(&rootDevice_));

        SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
        SystemTable->ConOut->OutputString(SystemTable->ConOut, u"Jones Loader Framework...\r\n\r\n");


        status = SystemTable->BootServices->LocateProtocol(&protocol_guid_v<Jones::jones_p>, nullptr, reinterpret_cast<void**>(&jones_));
        if (status == status_t::NotFound) {
            // Load the driver and try again...
            SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x0D);
            SystemTable->ConOut->OutputString(SystemTable->ConOut, u"    [WARN]  Could not connect to driver first time, attempting to load...\r\n");

            //efi_file_media_device_path_t dp{efi_device_path_type_t::media, 4, 52, u"\\uefi-llvm\\jonessvc.efi\0"};
            SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x07);

            return status_t::Aborted;
        }

        //SystemTable->BootServices->LoadImage(false, ImageHandle, dp, nullptr, 0, &hdrv);

        //jones_->GetLoader(imagePath_, &loadable_);



        return status_t::Success;



    }

}
