#include "ll/uefi/tables/system.hh"
#include "ll/uefi/protocols/loaded_image.hh"
#include "ll/uefi/protocols/simple_file_system.hh"
#include "jones/jones.hh"
#include "jones/jones_loadable.hh"
#include "string.h"

#include "conurbation/uefi/console.hh"

using namespace ll::UEFI;

namespace Jones {

    efiabi extern "C" auto efi_main(handle_t ImageHandle, Tables::system_table_t* SystemTable) -> status_t {

        console_logging_t* con = new (SystemTable) console_logging_t(SystemTable->ConOut);

        status_t status;

        jones_p* jones_;
        jones_loadable_p* loadable_;

        Protocols::device_path_p* imagePath_;

        Protocols::loaded_image_p* thisImage_;
        Protocols::simple_file_system_p* rootDevice_;
        Protocols::file_p* rootDir_;

        con->info(u"Jones Loder Framework");


        status = SystemTable->BootServices->HandleProtocol(ImageHandle, &protocol_guid_v<Protocols::loaded_image_p>, reinterpret_cast<void**>(&thisImage_));
        status = SystemTable->BootServices->HandleProtocol(thisImage_->DeviceHandle, &protocol_guid_v<Protocols::simple_file_system_p>, reinterpret_cast<void**>(&rootDevice_));

        // if (status == status_t::Success) {
        //     status = rootDevice_->OpenVolume(rootDevice_, &rootDir_);
        // } else {
        //     status = SystemTable->BootServices->HandleProtocol(thisImage_->DeviceHandle, &protocol_guid_v<efi_file_p>, reinterpret_cast<void**>(&rootDir_));
        // }
        // if (status != status_t::Success) {
        //     con->error(u"Unable to open root file system");
        //     return status;
        // }

        status = SystemTable->BootServices->LocateProtocol(&protocol_guid_v<Jones::jones_p>, nullptr, reinterpret_cast<void**>(&jones_));
        if (status == status_t::Success) {
            con->info(u"Connected to Jones service");
        } else if (status == status_t::NotFound) {
            con->warn(u"Could not connect to Jones service");
            con->info(u"Attempting to load Jones service");


            return status_t::Aborted;
        }

        //SystemTable->BootServices->LoadImage(false, ImageHandle, dp, nullptr, 0, &hdrv);

        //jones_->GetLoader(imagePath_, &loadable_);



        return status_t::Success;



    }

}
